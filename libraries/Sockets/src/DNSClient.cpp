// Arduino DNS client for WizNet5100-based Ethernet shield
// (c) Copyright 2009-2010 MCQN Ltd.
// Released under Apache License, version 2.0

#include "IPAddress.h"
#include "DNSClient.h"

#include <net/net_ip.h>
#include <net/net_pkt.h>
#include <net/dns_resolve.h>

#define DNS_SERVER_COUNT CONFIG_DNS_RESOLVER_MAX_SERVERS
#define SERVER_COUNT     (DNS_SERVER_COUNT + DNS_MAX_MCAST_SERVERS)

#define MDNS_IPV4_ADDR "224.0.0.251:5353"
#define MDNS_IPV6_ADDR "[ff02::fb]:5353"

#define LLMNR_IPV4_ADDR "224.0.0.252:5355"
#define LLMNR_IPV6_ADDR "[ff02::1:3]:5355"

// Possible return codes from ProcessResponse
#define SUCCESS          1
#define TIMED_OUT        -1
#define INVALID_SERVER   -2
#define TRUNCATED        -3
#define INVALID_RESPONSE -4

int DNSClient::begin()
{
	return 0;
}

int DNSClient::inet_aton(const char* address, IPAddress& result)
{
	struct sockaddr_in6 in6;
	int ret = net_addr_pton(AF_INET6, address, &in6);

	return ret ? 0 : 1;
}

struct dns_result {
	struct dns_addrinfo info;
	enum dns_resolve_status status;
	struct k_sem* sem;
};

static void dns_result_cb(enum dns_resolve_status status,
		   struct dns_addrinfo *info,
		   void *user_data)
{
	struct dns_result* pack = reinterpret_cast<struct dns_result*>(user_data);
	pack->status = status;
	memcpy(&pack->info, info, sizeof(struct dns_addrinfo));
	k_sem_give(pack->sem);
}

int DNSClient::getHostByName(const char* query, IPAddress& aResult, uint16_t timeout)
{
	uint16_t dns_id = {0};
	struct dns_result result = {0};

	k_sem_init(&query_sem, 0, 1);
	result.sem = &query_sem;

	int ret = dns_resolve_name(dns_resolve_get_default()/*&context*/, query,
				DNS_QUERY_TYPE_AAAA,
				&dns_id, dns_result_cb, &result, timeout);

	if(ret) return ret;

	k_sem_take(&query_sem, K_FOREVER);

	aResult = net_sin6(&result.info.ai_addr)->sin6_addr.s6_addr16;

	return 1;
}
