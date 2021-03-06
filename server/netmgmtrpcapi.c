/*
 * Copyright © 2016-2017 VMware, Inc.  All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License.  You may obtain a copy
 * of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, without
 * warranties or conditions of any kind, EITHER EXPRESS OR IMPLIED.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */


#include "includes.h"

unsigned32
netmgr_rpc_get_version(
    handle_t hBinding,
    wstring_t* ppwszVersion
    )
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;
    wstring_t pwszVersion = NULL;

    if(!hBinding || !ppwszVersion)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_version_w(
                  hPMD,
                  &pwszVersion);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszVersion = pwszVersion;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (ppwszVersion)
    {
        ppwszVersion = NULL;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_is_networkd_running(
    handle_t hBinding,
    wstring_t* ppwszIsNetworkdRunning
    )
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;
    wstring_t pwszIsNetworkdRunning = NULL;

    if(!hBinding || !ppwszIsNetworkdRunning)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_is_networkd_running_w(
                  hPMD,
                  &pwszIsNetworkdRunning);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszIsNetworkdRunning = pwszIsNetworkdRunning;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (ppwszIsNetworkdRunning)
    {
        pwszIsNetworkdRunning = NULL;
    }
    goto cleanup;
}

/*
 * Interface configuration APIs
 */
unsigned32
netmgr_rpc_set_mac_addr(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t pwszMacAddress
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname || !pwszMacAddress)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_mac_addr_w(
                  hPMD,
                  pwszIfname,
                  pwszMacAddress);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_mac_addr(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t *ppwszMacAddress
)
{
    uint32_t dwError = 0;
    wstring_t pwszMacAddress = NULL;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !pwszIfname || !ppwszMacAddress)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_mac_addr_w(
                  hPMD,
                  pwszIfname,
                  &pwszMacAddress);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszMacAddress = pwszMacAddress;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (ppwszMacAddress)
    {
        *ppwszMacAddress = NULL;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_set_link_mode(
    handle_t hBinding,
    wstring_t pwszIfname,
    NET_RPC_LINK_MODE linkMode
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_link_mode_w(hPMD, pwszIfname, linkMode);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_link_mode(
    handle_t hBinding,
    wstring_t pwszIfname,
    NET_RPC_LINK_MODE *pLinkMode
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;
    NET_RPC_LINK_MODE linkMode = RPC_LINK_MODE_UNKNOWN;

    if (!hBinding || !pwszIfname || !pLinkMode)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    netmgr_client_get_link_mode_w(hPMD, pwszIfname, &linkMode);
    BAIL_ON_PMD_ERROR(dwError);

    *pLinkMode = linkMode;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (pLinkMode)
    {
        *pLinkMode = RPC_LINK_MODE_UNKNOWN;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_set_link_mtu(
    handle_t hBinding,
    wstring_t pwszIfname,
    unsigned32 mtu
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_link_mtu_w(hPMD, pwszIfname, mtu);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_configure(
    handle_t hBinding,
    PPMD_WSTRING_ARRAY pwszIfname
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_configure_w(hPMD, pwszIfname);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_dhcp4_client_identifier(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t *ppwszDHCPClientIndentifier
)
{
    uint32_t dwError = 0;
    wstring_t pwszDHCPClientIndentifier = NULL;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !pwszIfname || !ppwszDHCPClientIndentifier)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_dhcp4_client_identifier_w(
                  hPMD,
                  pwszIfname,
                  &pwszDHCPClientIndentifier);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszDHCPClientIndentifier = pwszDHCPClientIndentifier;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (ppwszDHCPClientIndentifier)
    {
        *ppwszDHCPClientIndentifier = NULL;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_get_dhcp_mode(
    handle_t hBinding,
    wstring_t pwszIfname,
    unsigned32 *pDHCPMode
)
{
    uint32_t dwError = 0, nDHCPMode = 0;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !pDHCPMode || !pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_dhcp_mode_w(hPMD, pwszIfname, &nDHCPMode);
    BAIL_ON_PMD_ERROR(dwError);

    *pDHCPMode = nDHCPMode;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (pDHCPMode)
    {
        *pDHCPMode = 0;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_get_dhcp_client_iaid(
    handle_t hBinding,
    wstring_t pwszIfname,
    unsigned32 *pIaid
)
{
    uint32_t dwError = 0, dwIaid = 0;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !pwszIfname || !pIaid)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_dhcp_client_iaid_w(hPMD, pwszIfname, &dwIaid);
    BAIL_ON_PMD_ERROR(dwError);

    *pIaid = dwIaid;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (pIaid)
    {
        *pIaid = 0;
    }
    goto cleanup;
}


unsigned32
netmgr_rpc_get_link_mtu(
    handle_t hBinding,
    wstring_t pwszIfname,
    unsigned32 *pMtu
)
{
    uint32_t dwError = 0, mtu;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !pwszIfname || !pMtu)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_link_mtu_w(hPMD, pwszIfname, &mtu);
    BAIL_ON_PMD_ERROR(dwError);

    *pMtu = mtu;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (pMtu)
    {
        *pMtu = 0;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_set_link_state(
    handle_t hBinding,
    wstring_t pwszIfname,
    NET_RPC_LINK_STATE linkState
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_link_state_w(hPMD, pwszIfname, linkState);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_link_state(
    handle_t hBinding,
    wstring_t pwszIfname,
    NET_RPC_LINK_STATE *pLinkState
)
{
    uint32_t dwError = 0;
    NET_RPC_LINK_STATE linkState;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pLinkState)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_link_state_w(hPMD, pwszIfname, &linkState);
    BAIL_ON_PMD_ERROR(dwError);

    *pLinkState = linkState;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (pLinkState)
    {
        *pLinkState = RPC_LINK_STATE_UNKNOWN;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_ifup(
    handle_t hBinding,
    wstring_t pwszIfname
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_ifup_w(hPMD, pwszIfname);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_ifdown(
    handle_t hBinding,
    wstring_t pwszIfname
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_ifdown_w(hPMD, pwszIfname);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_link_info(
    handle_t hBinding,
    wstring_t pwszIfname,
    PNET_RPC_LINK_INFO_ARRAY *ppLinkInfoArray
)
{
    uint32_t dwError = 0;
    PNET_RPC_LINK_INFO_ARRAY pLinkInfoArray = NULL;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!ppLinkInfoArray)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_link_info_w(hPMD, pwszIfname, &pLinkInfoArray);
    BAIL_ON_PMD_ERROR(dwError);

    *ppLinkInfoArray = pLinkInfoArray;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}


/*
 * IP Address configuration APIs
 */
unsigned32
netmgr_rpc_set_ipv4_addr_gateway(
    handle_t hBinding,
    wstring_t pwszIfname,
    NET_RPC_IPV4_ADDR_MODE mode,
    wstring_t pwszIPv4AddrPrefix,
    wstring_t pwszIPv4Gateway
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_ipv4_addr_gateway_w(
                  hPMD,
                  pwszIfname,
                  mode,
                  pwszIPv4AddrPrefix,
                  pwszIPv4Gateway);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_ipv4_addr_gateway(
    handle_t hBinding,
    wstring_t pwszIfname,
    NET_RPC_IPV4_ADDR_MODE *pMode,
    wstring_t *ppwszIPv4AddrPrefix,
    wstring_t *ppwszIPv4Gateway
)
{
    uint32_t dwError = 0;
    NET_RPC_IPV4_ADDR_MODE mode = RPC_IPV4_ADDR_MODE_NONE;
    wstring_t pwszIPv4AddrPrefix = NULL, pwszIPv4Gateway = NULL;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname ||
        !pMode ||
        !ppwszIPv4AddrPrefix ||
        !ppwszIPv4Gateway)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_ipv4_addr_gateway_w(
                  hPMD,
                  pwszIfname,
                  &mode,
                  &pwszIPv4AddrPrefix,
                  &pwszIPv4Gateway);
    BAIL_ON_PMD_ERROR(dwError);

    *pMode = mode;
    *ppwszIPv4AddrPrefix = pwszIPv4AddrPrefix;
    *ppwszIPv4Gateway = pwszIPv4Gateway;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (pMode)
    {
        *pMode = RPC_IPV4_ADDR_MODE_NONE;
    }
    if (ppwszIPv4AddrPrefix)
    {
        *ppwszIPv4AddrPrefix = NULL;
    }
    if (ppwszIPv4Gateway)
    {
        *ppwszIPv4Gateway = NULL;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_add_static_ipv6_addr(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t pwszIPv6AddrPrefix
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname|| !pwszIPv6AddrPrefix)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_add_static_ipv6_addr_w(
                  hPMD,
                  pwszIfname,
                  pwszIPv6AddrPrefix);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_delete_static_ipv6_addr(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t pwszIPv6AddrPrefix
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname || !pwszIPv6AddrPrefix)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_delete_static_ipv6_addr_w(
                  hPMD,
                  pwszIfname,
                  pwszIPv6AddrPrefix);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_set_ipv6_addr_mode(
    handle_t hBinding,
    wstring_t pwszIfname,
    unsigned32 enableDhcp,
    unsigned32 enableAutoconf
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_ipv6_addr_mode_w(
                  hPMD,
                  pwszIfname,
                  enableDhcp,
                  enableAutoconf);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_ipv6_addr_mode(
    handle_t hBinding,
    wstring_t pwszIfname,
    unsigned32 *pDhcpEnabled,
    unsigned32 *pAutoconfEnabled
)
{
    uint32_t dwError = 0;
    uint32_t dhcpEnabled = 0;
    uint32_t autoconfEnabled = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_ipv6_addr_mode_w(
                  hPMD,
                  pwszIfname,
                  &dhcpEnabled,
                  &autoconfEnabled);
    BAIL_ON_PMD_ERROR(dwError);

    if (pDhcpEnabled)
    {
        *pDhcpEnabled = dhcpEnabled;
    }
    if (pAutoconfEnabled)
    {
        *pAutoconfEnabled = autoconfEnabled;
    }

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (pDhcpEnabled)
    {
        *pDhcpEnabled = 0;
    }
    if (pAutoconfEnabled)
    {
        *pAutoconfEnabled = 0;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_set_ipv6_gateway(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t pwszIPv6Gateway
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_ipv6_gateway_w(
                  hPMD,
                  pwszIfname,
                  pwszIPv6Gateway);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_ipv6_gateway(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t *ppwszIPv6Gateway
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;
    wstring_t pwszIPv6Gateway = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname || !ppwszIPv6Gateway)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_ipv6_gateway_w(
                  hPMD,
                  pwszIfname,
                  &pwszIPv6Gateway);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszIPv6Gateway = pwszIPv6Gateway;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (ppwszIPv6Gateway)
    {
        *ppwszIPv6Gateway = NULL;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_get_ip_addr(
    handle_t hBinding,
    wstring_t pwszIfname,
    unsigned32 addrTypes,
    NET_RPC_IP_ADDR_ARRAY **ppIpAddrArray
)
{
    uint32_t dwError = 0;
    size_t i, dwCount = 0;
    NET_RPC_IP_ADDR_ARRAY *pIpAddrArray = NULL;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!ppIpAddrArray)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_ip_addr_w(
                  hPMD,
                  pwszIfname,
                  addrTypes,
                  &pIpAddrArray);
    BAIL_ON_PMD_ERROR(dwError);

    *ppIpAddrArray = pIpAddrArray;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    if (ppIpAddrArray)
    {
        *ppIpAddrArray = NULL;
    }
    goto cleanup;
}


/*
 * Route configuration APIs
 */
unsigned32
netmgr_rpc_add_static_ip_route(
    handle_t hBinding,
    NET_RPC_IP_ROUTE *pIpRoute
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pIpRoute)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_add_static_ip_route_w(hPMD, pIpRoute);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    goto cleanup;
}

unsigned32
netmgr_rpc_delete_static_ip_route(
    handle_t hBinding,
    NET_RPC_IP_ROUTE *pIpRoute
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pIpRoute)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_delete_static_ip_route_w(hPMD, pIpRoute);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_static_ip_routes(
    handle_t hBinding,
    wstring_t pwszIfname,
    NET_RPC_IP_ROUTE_ARRAY **ppIpRouteArray
)
{
    uint32_t dwError = 0;
    size_t i, dwCount = 0;
    NET_RPC_IP_ROUTE_ARRAY *pIpRouteArray = NULL;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!ppIpRouteArray)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_static_ip_routes_w(
                  hPMD,
                  pwszIfname,
                  &pIpRouteArray);
    BAIL_ON_PMD_ERROR(dwError);

    *ppIpRouteArray = pIpRouteArray;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    if (ppIpRouteArray)
    {
        *ppIpRouteArray = NULL;
    }
    goto cleanup;
}


/*
 * DNS configuration APIs
 */
unsigned32
netmgr_rpc_add_dns_server(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t pwszDnsServer
)
{
    uint32_t i, dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszDnsServer)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_add_dns_server_w(
                  hPMD,
                  pwszIfname,
                  pwszDnsServer);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    goto cleanup;
}

unsigned32
netmgr_rpc_delete_dns_server(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t pwszDnsServer
)
{
    uint32_t i, dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszDnsServer)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_delete_dns_server_w(
                  hPMD,
                  pwszIfname,
                  pwszDnsServer);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    goto cleanup;
}

unsigned32
netmgr_rpc_set_dns_servers(
    handle_t hBinding,
    wstring_t pwszIfname,
    NET_RPC_DNS_MODE dwMode,
    PPMD_WSTRING_ARRAY pwszDnsServers
)
{
    uint32_t i, dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszDnsServers)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_dns_servers_w(
                  hPMD,
                  pwszIfname,
                  dwMode,
                  pwszDnsServers);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_dns_servers(
    handle_t hBinding,
    PPMD_WSTRING_ARRAY *ppwszDnsServers
)
{
    uint32_t dwError = 0;
    PPMD_WSTRING_ARRAY pwszDnsServers = NULL;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !ppwszDnsServers)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_dns_servers_w(
                  hPMD,
                  &pwszDnsServers);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszDnsServers = pwszDnsServers;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    if (ppwszDnsServers)
    {
        *ppwszDnsServers = NULL;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_add_dns_domain(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t pwszDnsDomain
)
{
    uint32_t i, dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszDnsDomain)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_add_dns_domain_w(
                  hPMD,
                  pwszIfname,
                  pwszDnsDomain);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    goto cleanup;
}

unsigned32
netmgr_rpc_delete_dns_domain(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t pwszDnsDomain
)
{
    uint32_t i, dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszDnsDomain)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_delete_dns_domain_w(
                  hPMD,
                  pwszIfname,
                  pwszDnsDomain);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    goto cleanup;
}

unsigned32
netmgr_rpc_set_dns_domains(
    handle_t hBinding,
    wstring_t pwszIfname,
    PPMD_WSTRING_ARRAY pwszDnsDomains
)
{
    uint32_t i, dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszDnsDomains)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_dns_domains_w(
                  hPMD,
                  pwszIfname,
                  pwszDnsDomains);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_dns_domains(
    handle_t hBinding,
    PPMD_WSTRING_ARRAY *ppwszDnsDomains
)
{
    uint32_t dwError = 0;
    PPMD_WSTRING_ARRAY pwszDnsDomains = NULL;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !ppwszDnsDomains)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_dns_domains_w(
                  hPMD,
                  &pwszDnsDomains);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszDnsDomains = pwszDnsDomains;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    if (ppwszDnsDomains)
    {
        *ppwszDnsDomains = NULL;
    }
    goto cleanup;
}


/*
 * DHCP options, DUID, IAID configuration APIs
 */
unsigned32
netmgr_rpc_set_iaid(
    handle_t hBinding,
    wstring_t pwszIfname,
    unsigned32 dwIaid
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_iaid_w(hPMD, pwszIfname, (uint32_t)dwIaid);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_iaid(
    handle_t hBinding,
    wstring_t pwszIfname,
    unsigned32 *pdwIaid
)
{
    uint32_t dwError = 0, iaid = 0;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !pwszIfname|| !pdwIaid)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_iaid_w(hPMD, pwszIfname, &iaid);
    BAIL_ON_PMD_ERROR(dwError);

    *pdwIaid = (unsigned32)iaid;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (pdwIaid)
    {
        *pdwIaid = 0;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_set_duid(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t pwszDuid
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_duid_w(hPMD, pwszIfname, pwszDuid);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_duid(
    handle_t hBinding,
    wstring_t pwszIfname,
    wstring_t *ppwszDuid
)
{
    uint32_t dwError = 0;
    wstring_t pwszDuid = NULL;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!ppwszDuid)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_duid_w(hPMD, pwszIfname, &pwszDuid);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszDuid = pwszDuid;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (ppwszDuid)
    {
        ppwszDuid = NULL;
    }
    goto cleanup;
}

uint32_t
netmgr_rpc_set_ntp_servers(
    handle_t hBinding,
    PPMD_WSTRING_ARRAY pwszNtpServers
    )
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszNtpServers)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_ntp_servers_w(
                  hPMD,
                  pwszNtpServers);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    goto cleanup;
}

uint32_t
netmgr_rpc_add_ntp_servers(
    handle_t hBinding,
    PPMD_WSTRING_ARRAY pwszNtpServers
    )
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszNtpServers)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_add_ntp_servers_w(
                  hPMD,
                  pwszNtpServers);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    goto cleanup;
}

uint32_t
netmgr_rpc_delete_ntp_servers(
    handle_t hBinding,
    PPMD_WSTRING_ARRAY pwszNtpServers
    )
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszNtpServers)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_delete_ntp_servers_w(
                  hPMD,
                  pwszNtpServers);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_addresses(
    handle_t hBinding,
    wstring_t pwszInterfaceName,
    PPMD_WSTRING_ARRAY *ppwszAddresses
    )
{
    uint32_t dwError = 0;
    PPMD_WSTRING_ARRAY pwszAddresses = NULL;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !ppwszAddresses || !pwszInterfaceName)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_addresses_w(hPMD, pwszInterfaceName, &pwszAddresses);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszAddresses = pwszAddresses;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    if (ppwszAddresses)
    {
        *ppwszAddresses = NULL;
    }
    goto cleanup;
}


unsigned32
netmgr_rpc_get_routes(
    handle_t hBinding,
    wstring_t pwszInterfaceName,
    PPMD_WSTRING_ARRAY *ppwszRoutes
    )
{
    uint32_t dwError = 0;
    PPMD_WSTRING_ARRAY pwszRoutes = NULL;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !ppwszRoutes || !pwszInterfaceName)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_routes_w(hPMD, pwszInterfaceName, &pwszRoutes);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszRoutes = pwszRoutes;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    if (ppwszRoutes)
    {
        *ppwszRoutes = NULL;
    }
    goto cleanup;
}


unsigned32
netmgr_rpc_get_ntp_servers(
    handle_t hBinding,
    wstring_t pwszInterfaceName,
    PPMD_WSTRING_ARRAY *ppwszNtpServers
    )
{
    uint32_t dwError = 0;
    PPMD_WSTRING_ARRAY pwszNtpServers = NULL;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !ppwszNtpServers || !pwszInterfaceName)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_ntp_servers_w(hPMD, pwszInterfaceName, &pwszNtpServers);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszNtpServers = pwszNtpServers;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    if (ppwszNtpServers)
    {
        *ppwszNtpServers = NULL;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_nft_get_tables(
    handle_t hBinding,
    wstring_t pwszFamily,
    wstring_t pwszTable,
    PPMD_WSTRING_ARRAY *ppwszNftables
    )
{
    uint32_t dwError = 0;
    PPMD_WSTRING_ARRAY pwszNftables = NULL;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !pwszFamily || !pwszTable || !ppwszNftables)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_nft_get_tables_w(hPMD, pwszFamily, pwszTable, &pwszNftables);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszNftables = pwszNftables;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    if (ppwszNftables)
    {
        *ppwszNftables = NULL;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_nft_get_chains(
    handle_t hBinding,
    wstring_t pwszFamily,
    wstring_t pwszTable,
    wstring_t pwszChains,
    PPMD_WSTRING_ARRAY *ppwszNftablesChains
    )
{
    uint32_t dwError = 0;
    PPMD_WSTRING_ARRAY pwszNftablesChains = NULL;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !pwszFamily || !pwszTable || !pwszChains || !ppwszNftablesChains)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_nft_get_chains_w(hPMD, pwszFamily, pwszTable, pwszChains, &pwszNftablesChains);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszNftablesChains = pwszNftablesChains;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;

error:
    if (ppwszNftablesChains)
    {
        *ppwszNftablesChains = NULL;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_get_nft_rules(
    handle_t hBinding,
    const wstring_t pwszTable,
    wstring_t *ppwszNftableRules
)
{
    uint32_t dwError = 0;
    wstring_t pwszNftableRules = NULL;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !pwszTable || !ppwszNftableRules)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_nft_rules_w(
                  hPMD,
                  pwszTable,
                  &pwszNftableRules);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszNftableRules = pwszNftableRules;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (ppwszNftableRules)
    {
        *ppwszNftableRules = NULL;
    }
    goto cleanup;
}

/*
 * Misc APIs
 */
unsigned32
netmgr_rpc_set_hostname(
    handle_t hBinding,
    wstring_t pwszHostname
    )
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszHostname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_hostname_w(hPMD, pwszHostname);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_hostname(
    handle_t hBinding,
    wstring_t *ppwszHostname
    )
{
    uint32_t dwError = 0;
    wstring_t pwszHostname = NULL;
    PPMDHANDLE hPMD = NULL;

    if (!hBinding || !ppwszHostname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    CHECK_RPC_ACCESS(hBinding, dwError);

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_hostname_w(hPMD, &pwszHostname);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszHostname = pwszHostname;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (ppwszHostname)
    {
        ppwszHostname = NULL;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_wait_for_link_up(
    handle_t hBinding,
    wstring_t pwszIfname,
    unsigned32 dwTimeout
    )
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_wait_for_link_up_w(
                  hPMD,
                  pwszIfname,
                  (uint32_t)dwTimeout);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_wait_for_ip(
    handle_t hBinding,
    wstring_t pwszIfname,
    unsigned32 dwTimeout,
    NET_RPC_ADDR_TYPE dwAddrTypes
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszIfname)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_wait_for_ip_w(
                  hPMD,
                  pwszIfname,
                  (uint32_t)dwTimeout,
                  dwAddrTypes);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_error_info(
    handle_t hBinding,
    unsigned32 nmErrCode,
    wstring_t *ppwszErrInfo
)
{
    uint32_t dwError = 0;
    wstring_t pwszErrInfo = NULL;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!ppwszErrInfo)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_error_info_w(
                  hPMD,
                  nmErrCode,
                  &pwszErrInfo);
    if (!pwszErrInfo)
    {
        dwError = ERROR_PMD_NO_DATA;
    }
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszErrInfo = pwszErrInfo;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (ppwszErrInfo)
    {
        ppwszErrInfo = NULL;
    }
    goto cleanup;
}

unsigned32
netmgr_rpc_set_network_param(
    handle_t hBinding,
    wstring_t pwszObjectName,
    wstring_t pwszParamName,
    wstring_t pwszParamValue
)
{
    uint32_t dwError = 0;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszObjectName || !pwszParamName)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_set_network_param_w(
                  hPMD,
                  pwszObjectName,
                  pwszParamName,
                  pwszParamValue);
    BAIL_ON_PMD_ERROR(dwError);

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    goto cleanup;
}

unsigned32
netmgr_rpc_get_network_param(
    handle_t hBinding,
    wstring_t pwszObjectName,
    wstring_t pwszParamName,
    wstring_t *ppwszParamValue
)
{
    uint32_t dwError = 0;
    wstring_t pwszParamValue = NULL;
    PPMDHANDLE hPMD = NULL;

    CHECK_RPC_ACCESS(hBinding, dwError);

    if (!pwszObjectName || !pwszParamName || !ppwszParamValue)
    {
        dwError = ERROR_PMD_INVALID_PARAMETER;
        BAIL_ON_PMD_ERROR(dwError);
    }

    dwError = rpc_open_privsep_internal(NET_PRIVSEP, &hPMD);
    BAIL_ON_PMD_ERROR(dwError);

    dwError = netmgr_client_get_network_param_w(
                  hPMD,
                  pwszObjectName,
                  pwszParamName,
                  &pwszParamValue);
    BAIL_ON_PMD_ERROR(dwError);

    *ppwszParamValue = pwszParamValue;

cleanup:
    rpc_free_handle(hPMD);
    return dwError;
error:
    if (ppwszParamValue)
    {
        ppwszParamValue = NULL;
    }
    goto cleanup;
}
