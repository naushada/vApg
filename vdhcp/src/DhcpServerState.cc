#ifndef __DHCP_SERVER_STATE_CC__
#define __DHCP_SERVER_STATE_CC__

#include "commonIF.h"
#include "ace/Log_Msg.h"
#include "DhcpServerState.h"
#include "DhcpCommon.h"
#include "DhcpServer.h"

DhcpServerState::DhcpServerState()
{
  ACE_TRACE("DhcpServerState::DhcpServerState\n");
  ACE_CString desc("DhcpServerState");
  m_description = desc;
}

DhcpServerState::~DhcpServerState()
{
  ACE_TRACE("DhcpServerState::~DhcpServerState\n");
}

void DhcpServerState::onEntry(DHCP::Server *parent)
{
  ACE_TRACE("DhcpServerState::onEntry\n");
}

void DhcpServerState::onExit(DHCP::Server *parent)
{
  ACE_TRACE("DhcpServerState::onExit\n");
}

/*DHCP Offer */
ACE_UINT32 DhcpServerState::offer(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerState::offer\n");
  return(0);
}

/*DHCP Discover */
ACE_UINT32 DhcpServerState::discover(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerState::discover\n");
  return(0);
}

/*DHCP Request */
ACE_UINT32 DhcpServerState::request(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerState::request\n");
  return(0);
}

/*DHCP Request Ack */
ACE_UINT32 DhcpServerState::requestAck(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerState::requestAck\n");
  return(0);
}

/*Lease Time Out */
ACE_UINT32 DhcpServerState::leaseTO(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerState::leaseTO\n");
  return(0);
}

/*Release  */
ACE_UINT32 DhcpServerState::release(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerState::release\n");
  return(0);
}

/*NACK  */
ACE_UINT32 DhcpServerState::nack(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerState::nack\n");
  return(0);
}

/*NACK  */
ACE_UINT32 DhcpServerState::decline(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerState::nack\n");
  return(0);
}

/*RX*/
ACE_UINT32 DhcpServerState::rx(DHCP::Server *parent, ACE_Byte *in, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerState::rx\n");

  TransportIF::DHCP *dhcpHdr = (TransportIF::DHCP *)&in[sizeof(TransportIF::ETH) +
                                                        sizeof(TransportIF::IP) +
                                                        sizeof(TransportIF::UDP)];
  switch(dhcpHdr->op)
  {
    case RFC2131::DISCOVER:
      /*Kick the state Machine.*/
      parent->getState()->discover(parent, in, inLen);
      break;
    case RFC2131::REQUEST:
      /*Kick the state Machine.*/
      parent->getState()->request(parent, in, inLen);
      break;
    case RFC2131::RELEASE:
      /*Kick the state Machine.*/
      parent->getState()->release(parent, in, inLen);
      break;
    case RFC2131::DECLINE:
      /*Kick the state Machine.*/
      parent->getState()->decline(parent, in, inLen);
      break;
    case RFC2131::NACK:
      /*Kick the state Machine.*/
      parent->getState()->nack(parent, in, inLen);
      break;
    default:
      ACE_ERROR((LM_ERROR, "%I the DHCP opcode %u is not supported\n", dhcpHdr->op));
      break;
  }

  return(0);
}



#endif /*__DHCP_SERVER_STATE_CC__*/
