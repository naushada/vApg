#ifndef __CPGATEWAY_H__
#define __CPGATEWAY_H__

#include "server.h"
#include "CPGatewayState.h"

#include <unordered_map>

typedef std::unordered_map<ACE_CString, DHCP::Server *>subscriberMap_t;
typedef subscriberMap_t::iterator subscriberMap_ter;

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

    subscriberMap_t m_subscriberMap;

  public:
    CPGateway(ACE_CString intfName)
    {
      m_ethInterface = intfName;
    }

    ACE_UINT8 start();
    ACE_UINT8 stop();

    virtual ACE_HANDLE get_handle() const;
    virtual int handle_input(ACE_HANDLE handle);
    ACE_INT32 open(void);
    ACE_INT32 get_index(void);
    ACE_HANDLE handle();
    void set_handle(ACE_HANDLE handle);

    void setState(CPGatewayState *sm);
    CPGatewayState *getState(void);

    ACE_UINT8 isSubscriberFound(ACE_CString macAddress);
    ACE_UINT8 createSubscriber(ACE_CString macAddress);
    DHCP::Server &getSubscriber(ACE_CString macAddress);
    ACE_UINT8 deleteSubscriber(ACE_CString macAddress);
    ACE_UINT32 processDhcpRequest(const char *inPtr, ACE_UINT32 inLen);

    ACE_UINT8 isSubscriberAuthenticated(ACE_CString macAddress);
};

#endif /*__CPGATEWAY_H__*/
