#ifndef __CPGATEWAY_CC__
#define __CPGATEWAY_CC__

#include <sys/time.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/tcp.h>
#include <linux/if_arp.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "ace/Reactor.h"
#include "ace/Event_Handler.h"
#include "ace/SString.h"
#include "ace/SOCK_Dgram.h"
#include "server.h"
#include "ace/Log_Msg.h"

#include "cpgateway.h"
#include "CPGatewayState.h"

void CPGateway::setState(CPGatewayState *st)
{
  ACE_TRACE("CPGateway::setState\n");

  if(m_state)
    getState()->onExit(this);

  m_state = st;
  getState()->onEntry(this);
}

CPGatewayState *CPGateway::getState(void)
{
  ACE_TRACE("CPGateway::getState\n");
  return(m_state);
}

int CPGateway::handle_input(ACE_HANDLE fd)
{
  ACE_TRACE("CPGateway::handle_input\n");
  struct sockaddr_ll sa;
  socklen_t addr_len = sizeof(sa);
  ACE_INT32 len = -1;

  ACE_NEW_NORETURN(m_mb, ACE_Message_Block(CPGateway::SIZE_64MB));

  len = ACE_OS::recvfrom(fd, m_mb->wr_ptr(),
                         CPGateway::SIZE_64MB, 0, (struct sockaddr *)&sa, &addr_len);
  if(len < 0)
  {
    ACE_ERROR((LM_ERROR, "%Irecvfrom failed for handle %d\n", fd));
    return(0);
  }

  /*Update the length od data in m_mb*/
  m_mb->wr_ptr(len);

  /*Check wheather CPGateway is administrative locked/error state.*/
  if(getState())
  {
    getState()->processRequest(this, m_mb->rd_ptr(), m_mb->length());
    return(0);
  }

  ACE_DEBUG((LM_INFO, "%I CPGateway state is locked/error state\n"));
  return(0);
}

ACE_INT32 CPGateway::get_index(void)
{
  ACE_HANDLE handle = -1;
  struct ifreq ifr;
  ACE_INT32 retStatus = CPGateway::FAILURE;

  ACE_TRACE("CPGateway::get_index");

  do
  {
    handle = ACE_OS::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(handle < 0)
    {
      ACE_ERROR((LM_ERROR, "%Isocket creation failed\n"));
      break;
    }

    ACE_OS::memset((void *)&ifr, 0, sizeof(struct ifreq));
    ifr.ifr_addr.sa_family = AF_INET;
    ACE_OS::strncpy(ifr.ifr_name, m_ethInterface.c_str(), IFNAMSIZ);

    if(ACE_OS::ioctl(handle, SIOCGIFHWADDR, &ifr) < 0)
    {
      ACE_ERROR((LM_ERROR, "%IMAC Address retrieval Failed for handle %d", handle));
      ACE_OS::close(handle);
      break;
    }

    m_macAddress.set(ifr.ifr_addr.sa_data, ETH_ALEN, 1);

    if(ACE_OS::ioctl(handle, SIOCGIFINDEX, &ifr) < 0)
    {
      ACE_ERROR((LM_ERROR, "%IRetrieval of ethernet Index failed for handle %d", handle));
      ACE_OS::close(handle);
      break;
    }

    ACE_OS::close(handle);
    retStatus = ifr.ifr_ifindex;

  }while(0);

  return(retStatus);
}

ACE_INT32 CPGateway::open(void)
{
  ACE_HANDLE handle = -1;
  ACE_HANDLE option = 0;
  struct ifreq ifr;
  struct sockaddr_ll sa;
  struct packet_mreq mr;
  ACE_INT32 retStatus = CPGateway::FAILURE;

  do
  {
    handle = ACE_OS::socket(PF_PACKET, SOCK_RAW, ACE_OS::htons(ETH_P_ALL));

    if(handle < 0)
    {
      ACE_ERROR((LM_ERROR, "%ICreation of handle for RAW Socket Failed\n"));
      break;
    }

    option = 1;
    ACE_OS::setsockopt(handle, SOL_SOCKET, TCP_NODELAY, &option, sizeof(option));
    option = 1;
    ACE_OS::setsockopt(handle, SOL_SOCKET, SO_BROADCAST, &option, sizeof(option));


    ACE_OS::memset((void *)&ifr, 0, sizeof(ifr));

    if(ioctl(handle, SIOCGIFFLAGS, &ifr) < 0)
    {
      ACE_ERROR((LM_ERROR, "%IRetrieval of IFFLAG flaied for handle %d\n", handle));
      ACE_OS::close(handle);
      break;
    }

    ifr.ifr_flags |= IFF_PROMISC | IFF_NOARP;

    if(ioctl(handle, SIOCSIFFLAGS, &ifr) < 0)
    {
      ACE_ERROR((LM_ERROR, "%ISeting of PROMISC and NOARP failed for handle %d\n", handle));
      ACE_OS::close(handle);
      break;
    }

    ACE_OS::memset((void *)&mr, 0, sizeof(mr));
    mr.mr_ifindex = get_index();
    mr.mr_type = PACKET_MR_PROMISC;

    if(ACE_OS::setsockopt(handle, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mr, sizeof(mr)) < 0)
    {
      ACE_ERROR((LM_ERROR, "%IAdding membership failed for handle %d\n", handle));
      ACE_OS::close(handle);
      break;
    }

    ACE_OS::memset((void *)&sa, 0, sizeof(sa));
    sa.sll_family = AF_PACKET;
    sa.sll_protocol = ACE_OS::htons(ETH_P_ALL);
    sa.sll_ifindex = get_index();

    if(ACE_OS::bind(handle, (struct sockaddr *)&sa, sizeof(sa)) < 0)
    {
      ACE_ERROR((LM_ERROR, "%Ibind failed for handle %d\n", handle));
      ACE_OS::close(handle);
      break;
    }

    set_handle(handle);
    retStatus = CPGateway::SUCCESS;

  }while(0);

  return(retStatus);
}

ACE_HANDLE CPGateway::handle()
{
  return(m_handle);
}

void CPGateway::set_handle(ACE_HANDLE handle)
{
  m_handle = handle;
}

ACE_HANDLE CPGateway::get_handle() const
{
  ACE_TRACE("CPGateway::get_handle");
  return(handle());
}

CPGateway::CPGateway(ACE_CString intfName)
{
  ACE_TRACE("CPGateway::CPGateway");

  m_ethInterface = intfName;

  /*Mske CPGateway state machine Activated State.*/
  setState(CPGatewayStateActivated::instance());

  if(open() < 0)
  {
    ACE_ERROR((LM_ERROR, "%Iopen for ethernet Interface %s failed\n", intfName.c_str()));
  }
}

ACE_INT32 CPGateway::start()
{
  ACE_TRACE("CPGateway::start\n");
  ACE_Time_Value to(5);
  ACE_CString ipAddrStr("127.0.0.1");
  ACE_CString nodetag("primary");


  ACE_Reactor::instance()->register_handler(this, ACE_Event_Handler::READ_MASK);

  while(1)
  {
    ACE_Reactor::instance()->handle_events(to);
  }

  return(0);
}

ACE_INT32 CPGateway::stop()
{
  ACE_TRACE("CPGateway::stop\n");
  return(0);
}

ACE_UINT8 CPGateway::isSubscriberFound(ACE_CString macAddress)
{
  subscriberMap_ter it;

  it = m_subscriberMap.find(macAddress);

  return(it != m_subscriberMap.end());
}

ACE_UINT8 CPGateway::createSubscriber(ACE_CString macAddress)
{

  DHCP::Server sess();
  /*let STL do the memory management for stack object.*/
  m_subscriberMap.insert(std::make_pair<ACE_CString, DHCP::Server>(macAddress, sess));

  return(0);
}

DHCP::Server *CPGateway::getSubscriber(ACE_CString macAddress)
{
  subscriberMap_ter it;

  it = m_subscriberMap.find(macAddress);
  return(it->second);
}

ACE_UINT32 CPGateway::processDhcpRequest(const char *inPtr, ACE_UINT32 inLen)
{

  ACE_CString srcMac((const char *)&inPtr[ETH_ALEN], ETH_ALEN);

  DHCP::Server sess = getSubscriber(srcMac);
  sess.getState()->;
  return(0);
}

int main(int argc, char *argv[])
{

  /*
   * argv[0] = ethernetInterfaceName
   * argv[1] = IPC IP Address = 127.0.0.1
   * argv[2] = entityID/facility
   * argv[3] = instanceId
   * argv[4] = nodeName
   * */
  CPGateway *cp = new CPGateway(argv[0], argv[1], atoi(argv[2]),
                                atoi(argv[3]), argv[4]);

  if(!cp->start())
  {
    ACE_ERROR((LM_ERROR, "%I CPGateway instantiation failed\n"));
    delete cp;
    return(-1);
  }

  return(0);
}
#endif /*__CPGATEWAY_CC__*/
