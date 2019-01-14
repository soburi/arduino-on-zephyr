/* udp.c - UDP specific code for echo client */

/*
 * Copyright (c) 2017 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_MODULE_NAME net_echo_client_udp
#define NET_LOG_LEVEL LOG_LEVEL_DBG

#include <zephyr.h>
#include <errno.h>
#include <stdio.h>

#include <net/net_pkt.h>
#include <net/net_core.h>
#include <net/net_context.h>

#include <net/net_app.h>

#include "zephyr_in_addr.h"
#include "zephyr_udp.h"

static struct net_app_ctx udp6;

struct zephyr_udp_context {
  struct net_app_ctx ctx;
  void* thisptr;
  z_udp_receive_callback received;
};

#define UDP_SLEEP K_MSEC(150)
#define BUF_TIMEOUT K_MSEC(100)
#define WAIT_TIME K_SECONDS(10)
#define CONNECT_TIME K_SECONDS(10)

/* Note that both tcp and udp can share the same pool but in this
 * example the UDP context and TCP context have separate pools.
 */
#if defined(CONFIG_NET_CONTEXT_NET_PKT_POOL)
NET_PKT_TX_SLAB_DEFINE(echo_tx_udp, 5);
NET_PKT_DATA_POOL_DEFINE(echo_data_udp, 20);

static struct k_mem_slab *tx_udp_slab(void)
{
	return &echo_tx_udp;
}

static struct net_buf_pool *data_udp_pool(void)
{
	return &echo_data_udp;
}
#else
#define tx_udp_slab NULL
#define data_udp_pool NULL
#endif /* CONFIG_NET_CONTEXT_NET_PKT_POOL */

#if defined(CONFIG_NET_APP_DTLS)
#define HOSTNAME "localhost"   /* for cert verification if that is enabled */

/* The result buf size is set to large enough so that we can receive max size
 * buf back. Note that mbedtls needs also be configured to have equal size
 * value for its buffer size. See MBEDTLS_SSL_MAX_CONTENT_LEN option in DTLS
 * config file.
 */
#define RESULT_BUF_SIZE 1500
static u8_t dtls_result_ipv6[RESULT_BUF_SIZE];


#if !defined(CONFIG_NET_APP_TLS_STACK_SIZE)
#define CONFIG_NET_APP_TLS_STACK_SIZE		6144
#endif /* CONFIG_NET_APP_TLS_STACK_SIZE */

#define INSTANCE_INFO "Zephyr DTLS echo-client #1"

/* Note that each net_app context needs its own stack as there will be
 * a separate thread needed.
 */
NET_STACK_DEFINE(NET_APP_DTLS_IPv6, net_app_dtls_stack_ipv6,
		 CONFIG_NET_APP_TLS_STACK_SIZE, CONFIG_NET_APP_TLS_STACK_SIZE);

NET_APP_TLS_POOL_DEFINE(dtls_pool, 10);
#else
#define dtls_result_ipv6 NULL
#define net_app_dtls_stack_ipv6 NULL
#endif /* CONFIG_NET_APP_TLS */

#if defined(CONFIG_NET_APP_TLS) || defined(CONFIG_NET_APP_DTLS)
/* Load the certificates and private RSA key. */

#include "test_certs.h"

static int setup_cert(struct net_app_ctx *ctx, void *cert)
{
#if defined(MBEDTLS_KEY_EXCHANGE__SOME__PSK_ENABLED)
	mbedtls_ssl_conf_psk(&ctx->tls.mbedtls.conf,
			     client_psk, sizeof(client_psk),
			     (const unsigned char *)client_psk_id,
			     sizeof(client_psk_id) - 1);
#endif

#if defined(MBEDTLS_X509_CRT_PARSE_C)
	{
		mbedtls_x509_crt *ca_cert = cert;
		int ret;

		ret = mbedtls_x509_crt_parse_der(ca_cert,
						 ca_certificate,
						 sizeof(ca_certificate));
		if (ret != 0) {
			NET_ERR("mbedtls_x509_crt_parse_der failed "
				"(-0x%02x)", -ret);
			return ret;
		}

		mbedtls_ssl_conf_ca_chain(&ctx->tls.mbedtls.conf,
					  ca_cert, NULL);

		/* In this example, we skip the certificate checks. In real
		 * life scenarios, one should always verify the certificates.
		 */
		mbedtls_ssl_conf_authmode(&ctx->tls.mbedtls.conf,
					  MBEDTLS_SSL_VERIFY_REQUIRED);

		mbedtls_ssl_conf_cert_profile(&ctx->tls.mbedtls.conf,
					    &mbedtls_x509_crt_profile_default);
#define VERIFY_CERTS 0
#if VERIFY_CERTS
		mbedtls_ssl_conf_authmode(&ctx->tls.mbedtls.conf,
					  MBEDTLS_SSL_VERIFY_OPTIONAL);
#else
		;
#endif /* VERIFY_CERTS */
	}
#endif /* MBEDTLS_X509_CRT_PARSE_C */

	return 0;
}
#endif /* CONFIG_NET_APP_TLS */

void udp_init_context(void* context, void* thisptr, z_udp_receive_callback callback)
{
  struct zephyr_udp_context*  zctx = (struct zephyr_udp_context*)context;
  memset(zctx, 0, sizeof(struct zephyr_udp_context));
  zctx->thisptr = thisptr;
  zctx->received = callback;
}


void udp_send(void* context, const unsigned char* buf, size_t buflen)
{
  struct net_app_ctx* ctx = &udp6;
  struct net_pkt *pkt;
  size_t len = buflen;
  int ret;

  NET_INFO("send_udp_data %d\n", buflen);
    
  pkt = net_app_get_net_pkt(ctx, AF_UNSPEC, BUF_TIMEOUT);
  if (!pkt) return;

  net_pkt_append(pkt, buflen, buf, K_FOREVER);
  len = net_pkt_get_len(pkt);

  ret = net_app_send_pkt(ctx, pkt, NULL, 0, K_FOREVER, UINT_TO_POINTER(len));
  if (ret < 0) {
    net_pkt_unref(pkt);
  }
}

static void udp_received(struct net_app_ctx *ctx,
			 struct net_pkt *pkt,
			 int status,
			 void *context)
{
  u8_t* recvdata = net_pkt_appdata(pkt);
  size_t len = net_pkt_appdatalen(pkt);
  struct sockaddr_in6 srcaddr = {0};
  struct sockaddr_in6 dstaddr = {0};

  NET_INFO("udp_received %d : %d bytes\n", status, len);
  net_pkt_get_src_addr(pkt, (struct sockaddr*)&srcaddr, sizeof(struct sockaddr));
  net_pkt_get_dst_addr(pkt, (struct sockaddr*)&dstaddr, sizeof(struct sockaddr));

  struct sockaddr_in *psrc = (struct sockaddr_in*)&srcaddr;
  struct sockaddr_in *pdst = (struct sockaddr_in*)&dstaddr;

  struct zephyr_udp_context*  zctx = (struct zephyr_udp_context*)context;
  zctx->received( zctx->thisptr, (struct z_in_addr*)&psrc->sin_addr, psrc->sin_port,
		                 (struct z_in_addr*)&pdst->sin_addr, pdst->sin_port,
				 recvdata, len);

  net_pkt_unref(pkt);
}

void udp_connect(void* context, struct z_in_addr* in_addr, unsigned short peer_port)
{
  //void* user_data = &conf.ipv6;
  u8_t* dtls_result_buf = dtls_result_ipv6;
  size_t dtls_result_buf_len = sizeof(dtls_result_ipv6);
  k_thread_stack_t* stack = net_app_dtls_stack_ipv6;
  size_t stack_size = K_THREAD_STACK_SIZEOF(net_app_dtls_stack_ipv6);

  NET_INFO("udp_connect %d", sizeof(struct net_app_ctx));

  //struct data *data = user_data;
  int ret;

  struct sockaddr_in6 sa6 = { 0 };
  sa6.sin6_family = AF_INET6;
  sa6.sin6_port = peer_port;
  sa6.sin6_scope_id = 0;
  memcpy(&sa6.sin6_addr, in_addr, sizeof(sa6.sin6_addr));

  ret = net_app_release(&udp6);
  
  ret = net_app_init_udp_client(&udp6, NULL, (struct sockaddr*)&sa6, NULL, 0, WAIT_TIME, context);
  if (ret < 0) {
     NET_ERR("Cannot init UDP client (%d)", ret);
    return;
  }

#if defined(CONFIG_NET_CONTEXT_NET_PKT_POOL)
  net_app_set_net_pkt_pool(ctx, tx_udp_slab, data_udp_pool);
#endif

  ret = net_app_set_cb(&udp6, NULL, udp_received, NULL, NULL);
  if (ret < 0) {
    NET_ERR("Cannot set callbacks (%d)", ret);
    return;
  }

#if defined(CONFIG_NET_APP_DTLS)
  ret = net_app_client_tls(&udp6,
         dtls_result_buf,
         dtls_result_buf_len,
         INSTANCE_INFO,
         strlen(INSTANCE_INFO),
         setup_cert,
         HOSTNAME,
         NULL,
         &dtls_pool,
         stack,
         stack_size);
  if (ret < 0) {
    NET_ERR("Cannot init DTLS");
    return;
  }
#else
  ARG_UNUSED(dtls_result_buf);
  ARG_UNUSED(dtls_result_buf_len);
  ARG_UNUSED(stack);
  ARG_UNUSED(stack_size);
#endif

  ret = net_app_connect(&udp6, CONNECT_TIME);
  if (ret < 0) {
    NET_ERR("Cannot connect UDP (%d)", ret);
    return;
  }


}

void udp_close(void* context)
{
  net_app_close(&udp6);
  net_app_release(&udp6);
}
