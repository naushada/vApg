#ifndef __DHCP_SERVER_STATE_LEASE_EXPIRE__CC__
#define __DHCP_SERVER_STATE_LEASE_EXPIRE__CC__

#include "DhcpServerStateLeaseExpire.h"
#include "ace/Log_Msg.h"

LeaseTOST *LeaseTOST::m_instance = NULL;

static LeaseTOST *LeaseTOST::instance()
{
  ACE_TRACE("LeaseTOST::instance");
  if(!m_instance)
  {
    m_instance = new LeaseTOST();
  }

  return(m_instance);
}

void LeaseTOST::onEntry(DHCP::Server *parent)
{
  ACE_TRACE("LeaseTOST::onEntry");
}

void LeaseTOST::onExit(DHCP::Server *parent)
{
  ACE_TRACE("LeaseTOST::onExit");
}

ACE_UINT32 LeaseTOST::offer(DHCP::Server *parent)
{
  ACE_TRACE("LeaseTOST::offer");
  return(0);
}

ACE_UINT32 LeaseTOST::discover(DHCP::Server *parent)
{
  ACE_TRACE("LeaseTOST::discover");
  return(0);
}

ACE_UINT32 LeaseTOST::request(DHCP::Server *parent)
{
  ACE_TRACE("LeaseTOST::request");
  return(0);
}

ACE_UINT32 LeaseTOST::requestAck(DHCP::Server *parent)
{
  ACE_TRACE("LeaseTOST::requestAck");
  return(0);
}

ACE_UINT32 LeaseTOST::leaseTO(DHCP::Server *parent)
{
  ACE_TRACE("LeaseTOST::leaseTO");
  return(0);
}



#endif /*__DHCP_SERVER_STATE_LEASE_EXPIRE__CC__*/
