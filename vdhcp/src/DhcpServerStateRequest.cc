#ifndef __DHCP_SERVER_STATE_REQUEST_CC__
#define __DHCP_SERVER_STATE_REQUEST_CC__

#include "DhcpServerStateLeaseExpire.h"
#include "DhcpServerStateRequest.h"
#include "DhcpServer.h"
#include "ace/Log_Msg.h"

DhcpServerStateRequest *DhcpServerStateRequest::m_instance = NULL;

DhcpServerStateRequest *DhcpServerStateRequest::instance()
{
  ACE_TRACE("DhcpServerStateRequest::instance\n");
  if(!m_instance)
  {
    m_instance = new DhcpServerStateRequest();
  }

  return(m_instance);
}

DhcpServerStateRequest::DhcpServerStateRequest()
{
  ACE_TRACE("DhcpServerStateRequest::instance\n");
  ACE_CString desc("DhcpServerStateRequest");
  m_description = desc;
}

DhcpServerStateRequest::~DhcpServerStateRequest()
{
}

void DhcpServerStateRequest::onEntry(DHCP::Server &parent)
{
  ACE_TRACE("DhcpServerStateRequest::onEntry\n");

  /*2 seconds.*/
  ACE_UINT32 to = 2;

  DHCP::TIMER_ID *act = new DHCP::TIMER_ID();
  act->timerType(DHCP::EXPECTED_REQUEST_GUARD_TIMER_ID);
  act->chaddrLen(parent.ctx().chaddrLen());
  ACE_OS::memcpy((void *)act->chaddr(), (const void *)parent.ctx().chaddr(),
                 parent.ctx().chaddrLen());


  parent.guardTid(parent.start_timer(to, (const void *)act));
}

void DhcpServerStateRequest::onExit(DHCP::Server &parent)
{
  ACE_TRACE("DhcpServerStateRequest::onExit\n");
}

ACE_UINT32 DhcpServerStateRequest::offer(DHCP::Server &parent, ACE_Byte *in, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerStateRequest::offer\n");
  return(0);
}

ACE_UINT32 DhcpServerStateRequest::discover(DHCP::Server &parent, ACE_Byte *in, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerStateRequest::discover\n");
  return(0);
}

ACE_UINT32 DhcpServerStateRequest::request(DHCP::Server &parent, ACE_Byte *in, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerStateRequest::request\n");

  parent.stop_timer(parent.guardTid());

  /*Prepare Request ACK.*/
  ACE_Message_Block &mb = buildResponse(parent, in, inLen);

  /*Move to next State.*/
  parent.setState(DhcpServerStateLeaseExpire::instance());
  return(0);
}

ACE_UINT32 DhcpServerStateRequest::requestAck(DHCP::Server &parent, ACE_Byte *in, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerStateRequest::requestAck\n");
  return(0);
}

ACE_UINT32 DhcpServerStateRequest::leaseTO(DHCP::Server &parent, ACE_Byte *in, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerStateRequest::leaseTO\n");
  return(0);
}

/*Guard Timer is stared if next request is expected to complete the Flow.*/
ACE_UINT32 DhcpServerStateRequest::guardTimerExpiry(DHCP::Server &parent, const void *act)
{
  ACE_TRACE("DhcpServerStateRequest::guardTimerExpiry\n");
  DHCP::TIMER_ID *tObj = (DHCP::TIMER_ID *)act;

  return(0);
}

/*lease Timer is started when IP address assignment is done successfully.*/
ACE_UINT32 DhcpServerStateRequest::leaseTimerExpiry(DHCP::Server &parent, const void *act)
{
  ACE_TRACE("DhcpServerStateRequest::leaseTimerExpiry\n");
  return(0);
}

#endif /*__DHCP_SERVER_STATE_REQUEST_CC__*/
