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

#define OTCLS(cls) OT ## cls
#define OT_DECL__FUNC(n, cls, rettype, fn, ...) \
rettype OpenThreadClass::  OTCLS(cls)  ::  fn (OT_DECL_ARGS ## n(__VA_ARGS__)) \
{ \
  rettype ret = OT_CALL_FUNC ## n(cls, fn); \
  return ret; \
}

#define OT_DECL_VFUNC(n, cls, rettype, fn, ...) \
rettype OpenThreadClass::  OTCLS(cls)  ::  fn (OT_DECL_ARGS ## n(__VA_ARGS__)) \
{ \
  OT_CALL_FUNC ## n(cls, fn); \
}

otError OpenThreadClass::OTInstance::SetStateChangedCallback(otStateChangedCallback cb, void* user)
{
  return otSetStateChangedCallback(instance, cb, user);
}

void OpenThreadClass::OTInstance::RemoveStateChangeCallback(otStateChangedCallback cb, void* user)
{
  otRemoveStateChangeCallback(instance, cb, user);
}
OT_DECL_VFUNC(0, Instance, void, Reset);
OT_DECL_VFUNC(0, Instance, void, FactoryReset);

OT_DECL__FUNC(3, BorderRouter, otError, GetNetData, bool, uint8_t*, uint8_t*)
OT_DECL__FUNC(1, BorderRouter, otError, AddOnMeshPrefix, const otBorderRouterConfig*)
OT_DECL__FUNC(1, BorderRouter, otError, RemoveOnMeshPrefix, const otIp6Prefix*)
OT_DECL__FUNC(2, BorderRouter, otError, GetNextOnMeshPrefix, otNetworkDataIterator*, otBorderRouterConfig*)
OT_DECL__FUNC(1, BorderRouter, otError, AddRoute, const otExternalRouteConfig*)
OT_DECL__FUNC(1, BorderRouter, otError, RemoveRoute, const otIp6Prefix*)
OT_DECL__FUNC(2, BorderRouter, otError, GetNextRoute, otNetworkDataIterator*, otExternalRouteConfig*)
OT_DECL__FUNC(0, BorderRouter, otError, Register)

OT_DECL__FUNC(0, Commissioner, otError, Start)
OT_DECL__FUNC(0, Commissioner, otError, Stop)
OT_DECL__FUNC(3, Commissioner, otError, AddJoiner, const otExtAddress*, const char*, uint32_t)
OT_DECL__FUNC(1, Commissioner, otError, RemoveJoiner, const otExtAddress*)
OT_DECL__FUNC(1, Commissioner, otError, SetProvisioningUrl, const char*)
OT_DECL__FUNC(4, Commissioner, otError, AnnounceBegin, uint32_t, uint8_t, uint16_t, const otIp6Address*)
OT_DECL__FUNC(7, Commissioner, otError, EnergyScan, uint32_t, uint8_t, uint16_t, uint16_t, const otIp6Address*, otCommissionerEnergyReportCallback, void*)
OT_DECL__FUNC(5, Commissioner, otError, PanIdQuery, uint16_t, uint32_t, const otIp6Address*, otCommissionerPanIdConflictCallback, void*)
OT_DECL__FUNC(2, Commissioner, otError, SendMgmtGet, const uint8_t*, uint8_t)
OT_DECL__FUNC(3, Commissioner, otError, SendMgmtSet, const otCommissioningDataset*, const uint8_t*, uint8_t)
OT_DECL__FUNC(0, Commissioner, uint16_t, GetSessionId)
OT_DECL__FUNC(0, Commissioner, otCommissionerState, GetState)
OT_DECL__FUNC(4, Commissioner, otError, GeneratePSKc, const char*, const char*, const otExtendedPanId*, uint8_t*)

OT_DECL__FUNC(0, Dataset, bool, IsCommissioned)
OT_DECL__FUNC(1, Dataset, otError, GetActive, otOperationalDataset*)
OT_DECL__FUNC(1, Dataset, otError, SetActive, const otOperationalDataset*)
OT_DECL__FUNC(1, Dataset, otError, GetPending, otOperationalDataset*)
OT_DECL__FUNC(1, Dataset, otError, SetPending, const otOperationalDataset*)
OT_DECL__FUNC(4, Dataset, otError, SendMgmtActiveGet, const otOperationalDatasetComponents*, const uint8_t*, uint8_t, const otIp6Address*)
OT_DECL__FUNC(3, Dataset, otError, SendMgmtActiveSet, const otOperationalDataset*, const uint8_t*, uint8_t)
OT_DECL__FUNC(4, Dataset, otError, SendMgmtPendingGet, const otOperationalDatasetComponents*, const uint8_t*, uint8_t, const otIp6Address*)
OT_DECL__FUNC(3, Dataset, otError, SendMgmtPendingSet, const otOperationalDataset*, const uint8_t*, uint8_t)
OT_DECL__FUNC(0, Dataset, uint32_t, GetDelayTimerMinimal)
OT_DECL__FUNC(1, Dataset, otError, SetDelayTimerMinimal, uint32_t)

OT_DECL__FUNC(1, Ip6, otError, SetEnabled, bool)
OT_DECL__FUNC(0, Ip6, bool, IsEnabled)
OT_DECL__FUNC(1, Ip6, otError, AddUnicastAddress, const otNetifAddress*)
OT_DECL__FUNC(1, Ip6, otError, RemoveUnicastAddress, const otIp6Address*)
OT_DECL__FUNC(0, Ip6, const otNetifAddress*, GetUnicastAddresses)

OT_DECL__FUNC(8, Joiner, otError, Start, const char*, const char*, const char*, const char*, const char*, const char*, otJoinerCallback, void*)
OT_DECL__FUNC(0, Joiner, otError, Stop)
OT_DECL__FUNC(0, Joiner, otJoinerState, GetState)
OT_DECL__FUNC(1, Joiner, otError, GetId, otExtAddress*)

OT_DECL__FUNC(4, Link, otError, ActiveScan, uint32_t, uint16_t, otHandleActiveScanResult, void*)
OT_DECL__FUNC(0, Link, bool, IsActiveScanInProgress)
OT_DECL__FUNC(4, Link, otError, EnergyScan, uint32_t, uint16_t, otHandleEnergyScanResult, void*)
OT_DECL__FUNC(0, Link, bool, IsEnergyScanInProgress)
OT_DECL__FUNC(0, Link, otError, SendDataRequest)
OT_DECL__FUNC(0, Link, bool, IsInTransmitState)
OT_DECL__FUNC(1, Link, otError, OutOfBandTransmitRequest, otRadioFrame*)
OT_DECL__FUNC(0, Link, uint8_t, GetChannel)
OT_DECL__FUNC(1, Link, otError, SetChannel, uint8_t)
OT_DECL__FUNC(0, Link, const otExtAddress*, GetExtendedAddress)
OT_DECL__FUNC(1, Link, otError, SetExtendedAddress, const otExtAddress*)
OT_DECL_VFUNC(1, Link, void, GetFactoryAssignedIeeeEui64, otExtAddress*)
OT_DECL__FUNC(0, Link, otPanId, GetPanId)
OT_DECL__FUNC(1, Link, otError, SetPanId, otPanId)
OT_DECL__FUNC(0, Link, uint32_t, GetPollPeriod)
OT_DECL__FUNC(1, Link, otError, SetPollPeriod, uint32_t)
OT_DECL__FUNC(0, Link, otShortAddress, GetShortAddress)
OT_DECL__FUNC(0, Link, otMacFilterAddressMode, FilterGetAddressMode)
OT_DECL__FUNC(1, Link, otError, FilterSetAddressMode, otMacFilterAddressMode)
OT_DECL__FUNC(1, Link, otError, FilterAddAddress, const otExtAddress*)
OT_DECL__FUNC(1, Link, otError, FilterRemoveAddress, const otExtAddress*)
OT_DECL_VFUNC(0, Link, void, FilterClearAddresses)
OT_DECL__FUNC(2, Link, otError, FilterGetNextAddress, otMacFilterIterator*, otMacFilterEntry*)
OT_DECL__FUNC(2, Link, otError, FilterAddRssIn, const otExtAddress*, int8_t)
OT_DECL__FUNC(1, Link, otError, FilterRemoveRssIn, const otExtAddress*)
OT_DECL_VFUNC(0, Link, void, FilterClearRssIn)
OT_DECL__FUNC(2, Link, otError, FilterGetNextRssIn, otMacFilterIterator*, otMacFilterEntry*)
OT_DECL__FUNC(0, Link, const otMacCounters*, GetCounters)

OT_DECL_VFUNC(1, Message, void, GetBufferInfo, otBufferInfo*)

OT_DECL__FUNC(3, NetData, otError, Get, bool, uint8_t*, uint8_t*)
OT_DECL__FUNC(2, NetData, otError, GetNextOnMeshPrefix, otNetworkDataIterator*, otBorderRouterConfig*)
OT_DECL__FUNC(0, NetData, uint8_t, GetVersion)
OT_DECL__FUNC(0, NetData, uint8_t, GetStableVersion)

OT_DECL__FUNC(3, Server, otError, GetNetDataLocal, bool, uint8_t*, uint8_t*)
OT_DECL__FUNC(1, Server, otError, AddService, const otServiceConfig*)
OT_DECL__FUNC(3, Server, otError, RemoveService, uint32_t, uint8_t*, uint8_t)
OT_DECL__FUNC(2, Server, otError, GetNextService, otNetworkDataIterator*, otServiceConfig*)
OT_DECL__FUNC(2, Server, otError, GetNextLeaderService, otNetworkDataIterator*, otServiceConfig*)
OT_DECL__FUNC(0, Server, otError, Register)

OT_DECL__FUNC(1, Thread, otError, SetEnabled, bool)
OT_DECL__FUNC(0, Thread, bool, GetAutoStart)
OT_DECL__FUNC(1, Thread, otError, SetAutoStart, bool)
OT_DECL__FUNC(0, Thread, bool, IsSingleton)
OT_DECL__FUNC(6, Thread, otError, Discover, uint32_t, uint16_t, bool, bool, otHandleActiveScanResult, void*)
OT_DECL__FUNC(0, Thread, bool, IsDiscoverInProgress)
OT_DECL__FUNC(0, Thread, uint32_t, GetChildTimeout)
OT_DECL_VFUNC(1, Thread, void, SetChildTimeout, uint32_t)
OT_DECL__FUNC(0, Thread, const otExtendedPanId*, GetExtendedPanId)
OT_DECL__FUNC(1, Thread, otError, SetExtendedPanId, const otExtendedPanId*)
OT_DECL__FUNC(1, Thread, otError, GetLeaderRloc, otIp6Address*)
OT_DECL__FUNC(0, Thread, otLinkModeConfig, GetLinkMode)
OT_DECL__FUNC(1, Thread, otError, SetLinkMode, otLinkModeConfig)
OT_DECL__FUNC(0, Thread, const otMasterKey*, GetMasterKey)
OT_DECL__FUNC(1, Thread, otError, SetMasterKey, const otMasterKey*)
OT_DECL__FUNC(0, Thread, const otIp6Address*, GetMeshLocalEid)
OT_DECL__FUNC(0, Thread, const otMeshLocalPrefix*, GetMeshLocalPrefix)
OT_DECL__FUNC(1, Thread, otError, SetMeshLocalPrefix, const otMeshLocalPrefix*)
OT_DECL__FUNC(0, Thread, const char*, GetNetworkName)
OT_DECL__FUNC(1, Thread, otError, SetNetworkName, const char*)
OT_DECL__FUNC(0, Thread, uint32_t, GetKeySequenceCounter)
OT_DECL_VFUNC(1, Thread, void, SetKeySequenceCounter, uint32_t)
OT_DECL__FUNC(0, Thread, uint32_t, GetKeySwitchGuardTime)
OT_DECL_VFUNC(1, Thread, void, SetKeySwitchGuardTime, uint32_t)
OT_DECL__FUNC(0, Thread, otError, BecomeDetached)
OT_DECL__FUNC(0, Thread, otError, BecomeChild)
OT_DECL__FUNC(2, Thread, otError, GetNextNeighborInfo, otNeighborInfoIterator*, otNeighborInfo*)
OT_DECL__FUNC(0, Thread, otDeviceRole, GetDeviceRole)
OT_DECL__FUNC(1, Thread, otError, GetLeaderData, otLeaderData*)
OT_DECL__FUNC(0, Thread, uint8_t, GetLeaderRouterId)
OT_DECL__FUNC(0, Thread, uint8_t, GetLeaderWeight)
OT_DECL__FUNC(0, Thread, uint32_t, GetPartitionId)
OT_DECL__FUNC(0, Thread, uint16_t, GetRloc16)
OT_DECL__FUNC(1, Thread, otError, GetParentInfo, otRouterInfo*)
OT_DECL__FUNC(1, Thread, otError, GetParentAverageRssi, int8_t*)
OT_DECL__FUNC(1, Thread, otError, GetParentLastRssi, int8_t*)
OT_DECL__FUNC(3, Thread, otError, SendDiagnosticGet, const otIp6Address*, const uint8_t*, uint8_t)
OT_DECL__FUNC(3, Thread, otError, SendDiagnosticReset, const otIp6Address*, const uint8_t*, uint8_t)
OT_DECL__FUNC(0, Thread, const otIpCounters*, GetIp6Counters)
OT_DECL__FUNC(2, Thread, otError, RegisterParentResponseCallback, otThreadParentResponseCallback, void*)
OT_DECL__FUNC(0, Thread, uint8_t, GetMaxAllowedChildren)
OT_DECL__FUNC(1, Thread, otError, SetMaxAllowedChildren, uint8_t)
OT_DECL__FUNC(0, Thread, bool, IsRouterRoleEnabled)
OT_DECL_VFUNC(1, Thread, void, SetRouterRoleEnabled, bool)
OT_DECL__FUNC(1, Thread, otError, SetPreferredRouterId, uint8_t)
OT_DECL__FUNC(0, Thread, uint8_t, GetLocalLeaderWeight)
OT_DECL_VFUNC(1, Thread, void, SetLocalLeaderWeight, uint8_t)
OT_DECL__FUNC(0, Thread, uint32_t, GetLocalLeaderPartitionId)
OT_DECL_VFUNC(1, Thread, void, SetLocalLeaderPartitionId, uint32_t)
OT_DECL__FUNC(0, Thread, uint16_t, GetJoinerUdpPort)
OT_DECL__FUNC(1, Thread, otError, SetJoinerUdpPort, uint16_t)
OT_DECL__FUNC(0, Thread, uint32_t, GetContextIdReuseDelay)
OT_DECL_VFUNC(1, Thread, void, SetContextIdReuseDelay, uint32_t)
OT_DECL__FUNC(0, Thread, uint8_t, GetNetworkIdTimeout)
OT_DECL_VFUNC(1, Thread, void, SetNetworkIdTimeout, uint8_t)
OT_DECL__FUNC(0, Thread, uint8_t, GetRouterUpgradeThreshold)
OT_DECL_VFUNC(1, Thread, void, SetRouterUpgradeThreshold, uint8_t)
OT_DECL__FUNC(1, Thread, otError, ReleaseRouterId, uint8_t)
OT_DECL__FUNC(0, Thread, otError, BecomeRouter)
OT_DECL__FUNC(0, Thread, otError, BecomeLeader)
OT_DECL__FUNC(0, Thread, uint8_t, GetRouterDowngradeThreshold)
OT_DECL_VFUNC(1, Thread, void, SetRouterDowngradeThreshold, uint8_t)
OT_DECL__FUNC(0, Thread, uint8_t, GetRouterSelectionJitter)
OT_DECL_VFUNC(1, Thread, void, SetRouterSelectionJitter, uint8_t)
OT_DECL__FUNC(2, Thread, otError, GetChildInfoById, uint16_t, otChildInfo*)
OT_DECL__FUNC(2, Thread, otError, GetChildInfoByIndex, uint8_t, otChildInfo*)
OT_DECL__FUNC(0, Thread, uint8_t, GetRouterIdSequence)
OT_DECL__FUNC(0, Thread, uint8_t, GetMaxRouterId)
OT_DECL__FUNC(2, Thread, otError, GetRouterInfo, uint16_t, otRouterInfo*)
OT_DECL__FUNC(2, Thread, otError, GetEidCacheEntry, uint8_t, otEidCacheEntry*)
OT_DECL__FUNC(0, Thread, const uint8_t*, GetPSKc)
OT_DECL__FUNC(1, Thread, otError, SetPSKc, const uint8_t*)
OT_DECL__FUNC(0, Thread, int8_t, GetParentPriority)
OT_DECL__FUNC(1, Thread, otError, SetParentPriority, int8_t)

