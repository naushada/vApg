#ifndef __CPGATEWAY_STATE_CC__
#define __CPGATEWAY_STATE_CC__

#include "ace/Log_Msg.h"
#include "ace/SString.h"
#include "ace/Basic_Types.h"

#include "commonIF.h"
#include "CPGateway.h"
#include "CPGatewayState.h"

#include "DhcpServer.h"

CPGatewayState::CPGatewayState()
{
  ACE_TRACE("CPGatewayState::CPGatewayState\n");

  ACE_CString dsc("CPGatewayState");
  description(dsc);
}

CPGatewayState::~CPGatewayState()
{
  ACE_TRACE("CPGatewayState::~CPGatewayState\n");
}

ACE_UINT32 CPGatewayState::processRequest(CPGateway *parent,
                                          ACE_Byte *in,
                                          ACE_UINT32 inLen)
{
  ACE_TRACE("CPGatewayState::processRequest\n");

  TransportIF::ETH *ethHdr = (TransportIF::ETH *)in;

  if(TransportIF::ETH_P_IP == ntohs(ethHdr->proto))
  {
    /*Ethernet Header is followed by IP Packet.*/
    TransportIF::IP *ipHdr = (TransportIF::IP *)&in[sizeof(TransportIF::ETH)];
    if(TransportIF::IP_UDP == ipHdr->proto)
    {
      /*IP Packet is followed by UDP Payload.*/
      TransportIF::UDP *udpHdr = (TransportIF::UDP *)&in[sizeof(TransportIF::ETH) +
                                                         sizeof(TransportIF::IP)];

      if((TransportIF::DHCP_CLIENT_PORT == ntohs(udpHdr->src_port)) &&
         (TransportIF::DHCP_SERVER_PORT == ntohs(udpHdr->dest_port)))
      {
        /*This is a DHCP Message.*/
        TransportIF::DHCP *dhcpHdr = (TransportIF::DHCP *)&in[sizeof(TransportIF::ETH) +
                                                              sizeof(TransportIF::IP) +
                                                              sizeof(TransportIF::UDP)];

        ACE_CString haddr((const char *)dhcpHdr->chaddr, TransportIF::ETH_ALEN);
        if(parent->isSubscriberFound(haddr))
        {
          ACE_DEBUG((LM_INFO, "%I chaddr (%s) is found\n", haddr.c_str()));
          DHCP::Server *sess = parent->getSubscriber(haddr);
          sess->getState()->rx(sess, in, inLen);
        }
        else
        {
          DHCP::Server *sess = new DHCP::Server();
          parent->createSubscriber(haddr);
          sess->getState()->rx(sess, in, inLen);
        }

      }
      //else if()
      {
        /*DNS Packet.*/
      }
    }
    else if(TransportIF::IP_TCP == ipHdr->proto)
    {
      /*TCP Packet*/
    }
  }

  return(0);
}

ACE_UINT32 CPGatewayState::lock(CPGateway *parent)
{
  ACE_TRACE("CPGatewayState::lock\n");
  return(0);
}

ACE_UINT32 CPGatewayState::unlock(CPGateway *parent)
{
  ACE_TRACE("CPGatewayState::unlock\n");
  return(0);
}

void CPGatewayState::onEntry(CPGateway *parent)
{
  ACE_TRACE("CPGatewayState::onEntry\n");
}

void CPGatewayState::onExit(CPGateway *parent)
{
  ACE_TRACE("CPGatewayState::onExit\n");
}

ACE_CString CPGatewayState::description(void)
{
  ACE_TRACE("CPGatewayState::description\n");
  return(m_description);
}

void CPGatewayState::description(ACE_CString dsc)
{
  ACE_TRACE("CPGatewayState::description\n");
  m_description = dsc;
}

#endif /*__CPGATEWAY_STATE_CC__*/
