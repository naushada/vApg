#ifndef __REQUEST_ACK_ST_CC__
#define __REQUEST_ACK_ST_CC__
#include "RequestAckST.h"
#include "ace/Log_Msg.h"

RequestAckST *RequestAckST::m_instance = NULL;

static RequestAckST *RequestAckST::get_instance()
{
  ACE_TRACE("RequestAckST::get_instance");
  if(!m_instance)
  {
    m_instance = new RequestAckST();
  }

  return(m_instance);
}

void RequestAckST::onEntry(DHCP::Server *parent)
{
  ACE_TRACE("RequestAckST::onEntry");
}

void RequestAckST::onExit(DHCP::Server *parent)
{
  ACE_TRACE("RequestAckST::onExit");
}

ACE_UINT32 RequestAckST::offer(DHCP::Server *parent)
{
  ACE_TRACE("RequestAckST::offer");
  return(0);
}

ACE_UINT32 RequestAckST::discover(DHCP::Server *parent)
{
  ACE_TRACE("RequestAckST::discover");
  return(0);
}

ACE_UINT32 RequestAckST::request(DHCP::Server *parent)
{
  ACE_TRACE("RequestAckST::request");
  return(0);
}

ACE_UINT32 RequestAckST::requestAck(DHCP::Server *parent)
{
  ACE_TRACE("RequestAckST::requestAck");
  return(0);
}

ACE_UINT32 RequestAckST::leaseTO(DHCP::Server *parent)
{
  ACE_TRACE("RequestAckST::leaseTO");
  return(0);
}

#endif /*__REQUEST_ACK_ST_CC__*/
