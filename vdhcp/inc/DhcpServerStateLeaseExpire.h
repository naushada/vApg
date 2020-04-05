#ifndef __DHCP_SERVER_STATE_LEASE_EXPIRE__H__
#define __DHCP_SERVER_STATE_LEASE_EXPIRE__H__

#include "DhcpServerState.h"

class DhcpServerStateLeaseExpire : public DhcpServerState
{
private:
  static DhcpServerStateLeaseExpire *m_instance;
  DhcpServerStateLeaseExpire();

public:
  ~DhcpServerStateLeaseExpire();
  static DhcpServerStateLeaseExpire *instance();

  void onEntry(DHCP::Server &parent);
  void onExit(DHCP::Server &parent);
  ACE_UINT32 offer(DHCP::Server &parent);
  ACE_UINT32 discover(DHCP::Server &parent);
  ACE_UINT32 request(DHCP::Server &parent);
  ACE_UINT32 requestAck(DHCP::Server &parent);
  ACE_UINT32 leaseTO(DHCP::Server &parent);

};


#endif /*__DHCP_SERVER_STATE_LEASE_EXPIRE__H__*/
