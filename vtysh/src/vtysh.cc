#ifndef __VTYSH_CC__
#define __VTYSH_CC__


/*
This file interfaces with readline library and provides the implementation
for command/response to/from hostapd.
Copyright (C) <2019>  <Mohammed Naushad Ahmed>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "readlineIF.h"
#include "vtysh.h"

Vtysh::~Vtysh()
{

}

Vtysh::Vtysh()
{
  do
  {
    if(-1 == m_unixAddr.set("/tmp/vtysh/ctrlIF"))
    {
      ACE_ERROR((LM_ERROR, "Setting of Address Failed\n"));
      break;
    }

    #ifdef DEBUG
    ACE_OS::unlink(m_unixAddr.get_path_name());
    struct sockaddr_un *ss = (struct sockaddr_un *)m_unixAddr.get_addr();
    ACE_DEBUG((LM_DEBUG, "family %d path %s\n", ss->sun_family, ss->sun_path));
    #endif

    ACE_OS::unlink(m_unixAddr.get_path_name());
    if(-1 == m_unixDgram.open(m_unixAddr, PF_UNIX))
    {
      ACE_ERROR((LM_ERROR,"Unix Socket Creation Failed\n"));
      break;
    }

    handle(m_unixDgram.get_handle());
    /*Note: Right after registering handler, ACE Framework calls get_handle
            to retrieve the handle. The handle is nothing but a fd
            (File Descriptor).*/
    ACE_Reactor::instance()->register_handler(this,
					ACE_Event_Handler::READ_MASK |
					ACE_Event_Handler::TIMER_MASK);

  }while(0);
}

/*
 * @brief  This is the hook method of ACE Event Handler and is called by ACE Framework to retrieve the
 *         handle. The handle is nothing but it's fd - file descriptor.
 * @param  none
 * @return handle of type ACE_HANDLE
 */
ACE_HANDLE Vtysh::get_handle(void) const
{
  return(const_cast<Vtysh *>(this)->handle());
}

ACE_HANDLE Vtysh::handle(void)
{
  return(m_handle);
}

void Vtysh::handle(ACE_HANDLE handle)
{
  m_handle = handle;
}


int Vtysh::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask mask)
{
  return(0);
}

/*
 * @brief  This is the hook method for application to process the timer expiry. This is invoked by 
 *         ACE Framework upon expiry of timer.
 * @param  tv in sec and usec.
 * @param  argument which was passed while starting the timer.
 * @return 0 for success else for failure.
 */
int Vtysh::handle_timeout(const ACE_Time_Value &tv, const void *arg)
{
  ACE_DEBUG((LM_DEBUG, "Time is expired now\n"));
  return(0);
}

/*
 * @brief  This is the hook method for application to define this member function and is invoked by 
 *         ACE Framework.
 * @param  handle in which read/recv/recvfrom to be called.
 * @return 0 for success else for failure.
 */
int Vtysh::handle_input(ACE_HANDLE handle)
{
  char buff[1024];
  size_t len = sizeof(buff);

  memset((void *)buff, 0, sizeof(buff));
  ACE_Reactor::instance()->cancel_timer(this->m_rspTimerId);

  /*UNIX socket for IPC.*/
  ACE_UNIX_Addr peer;
  int recv_len = -1;
  if((recv_len = m_unixDgram.recv(buff, len, peer)) < 0)
  {
    ACE_ERROR((LM_ERROR, "Receive from peer failed\n"));
  }

  ACE_DEBUG((LM_DEBUG, "%s", buff));

  return(0);
}


int Vtysh::transmit(char *command)
{
  do
  {
    size_t len = -1;
    if(!command)
    {
      ACE_ERROR((LM_ERROR, "Command can't be transmitted because it's NULL\n"));
      break;
    }

    len = ACE_OS::strlen(command);

    /*For UNIX Socket...*/
    ACE_UNIX_Addr peer("/var/run/vapgCtrl");
    if(m_unixDgram.send(command, len, peer) < 0)
    {
      ACE_ERROR((LM_ERROR, "Sending of command len %d (%s) failed\n", strlen(command), command));
      break;
    }

    /*Start Response Guard Timer now.*/
    ACE_Time_Value to(1, 0);
    ACE_Time_Value interval = ACE_Time_Value::zero;
    m_rspTimerId = ACE_Reactor::instance()->schedule_timer(this, NULL, to, interval);

  }while(0);

  return(0);
}

int main()
{
  return(0);
}
#endif
