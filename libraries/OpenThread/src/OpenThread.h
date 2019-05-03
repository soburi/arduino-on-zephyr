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

#ifndef SOCKETS_OPENTHREAD_H
#define SOCKETS_OPENTHREAD_H

#include "NetworkInterface.h"
#include "Print.h"

#include <net/openthread.h>
#include <openthread/cli.h>
#include <openthread/border_router.h>
#include <openthread/instance.h>
#include <openthread/ip6.h>
#include <openthread/link.h>
#include <openthread/message.h>
#include <openthread/tasklet.h>
#include <openthread/thread.h>
#include <openthread/thread_ftd.h>
#include <openthread/dataset.h>
#include <openthread/joiner.h>
#include <openthread/netdata.h>
#include <openthread/server.h>
#include <openthread/platform/radio.h>
#include <openthread-system.h>
#ifndef ARDUINO_PREPROC
#include <openthread-config-generic.h>
#endif

#define OT_CALL_FUNC0(cls, fn) ot##cls##fn (instance)
#define OT_CALL_FUNC1(cls, fn) ot##cls##fn (instance, a1)
#define OT_CALL_FUNC2(cls, fn) ot##cls##fn (instance, a1, a2)
#define OT_CALL_FUNC3(cls, fn) ot##cls##fn (instance, a1, a2, a3)
#define OT_CALL_FUNC4(cls, fn) ot##cls##fn (instance, a1, a2, a3, a4)
#define OT_CALL_FUNC5(cls, fn) ot##cls##fn (instance, a1, a2, a3, a4, a5)
#define OT_CALL_FUNC6(cls, fn) ot##cls##fn (instance, a1, a2, a3, a4, a5, a6)
#define OT_CALL_FUNC7(cls, fn) ot##cls##fn (instance, a1, a2, a3, a4, a5, a6, a7)
#define OT_CALL_FUNC8(cls, fn) ot##cls##fn (instance, a1, a2, a3, a4, a5, a6, a7, a8)

#define OT_DECL_ARGS0()
#define OT_DECL_ARGS1(T1) T1 a1
#define OT_DECL_ARGS2(T1, T2) T1 a1, T2 a2
#define OT_DECL_ARGS3(T1, T2, T3) T1 a1, T2 a2, T3 a3
#define OT_DECL_ARGS4(T1, T2, T3, T4) T1 a1, T2 a2, T3 a3, T4 a4
#define OT_DECL_ARGS5(T1, T2, T3, T4, T5) T1 a1, T2 a2, T3 a3, T4 a4, T5 a5
#define OT_DECL_ARGS6(T1, T2, T3, T4, T5, T6) T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6
#define OT_DECL_ARGS7(T1, T2, T3, T4, T5, T6, T7) T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7
#define OT_DECL_ARGS8(T1, T2, T3, T4, T5, T6, T7, T8) T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6, T7 a7, T8 a8

#define OT_IS_DECL(ty, na, cat, n2)  ty na ();
#define OT_GETTER_DECL(ty, na, cat, n2)  ty na ();
#define OT_SETTER_DECL(ty, na, cat, n2)  otError na (ty arg);
#define OT_V_SETTER_DECL(ty, na, cat, n2)  void na (ty arg);

#define OT_SETGET_DECL(ty, na, cat, n2)  \
  OT_SETTER_DECL(ty, na, cat, n2); \
  OT_GETTER_DECL(ty, na, cat, n2) \

#define OT_SET_IS_DECL(ty, na, cat, n2)  \
  OT_SETTER_DECL(ty, na, cat, n2); \
  OT_IS_DECL(ty, na, cat, n2) \

#define OT_V_SETGET_DECL(ty, na, cat, n2)  \
  OT_V_SETTER_DECL(ty, na, cat, n2); \
  OT_GETTER_DECL(ty, na, cat, n2) \

#define OT_V_SET_IS_DECL(ty, na, cat, n2)  \
  OT_V_SETTER_DECL(ty, na, cat, n2); \
  OT_IS_DECL(ty, na, cat, n2) \

#define OT_FUNC_0_DECL(ty, na, cat, n2) \
  ty na()

#define OT_FUNC_1_DECL(ty, na, cat, n2, t1) \
  ty na(t1)

#define OT_FUNC_2_DECL(ty, na, cat, n2, t1, t2) \
  ty na(t1, t2)

#define OT_FUNC_3_DECL(ty, na, cat, n2, t1, t2, t3) \
  ty na(t1, t2, t3)

#define OT_FUNC_4_DECL(ty, na, cat, n2, t1, t2, t3, t4) \
  ty na(t1, t2, t3, t4)

template<typename T> class OTm8Buffer : public Printable {
public:
  OTm8Buffer(const T* v) : value(v) { }
  OTm8Buffer(const uint8_t* v) : value( reinterpret_cast<const T*>(v) ) { }
  size_t printTo(Print& p) const {
    size_t n=0;
    for(unsigned int i=0; i<sizeof(T); i++) {
      uint8_t byte = value->m8[i];
      if(byte <= 0xF) n += p.print('0');
      n += p.print(byte, HEX);
    }
    return n;
  }
  operator const uint8_t*() { return value->m8; }
  operator const T*() { return value; }
private:
  const T* value;
};

template<typename T> class OTm8String : public Printable {
public:
  OTm8String(const T* v) : value(v) { }
  size_t printTo(Print& p) const {
    return p.print(value->m8);
  }
private:
  const T* value;
};

typedef class OTm8Buffer<otExtAddress> OTExtAddress;
typedef class OTm8Buffer<otExtendedPanId> OTExtendedPanId;
typedef class OTm8Buffer<otMasterKey> OTMasterKey;
typedef class OTm8String<otNetworkName> OTNetworkName;

class OTPSKc : public Printable{
public:
  OTPSKc(const uint8_t* v) : pskc(v) { }
  size_t printTo(Print& p) const {
    size_t n=0;
    for(int i=0; i<OT_PSKC_MAX_SIZE; i++) {
      n += p.print(pskc[i], HEX);
    }
    return n;
  }

private:
  const uint8_t* pskc;
};

class OTLinkModeConfig : public Printable{
public:
  OTLinkModeConfig(otLinkModeConfig v) : conf(v) { }
  size_t printTo(Print& p) const {
    size_t n = 0;
    if (conf.mRxOnWhenIdle)       n += p.print("r");
    if (conf.mSecureDataRequests) n += p.print("s");
    if (conf.mDeviceType)         n += p.print("d");
    if (conf.mNetworkData)        n += p.print("n");
    return n;
  }

private:
  otLinkModeConfig conf;
};

class OpenThreadClass : public NetworkInterface {
public:
  int begin();
  int dump(Print& p);
  // x help
  OT_SETGET_DECL(bool, autostart, Thread, AutoStart);
  OT_FUNC_1_DECL(void, bufferinfo, Message, GetBufferInfo, otBufferInfo*);
  OT_SETGET_DECL(uint8_t, channel, Link, Channel);
#ifdef CONFIG_OPENTHREAD_FTD
  OT_FUNC_2_DECL(otError, child, Thread, GetChildInfoByIndex, int, otChildInfo*);
  OT_SETGET_DECL(uint8_t, childmax, Thread, MaxAllowedChildren);
#endif
  OT_V_SETGET_DECL(uint32_t, childtimeout, Thread, ChildTimeout);
  // x coap
  // x coaps
#ifdef CONFIG_OPENTHREAD_COMMISSIONER
  OT_GETTER_DECL(otCommissionerState, commissioner, Commissioner, State);
  OT_FUNC_0_DECL(otError, commissioner_start, Commissioner, Start);
  OT_FUNC_0_DECL(otError, commissioner_stop, Commissioner, Stop);
  OT_SETTER_DECL(const char*, commissioner_provisioningurl, Commissioner, ProvisioningUrl);
  otError commissioner_announce(uint32_t mask, uint8_t count, uint16_t period, IPAddress& addr);
  otError commissioner_energy(uint32_t mask, uint8_t count, uint16_t period, uint16_t duration, IPAddress& addr, otCommissionerEnergyReportCallback cb, void* ctx);
  otError commissioner_panid(uint16_t, uint32_t, IPAddress&, otCommissionerPanIdConflictCallback, void* ctx);
  OT_GETTER_DECL(uint16_t, commissioner_sessionid, Commissioner, SessionId);
#endif
#ifdef CONFIG_OPENTHREAD_FTD
  OT_V_SETGET_DECL(uint32_t, contextreusedelay, Thread, ContextIdReuseDelay);
#endif
  uint32_t counter(int type);
  OT_FUNC_1_DECL(otError, dataset_active, Dataset, GetActive, otOperationalDataset*);
  OT_FUNC_1_DECL(otError, dataset_pending, Dataset, GetPending, otOperationalDataset*);
  OT_FUNC_1_DECL(otError, dataset_commit_active, Dataset, SetActive, otOperationalDataset*);
  OT_FUNC_1_DECL(otError, dataset_commit_pending, Dataset, SetPending, otOperationalDataset*);
  OT_FUNC_4_DECL(otError, dataset_mgmtget_active, Dataset, SendMgmtActiveGet, otOperationalDatasetComponents*, uint8_t*, uint8_t, otIp6Address*);
  OT_FUNC_4_DECL(otError, dataset_mgmtget_pending, Dataset, SendMgmtPendingGet, otOperationalDatasetComponents*, uint8_t*, uint8_t, otIp6Address*);
  otError dataset_mgmtget_active(otOperationalDatasetComponents* dataset, uint8_t* tlvs, uint8_t len) { return dataset_mgmtget_active(dataset, tlvs, len, NULL); }
  otError dataset_mgmtget_pending(otOperationalDatasetComponents* dataset, uint8_t* tlvs, uint8_t len) { return dataset_mgmtget_pending(dataset, tlvs, len, NULL); }
  otError dataset_mgmtget_active(otOperationalDatasetComponents* dataset, uint8_t* tlvs, uint8_t len, IPAddress& addr);
  otError dataset_mgmtget_pending(otOperationalDatasetComponents* dataset, uint8_t* tlvs, uint8_t len, IPAddress& addr);
  OT_FUNC_3_DECL(otError, dataset_mgmtset_active, Dataset, SendMgmtActiveSet, otOperationalDataset*, uint8_t*, uint8_t);
  OT_FUNC_3_DECL(otError, dataset_mgmtset_pending, Dataset, SendMgmtPendingSet, otOperationalDataset*, uint8_t*, uint8_t);
  OT_SETGET_DECL(uint32_t, delaytimermin, Dataset, DelayTimerMinimal);
  // x diag
  otError discover(uint32_t chbits, otHandleActiveScanResult callback, void* context);
  otError discover(otActiveScanResult* table, size_t tablesize, uint32_t chbits=0xFFFFFFFF);
  // x dns
#ifdef CONFIG_OPENTHREAD_FTD
  int eidcache_num();
  OT_FUNC_2_DECL(otError, eidcache, Thread, GetEidCacheEntry, int, otEidCacheEntry*);
#endif
  OT_FUNC_1_DECL(void, eui64, Link, GetFactoryAssignedIeeeEui64, otExtAddress*);
  // x exit
  // x logfilename
  OT_SETGET_DECL(OTExtAddress, extaddr, Link, ExtendedAddress);
  OT_SETGET_DECL(OTExtendedPanId, extpanid, Thread, ExtendedPanId);
  OT_FUNC_0_DECL(void, factoryreset, Instance, FactoryReset);
  OT_SET_IS_DECL(bool, ifconfig, Ip6, Enabled);
  // x instance
  // x instancelist
  int ipaddr_num();
  IPAddress ipaddr(int idx=0);
  otError ipaddr_add(IPAddress& addr, uint8_t prefixlen, bool preferred, bool valid, bool scopeoverridevalid, uint32_t scopeoverride, bool rloc);
  otError ipaddr_del(IPAddress&);
  int ipmaddr_num();
  IPAddress ipmaddr(int idx=0);
  otError ipmaddr_add(IPAddress& addr);
  otError ipmaddr_del(IPAddress& addr);
#ifdef CONFIG_OPENTHREAD_JOINER
  otError joiner_start(char* pskc, char* provision, otJoinerCallback, void*);
  otError joiner_start(char* pskc, char* provision=NULL);
  OT_FUNC_0_DECL(otError, joiner_stop, Joiner, Stop);
  OT_FUNC_1_DECL(otError, joinerid, Joiner, GetId, otExtAddress*);
#endif
#ifdef CONFIG_OPENTHREAD_FTD
  OT_GETTER_DECL(uint16_t, joinerport, Thread, JoinerUdpPort);
#endif
  OT_V_SETGET_DECL(uint32_t, keysequencecounter, Thread, KeySequenceCounter);
  OT_V_SETGET_DECL(uint32_t, keyswitchguadtime, Thread, KeySwitchGuardTime);
  OT_FUNC_1_DECL(otError, leaderdata, Thread, GetLeaderData, otLeaderData*);
#ifdef CONFIG_OPENTHREAD_FTD
  OT_V_SETGET_DECL(uint32_t, leaderpartitionid, Thread, LocalLeaderPartitionId);
  OT_V_SETGET_DECL(uint8_t, leaderweight, Thread, LocalLeaderWeight);
#endif
  // x macfilter
  OT_SETGET_DECL(OTMasterKey, masterkey, Thread, MasterKey);
  OT_SETGET_DECL(otLinkModeConfig, mode, Thread, LinkMode);
#ifdef CONFIG_OPENTHREAD_FTD
  otError neighbor(int idx, otNeighborInfo*);
#endif
  // x neighborregister
  // x neighborshow
  // x networkdiagnostic
  OT_V_SETGET_DECL(uint8_t, networkidtimeout, Thread, NetworkIdTimeout);
  OT_SETGET_DECL(const char*, networkname, Thread, NetworkName);
  // x networktime
  OT_SETGET_DECL(uint16_t, panid, Link, PanId);
  otError parent(otRouterInfo* parent);
  OT_SETGET_DECL(uint8_t, parentpriority, Thread, ParentPriority);
  otError ping(IPAddress& addr, const uint8_t*, uint16_t);
  OT_SETGET_DECL(uint32_t, pollperiod, Link, PollPeriod);
  OT_SET_IS_DECL(bool, promiscuous, Link, Promiscuous);
  otError promiscuous(otLinkPcapCallback, void* ctx=NULL);
  // x prefix
#ifdef CONFIG_OPENTHREAD_FTD
  OT_SETGET_DECL(const uint8_t*, pskc, Thread, PSKc);
  OT_FUNC_1_DECL(otError, releaserouterid, Thread, ReleaseRouterId, uint8_t);
#endif
  OT_FUNC_0_DECL(void, reset, Instance, Reset);
  OT_GETTER_DECL(uint16_t, rloc16, Thread, Rloc16);
  // x route
#ifdef CONFIG_OPENTHREAD_FTD
  OT_FUNC_2_DECL(otError, router, Thread, GetRouterInfo, int, otRouterInfo*);
  OT_V_SETGET_DECL(uint8_t, routerdowngradethreshold, Thread, RouterDowngradeThreshold);
  OT_V_SET_IS_DECL(bool, routerrole, Thread, RouterRoleEnabled);
  OT_V_SETGET_DECL(uint8_t, routerselectionjitter, Thread, RouterSelectionJitter);
  OT_V_SETGET_DECL(uint8_t, routerupgradethreshold, Thread, RouterUpgradeThreshold);
#endif
  OT_FUNC_4_DECL(otError, activescan, Link, ActiveScan, uint16_t, uint32_t, otHandleActiveScanResult, void*);
  OT_FUNC_4_DECL(otError, energyscan, Link, EnergyScan, uint16_t, uint32_t, otHandleEnergyScanResult, void*);
  OT_IS_DECL(bool, singleton, Thread, Singleton);
  // x sntp
  OT_GETTER_DECL(otDeviceRole, state, Thread, DeviceRole);
  otError state(otDeviceRole role);
  OT_SETTER_DECL(bool, thread, Thread, Enabled);
  OT_SETTER_DECL(int8_t, txpower, PlatRadio, TransmitPower);
  OT_FUNC_1_DECL(otError, txpower, PlatRadio, GetTransmitPower, int8_t*);
  int8_t txpower() { int8_t ret; otError err = txpower(&ret); return err ? 0 : ret; }
  inline const char* version() { return otGetVersionString(); }
  inline const char* otErrorToString(otError err) { return otThreadErrorToString(err); }


  class OTBorderRouter {
  friend class OpenThreadClass;
  public:
    otError GetNetData(bool, uint8_t*, uint8_t*);
    otError AddOnMeshPrefix(const otBorderRouterConfig*);
    otError RemoveOnMeshPrefix(const otIp6Prefix*);
    otError GetNextOnMeshPrefix(otNetworkDataIterator*, otBorderRouterConfig*);
    otError AddRoute(const otExternalRouteConfig*);
    otError RemoveRoute(const otIp6Prefix*);
    otError GetNextRoute(otNetworkDataIterator*, otExternalRouteConfig*);
    otError Register();
  private:
    otInstance* instance;
  };

  OTBorderRouter BorderRouter;

  class OTCommissioner {
  friend class OpenThreadClass;
  public:
    otError Start();
    otError Stop();
    otError AddJoiner(const otExtAddress*, const char*, uint32_t);
    otError RemoveJoiner(const otExtAddress*);
    otError SetProvisioningUrl(const char*);
    otError AnnounceBegin(uint32_t, uint8_t, uint16_t, const otIp6Address*);
    otError EnergyScan(uint32_t, uint8_t, uint16_t, uint16_t, const otIp6Address*, otCommissionerEnergyReportCallback, void*);
    otError PanIdQuery(uint16_t, uint32_t, const otIp6Address*, otCommissionerPanIdConflictCallback, void*);
    otError SendMgmtGet(const uint8_t*, uint8_t);
    otError SendMgmtSet(const otCommissioningDataset*, const uint8_t*, uint8_t);
    uint16_t GetSessionId();
    otCommissionerState GetState();
    otError GeneratePSKc(const char*, const char*, const otExtendedPanId*, uint8_t*);
  private:
    otInstance* instance;
  };

  OTCommissioner Commissioner;

  class OTDataset {
  friend class OpenThreadClass;
  public:
    bool IsCommissioned();
    otError GetActive(otOperationalDataset*);
    otError SetActive(const otOperationalDataset*);
    otError GetPending(otOperationalDataset*);
    otError SetPending(const otOperationalDataset*);
    otError SendMgmtActiveGet(const otOperationalDatasetComponents*, const uint8_t*, uint8_t, const otIp6Address*);
    otError SendMgmtActiveSet(const otOperationalDataset*, const uint8_t*, uint8_t);
    otError SendMgmtPendingGet(const otOperationalDatasetComponents*, const uint8_t*, uint8_t, const otIp6Address*);
    otError SendMgmtPendingSet(const otOperationalDataset*, const uint8_t*, uint8_t);
    uint32_t GetDelayTimerMinimal();
    otError SetDelayTimerMinimal(uint32_t);
  private:
    otInstance* instance;
  };

  OTDataset Dataset;

  class OTError {
  friend class OpenThreadClass;
  public:
    inline const char* ErrorToString(otError err) { return otThreadErrorToString(err); }
  private:
    otInstance* instance;
  };

  OTError Error;

  class OTInstance {
  friend class OpenThreadClass;
  public:
    otError SetStateChangedCallback(otStateChangedCallback, void*);
    void RemoveStateChangeCallback(otStateChangedCallback, void*);
    void Reset();
    void FactoryReset();
    inline const char* GetVersionString(void) { return otGetVersionString(); }
  private:
    otInstance* instance;
  };

  OTInstance Instance;

  class OTIp6 {
  friend class OpenThreadClass;
  public:
    otError SetEnabled(bool);
    bool IsEnabled();
    otError AddUnicastAddress(const otNetifAddress*);
    otError RemoveUnicastAddress(const otIp6Address*);
    const otNetifAddress* GetUnicastAddresses();

    static inline bool IsAddressEqual(const otIp6Address* a1, const otIp6Address* a2)
    {
      return otIp6IsAddressEqual(a1, a2);
    }
    static inline otError AddressFromString(const char* str, otIp6Address* addr)
    {
      return otIp6AddressFromString(str, addr);
    }
    uint8_t PrefixMatch(const otIp6Address* addr1, const otIp6Address* addr2)
    {
      return otIp6PrefixMatch(addr1, addr2);
    }
  private:
    otInstance* instance;
  };

  OTIp6 Ip6;

  class OTJoiner {
  friend class OpenThreadClass;
  public:
    otError Start(const char*, const char*, const char*, const char*, const char*, const char*, otJoinerCallback, void*);
    otError Stop();
    otJoinerState GetState();
    otError GetId(otExtAddress*);
  private:
    otInstance* instance;
  };

  OTJoiner Joiner;

  class OTLink {
  friend class OpenThreadClass;
  public:
    otError ActiveScan(uint32_t, uint16_t, otHandleActiveScanResult, void*);
    bool IsActiveScanInProgress();
    otError EnergyScan(uint32_t, uint16_t, otHandleEnergyScanResult, void*);
    bool IsEnergyScanInProgress();
    otError SendDataRequest();
    bool IsInTransmitState();
    otError OutOfBandTransmitRequest(otRadioFrame*);
    uint8_t GetChannel();
    otError SetChannel(uint8_t);
    const otExtAddress* GetExtendedAddress();
    otError SetExtendedAddress(const otExtAddress*);
    void GetFactoryAssignedIeeeEui64(otExtAddress*);
    otPanId GetPanId();
    otError SetPanId(otPanId);
    uint32_t GetPollPeriod();
    otError SetPollPeriod(uint32_t);
    otShortAddress GetShortAddress();
    otMacFilterAddressMode FilterGetAddressMode();
    otError FilterSetAddressMode(otMacFilterAddressMode);
    otError FilterAddAddress(const otExtAddress*);
    otError FilterRemoveAddress(const otExtAddress*);
    void FilterClearAddresses();
    otError FilterGetNextAddress(otMacFilterIterator*, otMacFilterEntry*);
    otError FilterAddRssIn(const otExtAddress*, int8_t);
    otError FilterRemoveRssIn(const otExtAddress*);
    void FilterClearRssIn();
    otError FilterGetNextRssIn(otMacFilterIterator*, otMacFilterEntry*);
    const otMacCounters* GetCounters();

  private:
    otInstance* instance;
  };

  OTLink Link;

  class OTMessage {
  friend class OpenThreadClass;
  public:
    void GetBufferInfo(otBufferInfo*);
  private:
    otInstance* instance;
  };

  OTMessage Message;

  class OTNetData {
  friend class OpenThreadClass;
  public:
    otError Get(bool, uint8_t*, uint8_t*);
    otError GetNextOnMeshPrefix(otNetworkDataIterator*, otBorderRouterConfig*);
    uint8_t GetVersion();
    uint8_t GetStableVersion();
  private:
    otInstance* instance;
  };

  OTNetData NetData;

  class OTServer {
  friend class OpenThreadClass;
  public:
    otError GetNetDataLocal(bool, uint8_t*, uint8_t*);
    otError AddService(const otServiceConfig*);
    otError RemoveService(uint32_t, uint8_t*, uint8_t);
    otError GetNextService(otNetworkDataIterator*, otServiceConfig*);
    otError GetNextLeaderService(otNetworkDataIterator*, otServiceConfig*);
    otError Register();
  private:
    otInstance* instance;
  };

  OTServer Server;

  class OTThread {
  friend class OpenThreadClass;
  public:
    otError SetEnabled(bool aEnabled);
    bool GetAutoStart();
    otError SetAutoStart(bool aStartAutomatically);
    bool IsSingleton();

    otError Discover(uint32_t aScanChannels, uint16_t aPanId, bool aJoiner, bool aEnableEui64Filtering, otHandleActiveScanResult aCallback, void* aCallbackContext);

    bool IsDiscoverInProgress();
    uint32_t GetChildTimeout();
    void SetChildTimeout(uint32_t aTimeout);
    const otExtendedPanId* GetExtendedPanId();
    otError SetExtendedPanId(const otExtendedPanId *aExtendedPanId);
    otError GetLeaderRloc(otIp6Address *aLeaderRloc);
    otLinkModeConfig GetLinkMode();
    otError SetLinkMode(otLinkModeConfig aConfig);
    const otMasterKey* GetMasterKey();
    otError SetMasterKey(const otMasterKey *aKey);
    const otIp6Address* GetMeshLocalEid();
    const otMeshLocalPrefix* GetMeshLocalPrefix();
    otError SetMeshLocalPrefix(const otMeshLocalPrefix *aMeshLocalPrefix);
    const char* GetNetworkName();
    otError SetNetworkName(const char *aNetworkName);
    uint32_t GetKeySequenceCounter();
    void SetKeySequenceCounter(uint32_t aKeySequenceCounter);
    uint32_t GetKeySwitchGuardTime();
    void SetKeySwitchGuardTime(uint32_t aKeySwitchGuardTime);
    otError BecomeDetached();
    otError BecomeChild();
    otError GetNextNeighborInfo(otNeighborInfoIterator *aIterator, otNeighborInfo * aInfo);
    otDeviceRole GetDeviceRole();
    otError GetLeaderData(otLeaderData *aLeaderData);
    uint8_t GetLeaderRouterId();
    uint8_t GetLeaderWeight();
    uint32_t GetPartitionId();
    uint16_t GetRloc16();
    otError GetParentInfo(otRouterInfo *aParentInfo);
    otError GetParentAverageRssi(int8_t *aParentRssi);
    otError GetParentLastRssi(int8_t *aLastRssi);
    otError SendDiagnosticGet(const otIp6Address *aDestination, const uint8_t aTlvTypes[], uint8_t aCount);
    otError SendDiagnosticReset(const otIp6Address *aDestination, const uint8_t aTlvTypes[], uint8_t aCount);
    const otIpCounters* GetIp6Counters();

    otError RegisterParentResponseCallback(otThreadParentResponseCallback aCallback, void* aContext);

    uint8_t GetMaxAllowedChildren();
    otError SetMaxAllowedChildren(uint8_t aMaxChildren);
    bool IsRouterRoleEnabled();
    void SetRouterRoleEnabled(bool aEnabled);
    otError SetPreferredRouterId(uint8_t aRouterId);
    uint8_t GetLocalLeaderWeight();
    void SetLocalLeaderWeight(uint8_t aWeight);
    uint32_t GetLocalLeaderPartitionId();
    void SetLocalLeaderPartitionId(uint32_t aPartitionId);
    uint16_t GetJoinerUdpPort();
    otError SetJoinerUdpPort(uint16_t aJoinerUdpPort);
    uint32_t GetContextIdReuseDelay();
    void SetContextIdReuseDelay(uint32_t aDelay);
    uint8_t GetNetworkIdTimeout();
    void SetNetworkIdTimeout(uint8_t aTimeout);
    uint8_t GetRouterUpgradeThreshold();
    void SetRouterUpgradeThreshold(uint8_t aThreshold);
    otError ReleaseRouterId(uint8_t aRouterId);
    otError BecomeRouter();
    otError BecomeLeader();
    uint8_t GetRouterDowngradeThreshold();
    void SetRouterDowngradeThreshold(uint8_t aThreshold);
    uint8_t GetRouterSelectionJitter();
    void SetRouterSelectionJitter(uint8_t aRouterJitter);
    otError GetChildInfoById(uint16_t aChildId, otChildInfo *aChildInfo);
    otError GetChildInfoByIndex(uint8_t aChildIndex, otChildInfo *aChildInfo);
    uint8_t GetRouterIdSequence();
    uint8_t GetMaxRouterId();
    otError GetRouterInfo(uint16_t aRouterId, otRouterInfo *aRouterInfo);
    otError GetEidCacheEntry(uint8_t aIndex, otEidCacheEntry *aEntry);
    const uint8_t* GetPSKc();
    otError SetPSKc(const uint8_t *aPSKc);
    int8_t GetParentPriority();
    otError SetParentPriority(int8_t aParentPriority);
  private:
    otInstance* instance;
  };

  OTThread Thread;

private:

  struct joiner_start_data {
    struct k_sem sem;
    otError error;
  };
  struct joiner_start_data sync_joiner_start_context;

  struct discover_data {
    struct k_sem sem;
    otError error;
    otActiveScanResult* table;
    size_t size;
    size_t count;
  };
  struct discover_data sync_discover_context;

  static void joiner_start_sync_callback(otError aResult, void *aContext);
  static void discover_sync_callback(otActiveScanResult *aResult, void *aContext);

  otInstance* instance;
};

extern OpenThreadClass OpenThread;

#endif
