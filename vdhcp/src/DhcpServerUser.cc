#ifndef __DHCP_SERVER_USER_CC__
#define __DHCP_SERVER_USER_CC__

#include "ace/Basic_Types.h"
#include "ace/Log_Msg.h"
#include "ace/Reactor.h"

#include "DhcpServerUser.h"
#include "commonIF.h"
#include "DhcpServer.h"

ACE_UINT8 DhcpServerUser::isSubscriberFound(ACE_CString macAddress)
{
  if(m_instMap.find(macAddress) == -1)
  {
    ACE_DEBUG((LM_ERROR, "This client %s is not found\n", macAddress.c_str()));
    return(0);
  }

  return(1);
}

ACE_UINT8 DhcpServerUser::createSubscriber(ACE_CString macAddress)
{

  DHCP::Server *sess = NULL;
  ACE_NEW_NORETURN(sess, DHCP::Server());
  /*let STL do the memory management for stack object.*/
  m_instMap.bind(macAddress, sess);

  return(0);
}

ACE_UINT8 DhcpServerUser::addSubscriber(DHCP::Server *sess, ACE_CString macAddress)
{
  /*let STL do the memory management for stack object.*/
  m_instMap.bind(macAddress, sess);

  return(0);
}

DHCP::Server *DhcpServerUser::getSubscriber(ACE_CString macAddress)
{
  DHCP::Server *sess = NULL;
  if(m_instMap.find(macAddress, sess) == -1)
  {
    ACE_DEBUG((LM_ERROR, "No session for client %s is found\n", macAddress.c_str()));
  }

  return(sess);
}

ACE_UINT32 DhcpServerUser::processRequest(ACE_Byte *in, ACE_UINT32 inLen)
{
   /*This is a DHCP Message.*/
   TransportIF::DHCP *dhcpHdr = (TransportIF::DHCP *)&in[sizeof(TransportIF::ETH) +
                                                         sizeof(TransportIF::IP) +
                                                         sizeof(TransportIF::UDP)];

   ACE_CString haddr((const char *)dhcpHdr->chaddr, TransportIF::ETH_ALEN);
   ACE_DEBUG((LM_DEBUG, "%I chaddr is %s\n", haddr.c_str()));

   if(isSubscriberFound(haddr))
   {
     ACE_DEBUG((LM_INFO, "%I chaddr (%s) is found\n", haddr.c_str()));
     DHCP::Server *sess = getSubscriber(haddr);
     sess->getState().rx(*sess, in, inLen);
   }
   else
   {
     DHCP::Server *sess = NULL;
     ACE_NEW_NORETURN(sess, DHCP::Server(this));

     addSubscriber(sess, haddr);
     sess->getState().rx(*sess, in, inLen);
   }

   return(0);
}

/*
 * @brief  This is the hook method for application to process the timer expiry. This is invoked by
 *         ACE Framework upon expiry of timer.
 * @param  tv in sec and usec.
 * @param  argument which was passed while starting the timer.
 * @return 0 for success else for failure.
 */
ACE_INT32 DhcpServerUser::handle_timeout(ACE_Time_Value &tv, const void *arg)
{
  ACE_TRACE(("DhcpServerUser::handle_timeout\n"));
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
long DhcpServerUser::start_timer(ACE_UINT32 to,
                                 const void *act,
                                 ACE_Time_Value interval)
{
  ACE_TRACE(("DhcpServerUser::start_timer\n"));
  ACE_Time_Value delay(to);
  long tid = 0;

  tid = ACE_Reactor::instance()->schedule_timer(this,
                                                act,
                                                delay,
                                                interval/*After this interval, timer will be started automatically.*/);

  /*Timer Id*/
  return(tid);
}

long DhcpServerUser::guardTid(void)
{
  return(m_guardTid);
}

void DhcpServerUser::guardTid(long gTid)
{
  m_guardTid = gTid;
}

long DhcpServerUser::leaseTid(void)
{
  return(m_leaseTid);
}

void DhcpServerUser::leaseTid(long lTid)
{
  m_leaseTid = lTid;
}

void DhcpServerUser::stop_timer(long tId)
{
  ACE_TRACE(("DhcpServerUser::stop_timer\n"));
  ACE_Reactor::instance()->cancel_timer(tId);
}

ACE_INT32 DhcpServerUser::process_timeout(const void *act)
{
  ACE_TRACE("DhcpServerUser::process_timeout\n");
  TIMER_ID *timerId = (TIMER_ID *)act;

  DHCP::Server *sess = NULL;
  ACE_CString cha((const char *)timerId->chaddr());
  if(m_instMap.find(cha, sess) != -1)
  {
    switch(timerId->timerType())
    {
    case DHCP::EXPECTED_REQUEST_GUARD_TIMER_ID:
      ACE_DEBUG((LM_DEBUG, "EXPECTED_REQUEST_GUARD_TIMER_ID is expired\n"));
      /*Kick the state machine.*/
      sess->getState().guardTimerExpiry(*sess, (const void *)act);
      //m_instMap.unbind(cha);
      delete sess;
      break;
    case DHCP::LEASE_GUARD_TIMER_ID:
      ACE_DEBUG((LM_DEBUG, "LEASE_GUARD_TIMER_ID is expired\n"));
      /*Kick the state machine.*/
      sess->getState().leaseTimerExpiry(*sess, (const void *)act);
      break;
    default:
      break;
    }
  }
  return(0);
}



#endif /*__DHCP_SERVER_USER_CC__*/
