#ifndef __REQUEST_ACK_ST_H__
#define __REQUEST_ACK_ST_H__

#include "common.h"

class RequestAckST : public DhcpState
{
private:
  static RequestAckST *m_instance;
  RequestAckST();

public:
  ~RequestAckST();
  static RequestAckST *get_instance();

  void onEntry(DHCP::Server *parent);
  void onExit(DHCP::Server *parent);
  ACE_UINT32 offer(DHCP::Server *parent);
  ACE_UINT32 discover(DHCP::Server *parent);
  ACE_UINT32 request(DHCP::Server *parent);
  ACE_UINT32 requestAck(DHCP::Server *parent);
  ACE_UINT32 leaseTO(DHCP::Server *parent);
};

#endif /*__REQUEST_ACK_ST_H__*/
