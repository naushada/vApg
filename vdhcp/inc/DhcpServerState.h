#ifndef __DHCP_SERVER_STATE_H__
#define __DHCP_SERVER_STATE_H__

#include "commonIF.h"
#include "ace/SString.h"

/*Forward declaration of a class belong to a namespace. */
namespace DHCP { class Server;}

class DhcpServerState
{
protected:
  ACE_CString m_description;

public:
  DhcpServerState();
  ~DhcpServerState();

  virtual void onEntry(DHCP::Server *parent);
  virtual void onExit(DHCP::Server *parent);
  /*DHCP Offer */
  virtual ACE_UINT32 offer(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen);
  /*DHCP Discover */
  virtual ACE_UINT32 discover(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen);
  /*DHCP Request */
  virtual ACE_UINT32 request(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen);
  /*DHCP Request Ack */
  virtual ACE_UINT32 requestAck(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen);
  /*Lease Time Out */
  virtual ACE_UINT32 leaseTO(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen);
  /*Release  */
  virtual ACE_UINT32 release(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen);
  /*NACK  */
  virtual ACE_UINT32 nack(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen);
  /*decline  */
  virtual ACE_UINT32 decline(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen);
  /*RX  */
  ACE_UINT32 rx(DHCP::Server *parent, ACE_Byte *inPtr, ACE_UINT32 inLen);

  /*Populate DHCP Header.*/
  ACE_UINT32 populateDhcpHeader(DHCP::Server *parent, TransportIF::DHCP *dhcpHeader);
  /*Populate DHCP Options.*/
  ACE_UINT32 populateDhcpOption(DHCP::Server *parent, ACE_Byte *dhcpOption, ACE_UINT32 len);

};

#endif /*__DHCP_SERVER_STATE_H__*/
