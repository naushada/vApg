#ifndef __DHCP_SERVER_CC__
#define __DHCP_SERVER_CC__

#include "ace/Reactor.h"
#include "ace/Event_Handler.h"
#include "ace/SString.h"
#include "ace/SOCK_Dgram.h"
#include "server.h"
#include "ace/Log_Msg.h"

DHCP::Server::~Server()
{
  ACE_TRACE("DHCP::~Server\n");
}

void DHCP::Server::setState(DhcpServerState *st)
{
  ACE_TRACE("DHCP::Server::setState\n");

  if(m_state)
  {
    m_state->onExit(this);
  }

  m_state = st;
  m_state.onEntry(this);
}

DhcpServerState *DHCP::Server::getState(void)
{
  ACE_TRACE("DHCP::Server::getState\n");
  return(m_state);
}

void DHCP::Server::xid(ACE_UINT32 xid)
{
  m_xid = xid;
}

ACE_UINT32 DHCP::Server::xid(void)
{
  return(m_xid);
}

ACE_INT32 DHCP::Server::process_timeout(const void *act)
{
  return(0);
}


ACE_INT32 DHCP::Server::start()
{
  ACE_TRACE("DHCP::Server::start\n");
#if 0
  ACE_Reactor::instance()->register_handler(this,
                                            ACE_Event_Handler::READ_MASK |
                                            ACE_Event_Handler::TIMER_MASK);
#endif
  return(0);
}

ACE_INT32 DHCP::Server::stop()
{
  ACE_TRACE("DHCP::Server::stop\n");
  return(0);
}

#endif /*__DHCP_SERVER_CC__*/
