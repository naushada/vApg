#ifndef __CPGATEWAY_H__
#define __CPGATEWAY_H__

#include "DhcpServer.h"
#include "CPGatewayState.h"

#include "ace/Event_Handler.h"
#include "ace/SOCK_Dgram.h"
#include "ace/SString.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Null_Mutex.h"

typedef ACE_Hash_Map_Manager<ACE_CString, DHCP::Server*, ACE_Null_Mutex>subscriberMap_t;
typedef ACE_Hash_Map_Manager<ACE_CString, DHCP::Server *, ACE_Null_Mutex>::iterator subscriberMap_ter;

class DhcpConf
{
private:
  static DhcpConf *m_instance;
  ACE_UINT8 m_mtu;
  ACE_UINT32 m_subnetMask;
  ACE_UINT32 m_dns;
  ACE_Byte m_domainName[255];
  ACE_UINT32 m_serverIp;
  ACE_Byte m_serverName[255];
  ACE_UINT32 m_leaseTime;
public:
  DhcpConf();
  DhcpConf(ACE_UINT8 mtu, ACE_UINT32 subnetMask, ACE_UINT32 dns,
           ACE_Byte *domainName, ACE_UINT32 serverIp, ACE_Byte *serverName,
           ACE_UINT32 lease);
  ~DhcpConf();
  static DhcpConf *instance();
};

class CPGateway : public ACE_Event_Handler
{
  private:
    /*Ethernet Interface Name.*/
    ACE_CString m_ethInterface;
    ACE_HANDLE m_handle;
    ACE_Message_Block *m_mb;
    ACE_CString m_ipAddress;
    ACE_CString m_macAddress;
    ACE_UINT32 m_intfIndex;
    ACE_SOCK_Dgram m_dgram;

    /*State-Machine for CPGateway. Note This will point to pointer to sub-class*/
    CPGatewayState *m_state;

    /*DHCP::Server instance based on chaddr - Client Identifier.*/
    subscriberMap_t m_subscriberMap;

  public:
    virtual ~CPGateway();
    CPGateway(ACE_CString intfName);
    CPGateway(ACE_CString intfName, ACE_CString ipAddr,
              ACE_UINT8 entity, ACE_UINT8 instance,
              ACE_CString nodeTag);

    ACE_UINT8 start();
    ACE_UINT8 stop();

    virtual ACE_HANDLE get_handle() const;
    virtual int handle_input(ACE_HANDLE handle);
    ACE_INT32 open(void);
    ACE_INT32 get_index(void);
    ACE_HANDLE handle();
    void set_handle(ACE_HANDLE handle);

    void setState(CPGatewayState *sm);
    CPGatewayState &getState(void);

    ACE_UINT8 isSubscriberFound(ACE_CString macAddress);
    ACE_UINT8 createSubscriber(ACE_CString macAddress);
    ACE_UINT8 addSubscriber(DHCP::Server *sess, ACE_CString macAddress);
    DHCP::Server *getSubscriber(ACE_CString macAddress);
    ACE_UINT8 deleteSubscriber(ACE_CString macAddress);

    ACE_UINT8 isSubscriberAuthenticated(ACE_CString macAddress);
};

#endif /*__CPGATEWAY_H__*/
