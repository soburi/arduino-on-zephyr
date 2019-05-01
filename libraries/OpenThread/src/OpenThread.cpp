/*
  Copyright (c) 2019 Tokita, Hiroshi  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "OpenThread.h"

#include <net/net_if.h>
#include <net/net_l2.h>

#include <Print.h>

#include <autoconf.h>

#ifndef ARDUINO_PREPROC
#include <openthread/config.h>
#include <openthread/commissioner.h>
#include <openthread/icmp6.h>
#include <openthread/joiner.h>
#include <openthread/link.h>
#if OPENTHREAD_CONFIG_ENABLE_TIME_SYNC
#include <openthread/network_time.h>
#endif

#if OPENTHREAD_FTD
#include <openthread/dataset_ftd.h>
#include <openthread/thread_ftd.h>
#endif

#if OPENTHREAD_ENABLE_BORDER_ROUTER
#include <openthread/border_router.h>
#endif
#if OPENTHREAD_ENABLE_SERVICE
#include <openthread/server.h>
#endif
#endif

static void find_openthread_instance(struct net_if* nif, void* data)
{
  struct net_if** piface = reinterpret_cast<struct net_if**>(data);
  // TODO We use first detected net_if that is configured with OT.
  if(IS_OPENTHREAD_L2(nif) && (*piface == NULL)) *piface = nif;
}

int OpenThreadClass::begin()
{
  struct net_if* nif = NULL;
  net_if_foreach(find_openthread_instance, &nif);

  if(nif) {
    iface = nif;
    struct openthread_context* otctx = reinterpret_cast<struct openthread_context*>(net_if_l2_data(nif));
    instance = otctx->instance;
    BorderRouter.instance = instance;
    Commissioner.instance = instance;
    Dataset.instance = instance;
    Error.instance = instance;
    Instance.instance = instance;
    Ip6.instance = instance;
    Joiner.instance = instance;
    Link.instance = instance;
    Message.instance = instance;
    NetData.instance = instance;
    Server.instance = instance;
    Thread.instance = instance;
    return 1;
  }
  return 0;
}

#define HDR(x) #x "="
#define OTFUN(x) OpenThread.x()
#define DUMP(x) n += p.print(HDR(x)); n += p.println(OTFUN(x))
#define DUMPF(x, f) n += p.print(HDR(x)); n += p.println(OTFUN(x), f)

int OpenThreadClass::dump(Print& p)
{
  int n = 0;
  DUMP(networkname);
  OTExtendedPanId epan = extpanid();
  n += p.print("extpanid="); n += p.println(epan);
  DUMPF(panid, HEX);
  OTExtAddress eadr = extaddr();
  n += p.print("extaddr="); n += p.println(eadr);

  otExtAddress ex64;
  eui64(&ex64);
  OTExtAddress e64 = &ex64;
  n += p.print("eui64="); n += p.println(e64);

  OTPSKc pk = pskc();
  n += p.print("pskc="); n += p.println(pk);
  OTMasterKey mkey = masterkey();
  n += p.print("masterkey="); n += p.println(mkey);
  DUMP(channel);
  DUMPF(rloc16, HEX);
  DUMP(ipaddr);
  DUMP(version);

  DUMP(autostart);
  DUMP(commissioner);
  DUMP(ifconfig);
  OTLinkModeConfig lmode = mode();
  n += p.print("mode="); n += p.println(lmode);
  DUMP(promiscuous);
  DUMP(routerrole);
  DUMP(state);
  DUMP(singleton);
  DUMP(txpower);

  return n;
}


#define OT_GETTER_IMPL(ty, na, cat, n2)  \
ty OpenThreadClass::  na  () \
{ \
  return OT_CALL_FUNC0(cat, Get ## n2); \
}

#define OT_FUNC_0_IMPL(ty, na, cat, n2)  \
ty OpenThreadClass::  na  () \
{ \
  return OT_CALL_FUNC0(cat, n2); \
}

#define OT_FUNC_1_IMPL(ty, na, cat, n2, t1)  \
ty OpenThreadClass::  na  (t1 a1) \
{ \
  return OT_CALL_FUNC1(cat, n2); \
}

#define OT_FUNC_2_IMPL(ty, na, cat, n2, t1, t2)  \
ty OpenThreadClass::  na  (t1 a1, t2 a2) \
{ \
  return OT_CALL_FUNC2(cat, n2); \
}

#define OT_FUNC_3_IMPL(ty, na, cat, n2, t1, t2, t3)  \
ty OpenThreadClass::  na  (t1 a1, t2 a2, t3 a3) \
{ \
  return OT_CALL_FUNC3(cat, n2); \
}

#define OT_FUNC_4_IMPL(ty, na, cat, n2, t1, t2, t3, t4)  \
ty OpenThreadClass::  na  (t1 a1, t2 a2, t3 a3, t4 a4) \
{ \
  return OT_CALL_FUNC4(cat, n2); \
}

#define OT_IS_IMPL(ty, na, cat, n2)  \
ty OpenThreadClass::  na  () \
{ \
  return OT_CALL_FUNC0(cat, Is ## n2); \
}

#define OT_SETTER_IMPL(ty, na, cat, n2)  \
otError OpenThreadClass:: na (ty a1) \
{ \
  return OT_CALL_FUNC1(cat, Set ## n2); \
}

#define OT_V_SETTER_IMPL(ty, na, cat, n2)  \
void OpenThreadClass:: na (ty a1) \
{ \
  return OT_CALL_FUNC1(cat, Set ## n2); \
}

#define OT_SETGET_IMPL(ty, na, cat, n2)  \
  OT_GETTER_IMPL(ty, na, cat, n2) \
  OT_SETTER_IMPL(ty, na, cat, n2)

#define OT_SET_IS_IMPL(ty, na, cat, n2)  \
  OT_IS_IMPL(ty, na, cat, n2) \
  OT_SETTER_IMPL(ty, na, cat, n2)

#define OT_V_SETGET_IMPL(ty, na, cat, n2)  \
  OT_GETTER_IMPL(ty, na, cat, n2) \
  OT_V_SETTER_IMPL(ty, na, cat, n2)

#define OT_V_SET_IS_IMPL(ty, na, cat, n2)  \
  OT_IS_IMPL(ty, na, cat, n2) \
  OT_V_SETTER_IMPL(ty, na, cat, n2)

#define OT_COPY_IP6(ip6, addr) {\
    ip6.mFields.m16[0] = htons(addr.v6[0]); \
    ip6.mFields.m16[1] = htons(addr.v6[1]); \
    ip6.mFields.m16[2] = htons(addr.v6[2]); \
    ip6.mFields.m16[3] = htons(addr.v6[3]); \
    ip6.mFields.m16[4] = htons(addr.v6[4]); \
    ip6.mFields.m16[5] = htons(addr.v6[5]); \
    ip6.mFields.m16[6] = htons(addr.v6[6]); \
    ip6.mFields.m16[7] = htons(addr.v6[7]); \
}

// x help
OT_SETGET_IMPL(bool, autostart, Thread, AutoStart);
OT_FUNC_1_IMPL(void, bufferinfo, Message, GetBufferInfo, otBufferInfo*);
OT_SETGET_IMPL(uint8_t, channel, Link, Channel);
OT_FUNC_2_IMPL(otError, child, Thread, GetChildInfoByIndex, int, otChildInfo*);
OT_SETGET_IMPL(uint8_t, childmax, Thread, MaxAllowedChildren);
OT_V_SETGET_IMPL(uint32_t, childtimeout, Thread, ChildTimeout);
// x coap
// x coaps
OT_GETTER_IMPL(otCommissionerState, commissioner, Commissioner, State);
OT_FUNC_0_IMPL(otError, commissioner_start, Commissioner, Start);
OT_FUNC_0_IMPL(otError, commissioner_stop, Commissioner, Stop);
OT_SETTER_IMPL(const char*, commissioner_provisioningurl, Commissioner, ProvisioningUrl);
//otError commissioner_announce(uint32_t mask, uint8_t count, uint16_t period, IPAddress& addr);
//otError commissioner_energy(uint32_t mask, uint8_t count, uint16_t period, uint16_t duration, IPAddress& addr, otCommissionerEnergyReportCallback cb, void* ctx);
//otError commissioner_panid(uint16_t, uint32_t, IPAddress&, otCommissionerPanIdConflictCallback, void* ctx);
OT_GETTER_IMPL(uint16_t, commissioner_sessionid, Commissioner, SessionId);
OT_V_SETGET_IMPL(uint32_t, contextreusedelay, Thread, ContextIdReuseDelay);
//uint32_t counter(int type);
OT_FUNC_1_IMPL(otError, dataset_active, Dataset, GetActive, otOperationalDataset*);
OT_FUNC_1_IMPL(otError, dataset_pending, Dataset, GetPending, otOperationalDataset*);
OT_FUNC_1_IMPL(otError, dataset_commit_active, Dataset, SetActive, otOperationalDataset*);
OT_FUNC_1_IMPL(otError, dataset_commit_pending, Dataset, SetPending, otOperationalDataset*);
OT_FUNC_4_IMPL(otError, dataset_mgmtget_active, Dataset, SendMgmtActiveGet, otOperationalDatasetComponents*, uint8_t*, uint8_t, otIp6Address*);
OT_FUNC_4_IMPL(otError, dataset_mgmtget_pending, Dataset, SendMgmtPendingGet, otOperationalDatasetComponents*, uint8_t*, uint8_t, otIp6Address*);
//otError dataset_mgmtget_active(otOperationalDatasetComponents* dataset, uint8_t* tlvs, uint8_t len) { return dataset_mgmtget_active(dataset, tlvs, len, NULL); }
//otError dataset_mgmtget_pending(otOperationalDatasetComponents* dataset, uint8_t* tlvs, uint8_t len) { return dataset_mgmtget_pending(dataset, tlvs, len, NULL); }
//otError dataset_mgmtget_active(otOperationalDatasetComponents* dataset, uint8_t* tlvs, uint8_t len, IPAddress& addr);
//otError dataset_mgmtget_pending(otOperationalDatasetComponents* dataset, uint8_t* tlvs, uint8_t len, IPAddress& addr);
OT_FUNC_3_IMPL(otError, dataset_mgmtset_active, Dataset, SendMgmtActiveSet, otOperationalDataset*, uint8_t*, uint8_t);
OT_FUNC_3_IMPL(otError, dataset_mgmtset_pending, Dataset, SendMgmtPendingSet, otOperationalDataset*, uint8_t*, uint8_t);
OT_SETGET_IMPL(uint32_t, delaytimermin, Dataset, DelayTimerMinimal);
// x diag
//otError discover(uint32_t chbits, otHandleActiveScanResult callback, void* context);
// x dns
//int eidcache_num();
OT_FUNC_2_IMPL(otError, eidcache, Thread, GetEidCacheEntry, int, otEidCacheEntry*);
OT_FUNC_1_IMPL(void, eui64, Link, GetFactoryAssignedIeeeEui64, otExtAddress*);
// x exit
// x logfilename
OT_SETGET_IMPL(OTExtAddress, extaddr, Link, ExtendedAddress);
OT_SETGET_IMPL(OTExtendedPanId, extpanid, Thread, ExtendedPanId);
OT_FUNC_0_IMPL(void, factoryreset, Instance, FactoryReset);
OT_SET_IS_IMPL(bool, ifconfig, Ip6, Enabled);
// x instance
// x instancelist
//int ipaddr_num();
//IPAddress ipaddr(int idx=0);
//otError ipaddr_add(IPAddress& addr, uint8_t prefixlen, bool preferred, bool valid, bool scopeoverridevalid, uint32_t scopeoverride, bool rloc);
//otError ipaddr_del(IPAddress&);
//int ipmaddr_num();
//IPAddress ipmaddr(int idx=0);
//otError ipmaddr_add(IPAddress& addr);
//otError ipmaddr_del(IPAddress& addr);
//otError joiner_start(char* pskc, char* provision, otJoinerCallback, void*);
OT_FUNC_0_IMPL(otError, joiner_stop, Joiner, Stop);
OT_FUNC_1_IMPL(otError, joinerid, Joiner, GetId, otExtAddress*);
OT_GETTER_IMPL(uint16_t, joinerport, Thread, JoinerUdpPort);
OT_V_SETGET_IMPL(uint32_t, keysequencecounter, Thread, KeySequenceCounter);
OT_V_SETGET_IMPL(uint32_t, keyswitchguadtime, Thread, KeySwitchGuardTime);
OT_FUNC_1_IMPL(otError, leaderdata, Thread, GetLeaderData, otLeaderData*);
OT_V_SETGET_IMPL(uint32_t, leaderpartitionid, Thread, LocalLeaderPartitionId);
OT_V_SETGET_IMPL(uint8_t, leaderweight, Thread, LocalLeaderWeight);
// x macfilter
OT_SETGET_IMPL(OTMasterKey, masterkey, Thread, MasterKey);
OT_SETGET_IMPL(otLinkModeConfig, mode, Thread, LinkMode);
//otError neighbor(int idx, otNeighborInfo*);
// x neighborregister
// x neighborshow
// x networkdiagnostic
OT_V_SETGET_IMPL(uint8_t, networkidtimeout, Thread, NetworkIdTimeout);
OT_SETGET_IMPL(const char*, networkname, Thread, NetworkName);
// x networktime
OT_SETGET_IMPL(uint16_t, panid, Link, PanId);
//otError parent(otRouterInfo* parent);
OT_SETGET_IMPL(uint8_t, parentpriority, Thread, ParentPriority);
//otError ping(IPAddress& addr, const uint8_t*, uint16_t);
OT_SETGET_IMPL(uint32_t, pollperiod, Link, PollPeriod);
OT_SET_IS_IMPL(bool, promiscuous, Link, Promiscuous);
//otError promiscuous(otLinkPcapCallback, void* ctx=NULL);
// x prefix
OT_SETGET_IMPL(const uint8_t*, pskc, Thread, PSKc);
OT_FUNC_1_IMPL(otError, releaserouterid, Thread, ReleaseRouterId, uint8_t);
OT_FUNC_0_IMPL(void, reset, Instance, Reset);
OT_GETTER_IMPL(uint16_t, rloc16, Thread, Rloc16);
// x route
OT_FUNC_2_IMPL(otError, router, Thread, GetRouterInfo, int, otRouterInfo*);
OT_V_SETGET_IMPL(uint8_t, routerdowngradethreshold, Thread, RouterDowngradeThreshold);
OT_V_SET_IS_IMPL(bool, routerrole, Thread, RouterRoleEnabled);
OT_V_SETGET_IMPL(uint8_t, routerselectionjitter, Thread, RouterSelectionJitter);
OT_V_SETGET_IMPL(uint8_t, routerupgradethreshold, Thread, RouterUpgradeThreshold);
OT_FUNC_4_IMPL(otError, activescan, Link, ActiveScan, uint16_t, uint32_t, otHandleActiveScanResult, void*);
OT_FUNC_4_IMPL(otError, energyscan, Link, EnergyScan, uint16_t, uint32_t, otHandleEnergyScanResult, void*);
OT_IS_IMPL(bool, singleton, Thread, Singleton);
// x sntp
OT_GETTER_IMPL(otDeviceRole, state, Thread, DeviceRole);
//otError state(otDeviceRole role);
OT_SETTER_IMPL(bool, thread, Thread, Enabled);
OT_SETTER_IMPL(int8_t, txpower, PlatRadio, TransmitPower);
OT_FUNC_1_IMPL(otError, txpower, PlatRadio, GetTransmitPower, int8_t*);
//const char* version() { return otGetVersionString(); }


otError OpenThreadClass::commissioner_announce(uint32_t mask, uint8_t count, uint16_t period, IPAddress& addr)
{
  struct otIp6Address address;
  otError error;
  OT_COPY_IP6(address, addr);
  error = otCommissionerAnnounceBegin(instance, mask, count, period, &address);
  return error;
}
otError OpenThreadClass::commissioner_energy(uint32_t mask, uint8_t count, uint16_t period, uint16_t duration, IPAddress& addr, otCommissionerEnergyReportCallback cb, void* ctx)
{
  struct otIp6Address address;
  otError error;
  OT_COPY_IP6(address, addr);
  error = otCommissionerEnergyScan(instance, mask, count, period, duration, &address, cb, ctx);
  return error;
}
otError OpenThreadClass::commissioner_panid(uint16_t panid, uint32_t mask, IPAddress& addr, otCommissionerPanIdConflictCallback cb, void* ctx)
{
  struct otIp6Address address;
  otError error;
  OT_COPY_IP6(address, addr);
  error = otCommissionerPanIdQuery(instance, panid, mask, &address, cb, ctx);
  return error;
}

uint32_t OpenThreadClass::counter(int type)
{
  uint32_t ret = 0xFFFFFFFF;
  const otMacCounters* counters = otLinkGetCounters(instance);
  switch(type) //TODO
  {
  case 0:
    ret = counters->mTxTotal;
  }
  return ret;
}

otError OpenThreadClass::dataset_mgmtget_active(otOperationalDatasetComponents* dataset, uint8_t* tlvs, uint8_t len, IPAddress& addr)
{
  struct otIp6Address address;
  OT_COPY_IP6(address, addr);
  return dataset_mgmtget_active(dataset, tlvs, len, &address);
}

otError OpenThreadClass::dataset_mgmtget_pending(otOperationalDatasetComponents* dataset, uint8_t* tlvs, uint8_t len, IPAddress& addr)
{
  struct otIp6Address address;
  OT_COPY_IP6(address, addr);
  return dataset_mgmtget_pending(dataset, tlvs, len, &address);
}

otError OpenThreadClass::discover(uint32_t chbits, otHandleActiveScanResult callback, void* context)
{
  otError err = otThreadDiscover(instance, chbits, OT_PANID_BROADCAST, false, false, callback, context);
  return err;
}


void OpenThreadClass::discover_sync_callback(otActiveScanResult *aResult, void *aContext)
{
  struct discover_data* data= reinterpret_cast<struct discover_data*>(aContext);
  if(aResult) {
    if(data->size == data->count) {
      data->error = OT_ERROR_NO_BUFS;
      k_sem_give(&data->sem);
    }
    else {
      memcpy(&data->table[data->count], aResult, sizeof(otActiveScanResult));
      data->count++;
    }
  }
  else {
    if(data->error != OT_ERROR_NO_BUFS) {
      k_sem_give(&data->sem);
    }
  }
}

otError OpenThreadClass::discover(otActiveScanResult* table, size_t tablesize, uint32_t chbits)
{
  memset(&sync_discover_context, 0, sizeof(struct discover_data));

  sync_discover_context.table = table;
  sync_discover_context.size = tablesize;
  k_sem_init(&sync_discover_context.sem, 0, 1);

  otError err = otThreadDiscover(instance, chbits, OT_PANID_BROADCAST, false, false, discover_sync_callback, &sync_discover_context);
  if(err) return err;

  k_sem_take(&sync_discover_context.sem, K_FOREVER);

  return sync_discover_context.error;
}

int OpenThreadClass::eidcache_num()
{
  int ret = 0;
  for (uint8_t i = 0;; i++)
  {
    otEidCacheEntry entry;
    if(otThreadGetEidCacheEntry(instance, i, &entry)) {
      ret = (i-1);
      break;
    }
  }

  return ret;
}

int OpenThreadClass::ipaddr_num()
{
  int count = 0;

  for (const otNetifAddress *addr = otIp6GetUnicastAddresses(instance); addr; addr = addr->mNext) {
    count++;
  }
  return count;
}

IPAddress OpenThreadClass::ipaddr(int idx)
{
  int count = 0;
  const otNetifAddress* addr = NULL;
  uint16_t* u16null = NULL;

  for (addr = otIp6GetUnicastAddresses(instance); addr; addr = addr->mNext) {
    if(count == idx) break;
  }
  return (addr ? addr->mAddress.mFields.m16 : u16null);
}

otError OpenThreadClass::ipaddr_add(IPAddress& addr, uint8_t prefixlen, bool preferred, bool valid, bool scopeoverridevalid, uint32_t scopeoverride, bool rloc)
{
  otError err;
  struct otNetifAddress address;

  OT_COPY_IP6(address.mAddress, addr);
  address.mPrefixLength = prefixlen;
  address.mPreferred = preferred;
  address.mValid = valid;
  address.mScopeOverrideValid = scopeoverridevalid;
  address.mScopeOverride = scopeoverride;
  address.mRloc = rloc;

  err = otIp6AddUnicastAddress(instance, &address);
  return err;
}
otError OpenThreadClass::ipaddr_del(IPAddress& addr)
{
  otError err;
  struct otIp6Address address;
  OT_COPY_IP6(address, addr);
  err = otIp6RemoveUnicastAddress(instance, &address);
  return err;
}

int OpenThreadClass::ipmaddr_num()
{

  int count = 0;
  for (const otNetifMulticastAddress *addr = otIp6GetMulticastAddresses(instance); addr; addr = addr->mNext) {
    count++;
  }
  return count;
}

IPAddress OpenThreadClass::ipmaddr(int idx)
{
  int count = 0;
  const otNetifMulticastAddress* addr = NULL;
  static const uint16_t* u16null = NULL;

  for (addr = otIp6GetMulticastAddresses(instance); addr; addr = addr->mNext) {
    if(count == idx) break;
  }
  return (addr ? addr->mAddress.mFields.m16 : u16null);
}

otError OpenThreadClass::ipmaddr_add(IPAddress& addr)
{
  otError error;
  struct otIp6Address address;
  OT_COPY_IP6(address, addr);
  error = otIp6SubscribeMulticastAddress(instance, &address);
  return error;
}

otError OpenThreadClass::ipmaddr_del(IPAddress& addr)
{
  otError error;
  struct otIp6Address address;
  OT_COPY_IP6(address, addr);
  error = otIp6UnsubscribeMulticastAddress(instance, &address);
  return error;
}

otError OpenThreadClass::joiner_start(char* pskc, char* provision, otJoinerCallback cb, void* ctx)
{
  otError err = OT_ERROR_NONE;
  err = otJoinerStart(instance, pskc, provision, PACKAGE_NAME, CONFIG_OPENTHREAD_PLATFORM_INFO,
                      PACKAGE_VERSION, NULL, cb, ctx);
  return err;
}

void OpenThreadClass::joiner_start_sync_callback(otError aResult, void *aContext)
{
   struct joiner_start_data* data = reinterpret_cast<struct joiner_start_data*>(aContext);
   data->error = aResult;
   k_sem_give(&data->sem);
}

otError OpenThreadClass::joiner_start(char* pskc, char* provision)
{
  memset(&sync_joiner_start_context, 0, sizeof(struct joiner_start_data));
  k_sem_init(&sync_joiner_start_context.sem, 0, 1);

  otError err = otJoinerStart(instance, pskc, provision, PACKAGE_NAME, CONFIG_OPENTHREAD_PLATFORM_INFO,
                      PACKAGE_VERSION, NULL, joiner_start_sync_callback, &sync_joiner_start_context);

  if(err) return err;

  k_sem_take(&sync_joiner_start_context.sem, K_FOREVER);

  return sync_joiner_start_context.error;
}

otError OpenThreadClass::neighbor(int index, otNeighborInfo* neighborInfo)
{
  otError err = OT_ERROR_NONE;
  otNeighborInfoIterator iterator = OT_NEIGHBOR_INFO_ITERATOR_INIT;
  for(int i=0; i<=index; i++) {
    err = otThreadGetNextNeighborInfo(instance, &iterator, neighborInfo);
    if(err) break;
  }
  return err;
}

otError OpenThreadClass::ping(IPAddress& addr, const uint8_t* buffer, uint16_t buflen)
{
  otMessageInfo messageInfo = {0};
  otError error = OT_ERROR_NONE;

  OT_COPY_IP6(messageInfo.mPeerAddr, addr);
  messageInfo.mInterfaceId = OT_NETIF_INTERFACE_ID_THREAD;

  otMessage* message = otIp6NewMessageFromBuffer(instance, buffer, buflen, NULL);
  if(!message) {
    error = OT_ERROR_NO_BUFS;
    goto exit;
  }
    
  error = otIcmp6SendEchoRequest(instance, message, &messageInfo, 1);

  if (error != OT_ERROR_NONE && message != NULL) {
    otMessageFree(message);
  }
exit:
  return error;
}

otError OpenThreadClass::promiscuous(otLinkPcapCallback cb, void* ctx)
{
  otError err = OT_ERROR_NONE;
  if(cb) {
    otLinkSetPcapCallback(instance, cb, ctx);
    err = otLinkSetPromiscuous(instance, true);
  }
  else {
    otLinkSetPcapCallback(instance, NULL, NULL);
    err = otLinkSetPromiscuous(instance, false);
  }
  return err;
}

otError OpenThreadClass::state(otDeviceRole role)
{
  otError err = OT_ERROR_NONE;
  switch (role)
  {
    case OT_DEVICE_ROLE_DETACHED:
      err = otThreadBecomeDetached(instance);
      break;
    case OT_DEVICE_ROLE_CHILD:
      err = otThreadBecomeChild(instance);
      break;

#if OPENTHREAD_FTD
    case OT_DEVICE_ROLE_ROUTER:
      err = otThreadBecomeRouter(instance);
      break;
    case OT_DEVICE_ROLE_LEADER:
      err = otThreadBecomeLeader(instance);
      break;
#endif // OPENTHREAD_FTD
    default:
      break;
  }
  return err;
}

OpenThreadClass OpenThread;
