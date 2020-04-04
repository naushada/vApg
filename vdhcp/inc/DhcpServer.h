#ifndef __DHCP_SERVER_H__
#define __DHCP_SERVER_H__

#include "ipc.h"

#include "DhcpCommon.h"
#include "DhcpServerState.h"
#include <ace/Basic_Types.h>
#include <ace/SString.h>
#include <ace/Hash_Map_Manager.h>
#include <ace/Null_Mutex.h>

class DhcpServerState;

namespace DHCP
{
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
  class Server : public UniTimer
  {
  private:
    ACE_Message_Block *m_mb;
    ACE_CString m_description;
    /*State Machine Instance.*/
    DhcpServerState *m_state;
    /*dhcp header is in context.*/
    RFC2131::DhcpCtx *m_ctx;
    ElemDef *m_optionMap;

  public:
    //Server(CPGateway *parent);
    Server();
    virtual ~Server();

    void setState(DhcpServerState *st);
    DhcpServerState *getState(void);

    ACE_UINT32 start();
    ACE_UINT32 stop();

    void xid(ACE_UINT32 xid);
    ACE_UINT32 xid(void);

    RFC2131::DhcpCtx &ctx(void);
    ElemDef &optionMap(void);

    ACE_INT32 process_timeout(const void *act);
  };
}


class CPServer : public UniIPC, public UniTimer
{
private:
  ACE_Message_Block *m_mb;
  ACE_CString m_description;
  DhcpServerState *m_state;

public:
  CPServer(ACE_CString ipStr, ACE_UINT8 facility, ACE_UINT8 instance,
         ACE_CString nodeTag) :
    UniIPC(ipStr, facility, instance, nodeTag)
  {
  }

  virtual ~CPServer();

  void setState(DhcpServerState *st);
  DhcpServerState *getState(void);

  ACE_INT8 start();
  ACE_INT8 stop();

  ACE_UINT32 handle_ipc(ACE_UINT8 *req, ACE_UINT32 reqLen);
  ACE_INT32 process_timeout(const void *act);

};



#endif /*__DHCP_SERVER_H__*/
