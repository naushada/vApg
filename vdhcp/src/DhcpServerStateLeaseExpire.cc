#ifndef __DHCP_SERVER_STATE_LEASE_EXPIRE__CC__
#define __DHCP_SERVER_STATE_LEASE_EXPIRE__CC__

#include "DhcpServerStateLeaseExpire.h"
#include "ace/Log_Msg.h"

DhcpServerStateLeaseExpire *DhcpServerStateLeaseExpire::m_instance = NULL;

DhcpServerStateLeaseExpire *DhcpServerStateLeaseExpire::instance()
{
  ACE_TRACE("DhcpServerStateLeaseExpire::instance");
  if(!m_instance)
  {
    m_instance = new DhcpServerStateLeaseExpire();
  }

  return(m_instance);
}

void DhcpServerStateLeaseExpire::onEntry(DHCP::Server &parent)
{
  ACE_TRACE("DhcpServerStateLeaseExpire::onEntry");
  /*A timer shall be started for leaseExpiry.*/
}

void DhcpServerStateLeaseExpire::onExit(DHCP::Server &parent)
{
  ACE_TRACE("DhcpServerStateLeaseExpire::onExit");
}

ACE_UINT32 DhcpServerStateLeaseExpire::offer(DHCP::Server &parent)
{
  ACE_TRACE("DhcpServerStateLeaseExpire::offer");
  return(0);
}

ACE_UINT32 DhcpServerStateLeaseExpire::discover(DHCP::Server &parent)
{
  ACE_TRACE("DhcpServerStateLeaseExpire::discover");
  return(0);
}

ACE_UINT32 DhcpServerStateLeaseExpire::request(DHCP::Server &parent)
{
  ACE_TRACE("DhcpServerStateLeaseExpire::request");
  return(0);
}

ACE_UINT32 DhcpServerStateLeaseExpire::requestAck(DHCP::Server &parent)
{
  ACE_TRACE("DhcpServerStateLeaseExpire::requestAck");
  return(0);
}

ACE_UINT32 DhcpServerStateLeaseExpire::leaseTO(DHCP::Server &parent)
{
  ACE_TRACE("DhcpServerStateLeaseExpire::leaseTO");
  return(0);
}

DhcpServerStateLeaseExpire::DhcpServerStateLeaseExpire()
{
  ACE_TRACE("DhcpServerStateLeaseExpire::DhcpServerStateLeaseExpire\n");
}

DhcpServerStateLeaseExpire::~DhcpServerStateLeaseExpire()
{
  ACE_TRACE("DhcpServerStateLeaseExpire::~DhcpServerStateLeaseExpire\n");
}
#endif /*__DHCP_SERVER_STATE_LEASE_EXPIRE__CC__*/
