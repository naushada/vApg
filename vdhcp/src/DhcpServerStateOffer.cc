#ifndef __OFFER_ST_CC__
#define __OFFER_ST_CC__

#include "OfferST.h"
#include "ace/Log_Msg.h"

OfferST *OfferST::m_instance = NULL;

static OfferST *OfferST::get_instance()
{
  ACE_TRACE("OfferST::get_instance");
  if(!m_instance)
  {
    m_instance = new OfferST();
  }

  return (m_instance);
}

void OfferST::onEntry(DHCP::Server *parent)
{
  ACE_TRACE("OfferST::onEntry");
}

void OfferST::onExit(DHCP::Server *parent)
{
  ACE_TRACE("OfferST::onExit");
}

ACE_UINT32 OfferST::offer(DHCP::Server *parent)
{
  ACE_TRACE("OfferST::offer");
  return(0);
}

ACE_UINT32 OfferST::discover(DHCP::Server *parent)
{
  ACE_TRACE("OfferST::discover");
  return(0);
}

ACE_UINT32 OfferST::request(DHCP::Server *parent)
{
  ACE_TRACE("OfferST::request");
  return(0);
}

ACE_UINT32 OfferST::requestAck(DHCP::Server *parent)
{
  ACE_TRACE("OfferST::requestAck");
  return(0);
}

ACE_UINT32 OfferST::leaseTO(DHCP::Server *parent)
{
  ACE_TRACE("OfferST::leaseTO");
  return(0);
}


#endif /*__OFFER_ST_CC__*/
