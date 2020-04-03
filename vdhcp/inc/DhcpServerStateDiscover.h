#ifndef __DHCP_SERVER_STATE_DISCOVER_H__
#define __DHCP_SERVER_STATE_DISCOVER_H__

#include "DhcpServerState.h"

class DhcpServerStateDiscover : public DhcpServerState
{
private:
  static DhcpServerStateDiscover *m_instance;
  DhcpServerStateDiscover();

public:
  virtual ~DhcpServerStateDiscover();
  static DhcpServerStateDiscover *instance();

  void onEntry(DHCP::Server *parent);
  void onExit(DHCP::Server *parent);
  ACE_UINT32 offer(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen);
  ACE_UINT32 discover(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen);
  ACE_UINT32 request(DHCP::Server *parent, ACE_Byte *in, ACE_UINT32 inLen);
  ACE_UINT32 requestAck(DHCP::Server *parent, ACE_Byte *in, ACE_UINT32 inLen);
  ACE_UINT32 leaseTO(DHCP::Server *parent, ACE_Byte *in, ACE_UINT32 inLen);

};


#endif /*__DHCP_SERVER_STATE_DISCOVER_H__*/
