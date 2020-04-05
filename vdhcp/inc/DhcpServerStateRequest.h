#ifndef __DHCP_SERVER_STATE_REQUEST_H__
#define __DHCP_SERVER_STATE_REQUEST_H__

#include "DhcpServerState.h"

class DhcpServerStateRequest : public DhcpServerState
{
private:
  static DhcpServerStateRequest *m_instance;
  DhcpServerStateRequest();

public:
  ~DhcpServerStateRequest();
  static DhcpServerStateRequest *instance();

  void onEntry(DHCP::Server &parent);
  void onExit(DHCP::Server &parent);

  ACE_UINT32 offer(DHCP::Server &parent, ACE_Byte *in, ACE_UINT32 inLen);
  ACE_UINT32 discover(DHCP::Server &parent, ACE_Byte *in, ACE_UINT32 inLen);
  ACE_UINT32 request(DHCP::Server &parent, ACE_Byte *in, ACE_UINT32 inLen);
  ACE_UINT32 requestAck(DHCP::Server &parent, ACE_Byte *in, ACE_UINT32 inLen);
  ACE_UINT32 leaseTO(DHCP::Server &parent, ACE_Byte *in, ACE_UINT32 inLen);

};


#endif /*__DHCP_SERVER_STATE_REQUEST_H__*/
