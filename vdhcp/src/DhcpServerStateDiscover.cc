#ifndef __DHCP_SERVER_STATE_DISCOVER_CC__
#define __DHCP_SERVER_STATE_DISCOVER_CC__

#include "DhcpServerStateDiscover.h"
#include "DhcpServer.h"
#include "DhcpServerStateRequest.h"
#include "ace/Log_Msg.h"
#include "ace/Message_Block.h"

DhcpServerStateDiscover *DhcpServerStateDiscover::m_instance = NULL;

DhcpServerStateDiscover *DhcpServerStateDiscover::instance()
{
  ACE_TRACE("DhcpServerStateDiscover::instance\n");

  if(!m_instance)
  {
    m_instance = new DhcpServerStateDiscover();
  }

  return(m_instance);
}

DhcpServerStateDiscover::DhcpServerStateDiscover()
{
  ACE_TRACE("DhcpServerStateDiscover::DhcpServerStateDiscover\n");
  ACE_CString desc("DhcpServerStateDiscover");
  m_description = desc;
}

DhcpServerStateDiscover::~DhcpServerStateDiscover()
{
  ACE_TRACE("DhcpServerStateDiscover::~DhcpServerStateDiscover\n");
  delete m_instance;
}

void DhcpServerStateDiscover::onEntry(DHCP::Server &parent)
{
  ACE_TRACE("DhcpServerStateDiscover::onEntry\n");
}

void DhcpServerStateDiscover::onExit(DHCP::Server &parent)
{
  ACE_TRACE("DhcpServerStateDiscover::onExit\n");
}

ACE_UINT32 DhcpServerStateDiscover::offer(DHCP::Server &parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerStateDiscover::offer\n");
  return(0);
}

ACE_UINT32 DhcpServerStateDiscover::request(DHCP::Server &parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerStateDiscover::offer\n");
  return(0);
}

ACE_UINT32 DhcpServerStateDiscover::requestAck(DHCP::Server &parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerStateDiscover::offer\n");
  return(0);
}

ACE_UINT32 DhcpServerStateDiscover::leaseTO(DHCP::Server &parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerStateDiscover::offer\n");
  return(0);
}

ACE_UINT32 DhcpServerStateDiscover::discover(DHCP::Server &parent, ACE_Byte *inPtr, ACE_UINT32 inLen)
{
  ACE_TRACE("DhcpServerStateDiscover::discover\n");

  /*Prelare DHCP Offer Message .*/
  ACE_Message_Block &mb = buildResponse(parent, inPtr, inLen);

  /*Move to next state to process DHCP Request.*/
  parent.setState(DhcpServerStateRequest::instance());
  return(0);
}



#endif /*__DHCP_SERVER_STATE_DISCOVER_CC__*/
