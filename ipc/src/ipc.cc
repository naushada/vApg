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

#include "commonIF.h"
#include "ipc.h"

IPC_::~IPC_()
{
	m_magic = 0x00000000;
}

IPC_::IPC_()
{
  m_magic = 0x00000000;
  m_handle = -1;
  m_ipcAddr.set("");
  m_facility = 0;
  m_instance = 0;
  m_ipcPort = 0;
  m_ipAddr = 0;
  m_taskIdToPeerUMap.clear();

}

IPC_::IPC_(ACE_CString ipAddr, ACE_UINT8 fac,
           ACE_UINT8 ins, ACE_CString node_tag)
{
  do
  {
    ACE_TRACE("IPC_::IPC_");

    selfProcId(CommonIF::get_hash32(reinterpret_cast<const ACE_UINT8 *>(node_tag.c_str())));
    m_nodeTag = node_tag;


    selfTaskId(CommonIF::get_task_id(fac, ins));
    m_ipAddr = ipAddr;

    ipcPort(CommonIF::get_ipc_port(fac, ins));
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

}/*IPC_*/

void IPC_::ipcPort(ACE_UINT32 port)
{
  m_ipcPort = port;
}

ACE_UINT32 IPC_::ipcPort(void)
{
  return(m_ipcPort);
}

void IPC_::facility(ACE_UINT8 fac)
{
  m_facility = fac;
}

ACE_UINT8 IPC_::facility(void)
{
  return(m_facility);
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

ACE_UINT32 IPC_::get_self_taskId(void)
{
  return(m_selfTaskId);
}

void IPC_::nodeTag(ACE_CString node_tag)
{
  m_nodeTag = node_tag;
}

ACE_CString IPC_::nodeTag(void)
{
  return(m_nodeTag);
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
  ACE_Message_Block *mb;
  size_t recv_len = -1;

  ACE_NEW_RETURN(mb, ACE_Message_Block(CommonIF::SIZE_64MB), -1);

  /*UDP socket for IPC.*/
  ACE_INET_Addr peer;
  do
  {
	  memset((void *)mb->rd_ptr(), 0, (CommonIF::SIZE_64MB * sizeof(char)));
    if((recv_len = m_dgram.recv(mb->rd_ptr(), (CommonIF::SIZE_64MB * sizeof(char)), peer)) < 0)
    {
      ACE_ERROR((LM_ERROR, "Receive from peer 0x%X Failed\n", peer.get_port_number()));
      break;
    }

    mb->rd_ptr(recv_len);
    /*! peer is remembered and shall be used while sending response to it.*/

    /* +--------------+--------------+---------------+--------------+------------+-----------+-------------------+
     * |dstProcId(4)  | dsttaskId(4) | srcProcId(4)  | srcTaskId(4) | version(4) | length(4) | payload of length |
     * +--------------+--------------+---------------+--------------+------------+-----------+-------------------+
     * */
    handle_ipc((ACE_UINT8 *)mb->rd_ptr(), mb->length());

  }while(0);

  return(0);
}

ACE_UINT32 IPC_::get_self_procId(void)
{
	return(m_selfProcId);
}

void IPC_::selfProcId(ACE_UINT32 selfProcId)
{
	m_selfProcId = selfProcId;
}

/*
 * @brief
 * @param dstProcId is the destination ProcId which is hash32 of processor ID/Node ID
 * @param
 * @param
 * @param
 * @return
 * */
ACE_UINT32 IPC_::send_ipc(ACE_UINT32 dstProcId, ACE_UINT8 dstEntity,
		                  ACE_UINT8 dstInst, ACE_UINT8 *req,
						  ACE_UINT32 reqLen, const char* ipAddr,
						  ACE_UINT16 sendPort)
{
	ACE_Message_Block *mb;

	do
	{
	  if(dstProcId == get_self_procId())
	  {
        /*data to be sent to different Node/Processor.*/
	  }
	}while(0);

#if 0
	ACE_UINT32 srcTaskId;
    ACE_Addr peerAddr;

    ACE_NEW_NORETURN(mb, ACE_Message_Block(IPC_RECV_SIZE_64M));

    mb->wr_ptr() = *((ACE_UINT32 *)procId);
    mb->wr_ptr(sizeof(ACE_UINT32));

    mb->wr_ptr() = *((ACE_UINT32 *)&req[4]);
    mb->wr_ptr(sizeof(ACE_UINT32));

	dstProcId = *((ACE_UINT32 *)req);
	dstTaskId = *((ACE_UINT32 *)&req[4]);
#endif

	return(reqLen);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * Timer API definition
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 * @brief  This is the hook method for application to process the timer expiry. This is invoked by
 *         ACE Framework upon expiry of timer.
 * @param  tv in sec and usec.
 * @param  argument which was passed while starting the timer.
 * @return 0 for success else for failure.
 */
ACE_INT32 Timer_::handle_timeout(ACE_Time_Value &tv, const void *arg)
{
  ACE_TRACE(("Timer_::handle_timeout"));
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
long Timer_::start_timer(ACE_UINT32 to,
                         const void *act,
                         ACE_Time_Value interval = ACE_Time_Value::zero)
{
  ACE_TRACE(("Timer_::start_timer"));
  ACE_Time_Value delay(to);

  return(ACE_Reactor::instance()->schedule_timer(this,
                                                 act,
                                                 delay,
                                                 interval/*After this interval, timer will be started automatically.*/));
}

void Timer_::stop_timer(long tId)
{
  ACE_TRACE((Timer_::stop_timer));
  ACE_Reactor::instance()->cancel_timer(tId);
}

ACE_INT32 Timer_::process_timeout(const void *act)
{
  /*! Derived class function should have been called.*/
  return(0);
}

Timer_::Timer_()
{
}

Timer_::~Timer_()
{
}























#endif /*__IPC_CC__*/
