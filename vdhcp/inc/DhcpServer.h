#ifndef __DHCP_SERVER_H__
#define __DHCP_SERVER_H__

#include "DhcpCommon.h"
#include "DhcpServerState.h"
#include <ace/Basic_Types.h>
#include <ace/SString.h>
#include <ace/Hash_Map_Manager.h>
#include <ace/Null_Mutex.h>
#include <ace/Event_Handler.h>

class DhcpServerState;

namespace DHCP
{
  static const ACE_UINT32 EXPECTED_REQUEST_GUARD_TIMER_ID = 0x01;
  static const ACE_UINT32 LEASE_GUARD_TIMER_ID = 0x02;

  static const ACE_UINT32 SIZE_64MB = (1 << 26);
  static const ACE_UINT32 SIZE_32MB = (1 << 25);
  static const ACE_UINT32 SIZE_16MB = (1 << 24);
  static const ACE_UINT32 SIZE_8MB  = (1 << 23);
  static const ACE_UINT32 SIZE_4MB  = (1 << 22);
  static const ACE_UINT32 SIZE_2MB  = (1 << 21);
  static const ACE_UINT32 SIZE_1MB  = (1 << 20);
  static const ACE_INT32 SUCCESS = 0;
  static const ACE_INT32 FAILURE = -1;

  typedef ACE_Hash_Map_Manager<ACE_UINT8, RFC2131::DhcpOption*,ACE_Null_Mutex>ElemDef;

  class Server : public ACE_Event_Handler 
  {
  private:
    ACE_Message_Block *m_mb;
    ACE_CString m_description;
    /*State Machine Instance.*/
    DhcpServerState *m_state;
    /*dhcp header is in context.*/
    RFC2131::DhcpCtx *m_ctx;
    ElemDef *m_optionMap;
    /*Guard Timer for next request.*/
    long m_guardTid;
    /*lease Expire timeout.*/
    long m_leaseTid;

  public:
    //Server(CPGateway *parent);
    Server();
    virtual ~Server();

    void setState(DhcpServerState *st);
    DhcpServerState &getState(void);

    ACE_UINT32 start();
    ACE_UINT32 stop();

    void xid(ACE_UINT32 xid);
    ACE_UINT32 xid(void);

    void guardTid(long gTid);
    long guardTid(void);

    void leaseTid(long lTid);
    long leaseTid(void);

    RFC2131::DhcpCtx &ctx(void);
    ElemDef &optionMap(void);

    ACE_INT32 process_timeout(const void *act);

    ACE_INT32 handle_timeout(ACE_Time_Value &tv,
                             const void *act=0);

    long start_timer(ACE_UINT32 delay, const void *act,
                     ACE_Time_Value interval = ACE_Time_Value::zero);

    void stop_timer(long timerId);
  };

  typedef struct TIMER_ID
  {
    TIMER_ID()
    {
      m_timerType = 0;
      m_chaddrLen = 0;
      ACE_OS::memset((void *)m_chaddr, 0, sizeof(m_chaddr));
    }

    ACE_UINT32 m_timerType;
    ACE_UINT8 m_chaddrLen;
    ACE_Byte m_chaddr[16];

    ACE_UINT32 timerType(void)
    {
      return(m_timerType);
    }

    void timerType(ACE_UINT32 tType)
    {
      m_timerType = tType;
    }

    ACE_UINT8 chaddrLen(void)
    {
      return(m_chaddrLen);
    }

    void chaddrLen(ACE_UINT8 len)
    {
      m_chaddrLen = len;
    }

    ACE_Byte *chaddr(void)
    {
      return(m_chaddr);
    }

    void chaddr(ACE_Byte *cha)
    {
      ACE_OS::memcpy((void *)m_chaddr, (const void *)cha, chaddrLen());
    }

  }TIMER_ID;
}


#endif /*__DHCP_SERVER_H__*/
