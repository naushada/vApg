#ifndef __LEASETO_ST_H__
#define __LEASETO_ST_H__

#include "common.h"


class LeaseTOST : public DhcpState
{
private:
  static LeaseTOST *m_instance;
  LeaseTOST();

public:
  ~LeaseTOST();
  static LeaseTOST *get_instance();

  void onEntry(DHCP::Server *parent);
  void onExit(DHCP::Server *parent);
  ACE_UINT32 offer(DHCP::Server *parent);
  ACE_UINT32 discover(DHCP::Server *parent);
  ACE_UINT32 request(DHCP::Server *parent);
  ACE_UINT32 requestAck(DHCP::Server *parent);
  ACE_UINT32 leaseTO(DHCP::Server *parent);

};


#endif /*__LEASETO_ST_H__*/
