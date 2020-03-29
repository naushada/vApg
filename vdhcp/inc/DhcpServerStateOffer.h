#ifndef __OFFER_ST_H__
#define __OFFER_ST_H__

#include "common.h"

class OfferST : public DhcpState
{
private:
  static OfferST *m_instance;
  OfferST();
public:
  ~OfferST();
  static OfferST *get_instance();
  void onEntry(DHCP::Server *parent);
  void onExit(DHCP::Server *parent);
  ACE_UINT32 offer(DHCP::Server *parent);
  ACE_UINT32 discover(DHCP::Server *parent);
  ACE_UINT32 request(DHCP::Server *parent);
  ACE_UINT32 requestAck(DHCP::Server *parent);
  ACE_UINT32 leaseTO(DHCP::Server *parent);

};


#endif /*__OFFER_ST_H__*/
