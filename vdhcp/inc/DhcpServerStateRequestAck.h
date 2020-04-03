#ifndef __DHCP_SERVER_STATE_REQUEST_ACK_H__
#define __DHCP_SERVER_STATE_REQUEST_ACK_H__

#include "DhcpServerState.h"

class RequestAckST : public DhcpServerState
{
private:
  static RequestAckST *m_instance;
  RequestAckST();

public:
  ~RequestAckST();
  static RequestAckST *instance();

  void onEntry(DHCP::Server *parent);
  void onExit(DHCP::Server *parent);
  ACE_UINT32 offer(DHCP::Server *parent);
  ACE_UINT32 discover(DHCP::Server *parent);
  ACE_UINT32 request(DHCP::Server *parent);
  ACE_UINT32 requestAck(DHCP::Server *parent);
  ACE_UINT32 leaseTO(DHCP::Server *parent);
};

#endif /*__DHCP_SERVER_STATE_REQUEST_ACK_H__*/
