#ifndef __DHCP_SERVER_CC__
#define __DHCP_SERVER_CC__

#include "ace/Reactor.h"
#include "ace/Event_Handler.h"
#include "ace/SString.h"
#include "ace/SOCK_Dgram.h"
#include "ace/Log_Msg.h"

#include "DhcpServer.h"
#include "DhcpServerStateInit.h"

//DHCP::Server(CPGateway *parent)
DHCP::Server::Server()
{
  //m_parent = parent;
  /*context of DHCP Client's dhcp-header.*/
  m_ctx = new RFC2131::DhcpCtx();
  setState(DhcpServerStateInit::instance());
}

DHCP::Server::~Server()
{
  ACE_TRACE("DHCP::~Server\n");
  delete m_ctx;
  m_ctx = NULL;
}

void DHCP::Server::setState(DhcpServerState *st)
{
  ACE_TRACE("DHCP::Server::setState\n");

  if(m_state)
  {
    m_state->onExit(this);
  }

  m_state = st;
  m_state->onEntry(this);
}

DhcpServerState *DHCP::Server::getState(void)
{
  ACE_TRACE("DHCP::Server::getState\n");
  return(m_state);
}

void DHCP::Server::xid(ACE_UINT32 xid)
{
  m_ctx->xid(xid);
}

ACE_UINT32 DHCP::Server::xid(void)
{
  return(m_ctx->xid());
}

ACE_INT32 DHCP::Server::process_timeout(const void *act)
{
  return(0);
}

RFC2131::DhcpCtx &DHCP::Server::ctx(void)
{
  return(*m_ctx);
}

DHCP::ElemDef &DHCP::Server::optionMap(void)
{
  return(*m_optionMap);
}

ACE_UINT32 DHCP::Server::start()
{
  ACE_TRACE("DHCP::Server::start\n");
#if 0
  ACE_Reactor::instance()->register_handler(this,
                                            ACE_Event_Handler::READ_MASK |
                                            ACE_Event_Handler::TIMER_MASK);
#endif
  return(0);
}

ACE_UINT32 DHCP::Server::stop()
{
  ACE_TRACE("DHCP::Server::stop\n");
  return(0);
}

#endif /*__DHCP_SERVER_CC__*/
