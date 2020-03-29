#ifndef __LEASETO_ST_CC__
#define __LEASETO_ST_CC__
#include "LeaseTOST.h"
#include "ace/Log_Msg.h"

LeaseTOST *LeaseTOST::m_instance = NULL;

static LeaseTOST *LeaseTOST::get_instance()
{
  ACE_TRACE("LeaseTOST::get_instance");
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



#endif /*__LEASETO_ST_CC__*/
