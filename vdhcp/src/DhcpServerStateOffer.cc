#ifndef __DHCP_SERVER_STATE_OFFER_CC__
#define __DHCP_SERVER_STATE_OFFER_CC__

#include "DhcpServerStateOffer.h"
#include "ace/Log_Msg.h"

OfferST *OfferST::m_instance = NULL;

OfferST *OfferST::instance()
{
  ACE_TRACE("OfferST::instance");
  if(!m_instance)
  {
    m_instance = new OfferST();
  }

  return (m_instance);
}

void OfferST::onEntry(DHCP::Server &parent)
{
  ACE_TRACE("OfferST::onEntry");
}

void OfferST::onExit(DHCP::Server &parent)
{
  ACE_TRACE("OfferST::onExit");
}

ACE_UINT32 OfferST::offer(DHCP::Server &parent)
{
  ACE_TRACE("OfferST::offer");
  return(0);
}

ACE_UINT32 OfferST::discover(DHCP::Server &parent)
{
  ACE_TRACE("OfferST::discover");
  return(0);
}

ACE_UINT32 OfferST::request(DHCP::Server &parent)
{
  ACE_TRACE("OfferST::request");
  return(0);
}

ACE_UINT32 OfferST::requestAck(DHCP::Server &parent)
{
  ACE_TRACE("OfferST::requestAck");
  return(0);
}

ACE_UINT32 OfferST::leaseTO(DHCP::Server &parent)
{
  ACE_TRACE("OfferST::leaseTO");
  return(0);
}


#endif /*__DHCP_SERVER_STATE_OFFER_CC__*/
