#ifndef __IPC_CC__
#define __IPC_CC__

#include <ace/Reactor.h>
#include <ace/Basic_Types.h>
#include <ace/Event_Handler.h>
#include <ace/Task.h>
#include <ace/INET_Addr.h>
#include <ace/UNIX_Addr.h>
#include <ace/SOCK_Dgram.h>
#include <ace/LSOCK_CODgram.h>
#include <ace/LSOCK_Dgram.h>
#include <ace/Task_T.h>
#include <ace/UNIX_Addr.h>
#include <ace/Timer_Queue_T.h>

#include "ipc.h"

IPC_::~IPC_()
{
}

IPC_::IPC_()
{
  m_magic = 0x00000000;
  m_handle = -1;

}

IPC_::IPC_(char *ipAddr, ACE_UINT8 cont, ACE_UINT8 com,
           ACE_UINT8 fac, ACE_UINT8 ins)
{
  do
  {

    ACE_CString addr(ipAddr);
    ACE_UINT32 taskId = cont << 24 |
                        com  << 16 |
                        fac  << 8  |
                        ins  << 0 ;

    m_ipAddr = addr;

    ipcPort(taskId);
    container(cont);
    component(com);
    facility(fac);
    instance(ins);

    m_ipcAddr.set_port_number(ipcPort());
    m_ipcAddr.set_address(m_ipAddr.rep(), m_ipAddr.length());

    if(m_dgram.open(m_ipcAddr, 1) < 0)
    {
      ACE_ERROR((LM_ERROR, "IPC Socket Creation Failed for 0x%X", m_ipcPort));
      break;
    }

    handle(m_dgram.get_handle());
    ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::READ_MASK);

  }while(0);

}

void IPC_::ipcPort(ACE_UINT32 port)
{
  m_ipcPort = port;
}

ACE_UINT32 IPC_::ipcPort(void)
{
  return(m_ipcPort);
}

void IPC_::container(ACE_UINT8 container)
{
  m_container = container;
}

ACE_UINT8 IPC_::container(void)
{
  return(m_container);
}

void IPC_::facility(ACE_UINT8 fac)
{
  m_facility = fac;
}

ACE_UINT8 IPC_::facility(void)
{
  return(m_facility);
}

void IPC_::component(ACE_UINT8 component)
{
  m_component = component;
}

ACE_UINT8 IPC_::component(void)
{
  return(m_component);
}

void IPC_::instance(ACE_UINT8 instance)
{
  m_instance = instance;
}

ACE_UINT8 IPC_::instance(void)
{
  return(m_instance);
}

void IPC_::handle(ACE_HANDLE handle)
{
  m_handle = handle;
}

ACE_HANDLE IPC_::handle(void)
{
  return(m_handle);
}

/*
 * @brief  This is the hook method of ACE Event Handler and is called by ACE Framework to retrieve the
 *         handle. The handle is nothing but it's fd - file descriptor.
 * @param  none
 * @return handle of type ACE_HANDLE
 */
ACE_HANDLE IPC_::get_handle(void) const
{
  return(const_cast<IPC_ *>(this)->handle());
}

/*
 * @brief  This is the hook method for application to define this member function and is invoked by 
 *         ACE Framework.
 * @param  handle in which read/recv/recvfrom to be called.
 * @return 0 for success else for failure.
 */
ACE_INT32 IPC_::handle_input(ACE_HANDLE handle)
{
  char buff[1500];
  size_t max_len = sizeof(buff);
  size_t recv_len = -1;
  taskIdToPeerMapIter_t iter;

  memset((void *)buff, 0, sizeof(buff));

  /*UDP socket for IPC.*/
  ACE_INET_Addr peer;
  do
  {
    if((recv_len = m_dgram.recv(buff, max_len, peer)) < 0)
    {
      ACE_ERROR((LM_ERROR, "Receive from peer 0x%X Failed\n", peer.get_port_number()));
      break;
    }

    /*! peer is remembered and shall be used while sending response to it.*/

    /* +--------------+--------------+------------+-----------+-------------------+
     * | srctaskId(4) | dstTaskId(4) | version(4) | length(4) | payload of length |
     * +--------------+--------------+------------+-----------+-------------------+
     * */
    processRequest((ACE_UINT8 *)buff, recv_len);

  }while(0);

  return(0);
}

ACE_UINT32 IPC_::getMyTaskId(void)
{
  return(m_ipcPort);
}

/*
 * @brief  This is the hook method for application to process the timer expiry. This is invoked by
 *         ACE Framework upon expiry of timer.
 * @param  tv in sec and usec.
 * @param  argument which was passed while starting the timer.
 * @return 0 for success else for failure.
 */
ACE_INT32 Timer_::handle_timeout(ACE_Time_Value &tv, const void *arg)
{
  /*!Delete this entry from list*/
  std::list<_timerToken_t *>::iterator it;

  for(it = m_timerTokenList.begin(); it != m_timerTokenList.end(); it++)
  {
    _timerToken_t *tt = *it;
    if(arg == tt->act())
    {
      /*! Remove this element from list.*/
      m_timerTokenList.erase(it);
      free(tt);
      break;
    }
  }

  processTimeout(arg);
  return(0);
}

long Timer_::startTimer(ACE_Time_Value &delay,
                        const void *act,
                        ACE_Time_Value interval = ACE_Time_Value::zero)
{
  long tId;
  do
  {
    _timerToken_t *tt = new _timerToken();
    tId = ACE_Reactor::instance()->schedule_timer(dynamic_cast<Timer_*>(this),
                                                      reinterpret_cast<const void *>(tt),
                                                      delay,
                                                      interval/*After this interval, timer will be started automatically.*/);
    tt->timerId(tId);
    tt->act(act);

    /*! Insert element into the list at back.*/
    m_timerTokenList.push_back(tt);

  }while(0);

  return(tId);
}

void Timer_::stopTimer(long tId)
{
  std::list<_timerToken_t *>::iterator it;

  for(it = m_timerTokenList.begin(); it != m_timerTokenList.end(); it++)
  {
    _timerToken_t *tt = *it;

    if(tId == tt->timerId())
    {
      /*! Remove this element from list.*/
      m_timerTokenList.erase(it);
      free(tt);
      break;
    }
  }

  ACE_Reactor::instance()->cancel_timer(tId);
}

ACE_INT32 Timer_::processTimeout(const void *act)
{
  /*! Derived class function should have been called.*/
  return(0);
}

Timer_::Timer_()
{
  /*! Make the list empty now.*/
  m_timerTokenList.clear();
}

























#endif /*__IPC_CC__*/
