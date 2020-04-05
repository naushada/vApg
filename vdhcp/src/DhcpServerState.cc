#ifndef __DHCP_SERVER_STATE_CC__
#define __DHCP_SERVER_STATE_CC__

//#include "commonIF.h"
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

/*Populate DHCP Options.*/
ACE_UINT32 DhcpServerState::populateDhcpOption(DHCP::Server *parent, ACE_Byte *dhcpOption,
                                               ACE_UINT32 optionLen)
{
  ACE_TRACE("DhcpServerState::populateDhcpOption\n");

  ACE_UINT32 offset = 0;

  while(optionLen > 0)
  {
    switch(dhcpOption[offset])
    {
    case RFC2131::OPTION_END:
      optionLen = 0;
      break;
    default:

      RFC2131::DhcpOption *elm = NULL;
      ACE_UINT8 tag = dhcpOption[offset];

      if(parent->optionMap().find(tag, elm) != -1)
      {
        /*Not found in the MAP.*/
        elm = new RFC2131::DhcpOption();

        elm->m_tag = dhcpOption[offset++];
        elm->m_len = dhcpOption[offset++];
        ACE_OS::memcpy((void *)elm->m_value, (const void *)&dhcpOption[offset], elm->m_len);

        offset += elm->m_len;
        /*Add it into MAP now.*/
        parent->optionMap().bind(elm->m_tag, elm);
      }
      else
      {
        /*Found in the Map , Update with new contents received now.*/
        elm->m_tag = dhcpOption[offset++];
        elm->m_len = dhcpOption[offset++];

        ACE_OS::memcpy((void *)elm->m_value, (const void *)&dhcpOption[offset], elm->m_len);

        offset += elm->m_len;
      }
    }
  }

  return(0);
}

/*Populating DHCP Header*/
ACE_UINT32 DhcpServerState::populateDhcpHeader(DHCP::Server *parent, TransportIF::DHCP *dhcpHeader)
{
  ACE_TRACE("DhcpServerState::populateDhcpHeader\n");
  parent->ctx().xid(dhcpHeader->xid);
  parent->ctx().ciaddr(dhcpHeader->ciaddr);
  parent->ctx().yiaddr(dhcpHeader->yiaddr);
  parent->ctx().siaddr(dhcpHeader->siaddr);
  parent->ctx().giaddr(dhcpHeader->giaddr);

  parent->ctx().chaddrLen(dhcpHeader->hlen);
  parent->ctx().chaddr(dhcpHeader->chaddr);

  parent->ctx().sname(dhcpHeader->sname);

  return(0);
}

/*RX*/
ACE_UINT32 DhcpServerState::rx(DHCP::Server *parent, ACE_Byte *in, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerState::rx\n");

  TransportIF::DHCP *dhcpHdr = (TransportIF::DHCP *)&in[sizeof(TransportIF::ETH) +
                                                        sizeof(TransportIF::IP) +
                                                        sizeof(TransportIF::UDP)];
  populateDhcpHeader(parent, dhcpHdr);

  TransportIF::UDP *udpHdr = (TransportIF::UDP *)&in[sizeof(TransportIF::ETH) +
                                                     sizeof(TransportIF::IP)];
  /*Number of bytes in dhcpOptional Payload.*/
  ACE_UINT32 dhcpOptionLen = ntohs(udpHdr->len) - sizeof(TransportIF::DHCP);

  /*dhcpOption Offset.*/
  ACE_Byte *dhcpOption = (ACE_Byte *)&in[sizeof(TransportIF::ETH)  +
                                         sizeof(TransportIF::IP)   +
                                         sizeof(TransportIF::UDP)  +
                                         sizeof(TransportIF::DHCP) +
                                         4/*Dhcp Cookies*/];

  populateDhcpOption(parent, dhcpOption, dhcpOptionLen);

  ACE_UINT8 msgType = 0;
  RFC2131::DhcpOption *elm = NULL;

  if(parent->optionMap().find(RFC2131::OPTION_MESSAGE_TYPE, elm) != -1)
  {
    msgType =(ACE_UINT8)elm->m_value[0];
    ACE_DEBUG((LM_DEBUG, "messageType tag(%u) is found\n", msgType));
  }

  switch(msgType)
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
      ACE_ERROR((LM_ERROR, "%I the DHCP opcode %u is not supported\n", msgType));
      break;
  }

  return(0);
}



#endif /*__DHCP_SERVER_STATE_CC__*/
