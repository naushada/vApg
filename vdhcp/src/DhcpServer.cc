#ifndef __DHCP_SERVER_CC__
#define __DHCP_SERVER_CC__

#include "ace/Reactor.h"
#include "ace/Event_Handler.h"
#include "ace/SString.h"
#include "ace/SOCK_Dgram.h"
#include "ace/Log_Msg.h"

#include "DhcpServer.h"
#include "DhcpServerStateDiscover.h"

/*
 * @brief  This is the hook method for application to process the timer expiry. This is invoked by
 *         ACE Framework upon expiry of timer.
 * @param  tv in sec and usec.
 * @param  argument which was passed while starting the timer.
 * @return 0 for success else for failure.
 */
ACE_INT32 DHCP::Server::handle_timeout(ACE_Time_Value &tv, const void *arg)
{
  ACE_TRACE(("UniTimer::handle_timeout"));
  process_timeout(arg);
  return(0);
}

/*
 * @brief this member function is invoked to start the timer.
 * @param This is the duration for timer.
 * @param This is the argument passed by caller.
 * @param This is to denote the preodicity whether this timer is going to be periodic or not.
 * @return timer_id is return.
 * */
long DHCP::Server::start_timer(ACE_UINT32 to,
                               const void *act,
                               ACE_Time_Value interval)
{
  ACE_TRACE(("UniTimer::start_timer"));
  ACE_Time_Value delay(to);
  long tid = 0;

  tid = ACE_Reactor::instance()->schedule_timer(this,
                                                act,
                                                delay,
                                                interval/*After this interval, timer will be started automatically.*/);

  /*Timer Id*/
  return(tid);
}

long DHCP::Server::guardTid(void)
{
  return(m_guardTid);
}

void DHCP::Server::guardTid(long gTid)
{
  m_guardTid = gTid;
}

long DHCP::Server::leaseTid(void)
{
  return(m_leaseTid);
}

void DHCP::Server::leaseTid(long lTid)
{
  m_leaseTid = lTid;
}

void DHCP::Server::stop_timer(long tId)
{
  ACE_TRACE((UniTimer::stop_timer));
  ACE_Reactor::instance()->cancel_timer(tId);
}

DHCP::Server::Server()
{
  /*context of DHCP Client's dhcp-header.*/
  m_ctx = new RFC2131::DhcpCtx();

  /*The start state is Discover.*/
  setState(DhcpServerStateDiscover::instance());
}

DHCP::Server::~Server()
{
  ACE_TRACE("DHCP::Server::~Server\n");
  delete m_ctx;
  m_ctx = NULL;
}

void DHCP::Server::setState(DhcpServerState *st)
{
  ACE_TRACE("DHCP::Server::setState\n");

  if(m_state)
  {
    m_state->onExit(*this);
  }

  m_state = st;
  m_state->onEntry(*this);
}

DhcpServerState &DHCP::Server::getState(void)
{
  ACE_TRACE("DHCP::Server::getState\n");
  return(*m_state);
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
  ACE_TRACE("DHCP::Server::process_timeout\n");
  DHCP::TIMER_ID *timerId = (DHCP::TIMER_ID *)act;

  switch(timerId->timerType())
  {
  case DHCP::EXPECTED_REQUEST_GUARD_TIMER_ID:
    ACE_DEBUG((LM_DEBUG, "EXPECTED_REQUEST_GUARD_TIMER_ID is expired\n"));
    /*Kick the state machine.*/
    getState().guardTimerExpiry(*this, (const void *)act);
    break;
  case LEASE_GUARD_TIMER_ID:
    ACE_DEBUG((LM_DEBUG, "LEASE_GUARD_TIMER_ID is expired\n"));
    /*Kick the state machine.*/
    getState().leaseTimerExpiry(*this, (const void *)act);
    break;
  default:
    break;
  }
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
