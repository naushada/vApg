#ifndef __DHCP_SERVER_STATE_OFFER_H__
#define __DHCP_SERVER_STATE_OFFER_H__

#include "DhcpServerState.h"

class OfferST : public DhcpServerState
{
private:
  static OfferST *m_instance;
  OfferST();
public:
  ~OfferST();
  static OfferST *instance();
  void onEntry(DHCP::Server &parent);
  void onExit(DHCP::Server &parent);
  ACE_UINT32 offer(DHCP::Server &parent);
  ACE_UINT32 discover(DHCP::Server &parent);
  ACE_UINT32 request(DHCP::Server &parent);
  ACE_UINT32 requestAck(DHCP::Server &parent);
  ACE_UINT32 leaseTO(DHCP::Server &parent);

};


#endif /*__DHCP_SERVER_STATE_OFFER_H__*/
