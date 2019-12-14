#ifndef __IPC_H__
#define __IPC_H__

#include <cstdio>
#include <unordered_map>
#include <list>

typedef std::unordered_map<ACE_UINT32, ACE_INET_Addr>taskIdToPeerMap_t;
typedef taskIdToPeerMap_t::iterator taskIdToPeerMapIter_t;

typedef std::unordered_map<long, const void *>timerUMap_t;
typedef timerUMap_t::iterator timerUMap_iter;

struct _timerToken
{
  /*! TimerId.*/
  long m_timerId;
  /*! Asynchronous Callback Token.*/
  const void *m_act;

  _timerToken()
  {
    m_timerId = 0;
    m_act = NULL;
  }

  _timerToken(long tId, const void *act)
  {
    m_timerId = tId;
    m_act = act;
  }

  ~_timerToken()
  {
    /*! Do nothing */
  }

  long timerId(void)
  {
    return(m_timerId);
  }

  void timerId(long tId)
  {
    m_timerId = tId;
  }

  const void *act(void)
  {
    return(m_act);
  }

  void act(const void *act)
  {
    m_act = act;
  }

};

typedef struct _timerToken _timerToken_t;

class Timer_ : public ACE_Event_Handler
{
  private:
    std::list<_timerToken_t *> m_timerTokenList;

  public:

    Timer_();
    virtual ~Timer_();

    virtual ACE_INT32 handle_timeout(ACE_Time_Value &tv, const void *act=0);
    /*!This will be overridden in subclass.*/
    virtual ACE_INT32 processTimeout(const void *act);

    long startTimer(ACE_Time_Value &delay, const void *act, ACE_Time_Value interval);
    void stopTimer(long timerId);
};


class IPC_ : public ACE_Task<ACE_MT_SYNCH>
{
  private:
    ACE_UINT32 m_magic;
    /*IPC - data member */
    ACE_HANDLE m_handle;
    ACE_INET_Addr m_ipcAddr;
    ACE_SOCK_Dgram m_dgram;
    /*IPC - Details */
    ACE_UINT8 m_container;
    ACE_UINT8 m_component;
    ACE_UINT8 m_facility;
    ACE_UINT8 m_instance;
    ACE_UINT32 m_ipcPort;
    ACE_CString m_ipAddr;
    taskIdToPeerMap_t m_taskIdToPeerUMap;

  public:
    IPC_();
    IPC_(char *ipAddr, ACE_UINT8 container, ACE_UINT8 component,
         ACE_UINT8 facility, ACE_UINT8 instance);

    virtual ~IPC_();

    ACE_UINT32 ipcPort(void);
    void ipcPort(ACE_UINT32 ipcPort);

    ACE_UINT8 container(void);
    void container(ACE_UINT8 container);

    ACE_UINT8 component(void);
    void component(ACE_UINT8 component);

    ACE_UINT8 facility(void);
    void facility(ACE_UINT8 facility);

    ACE_UINT8 instance(void);
    void instance(ACE_UINT8 instance);

    ACE_UINT32 magic(void);
    void magic(ACE_UINT32 magic);

    ACE_HANDLE handle(void);
    void handle(ACE_HANDLE);

    ACE_UINT32 getMyTaskId(void);

    /*! ACE Hook method */
    virtual ACE_INT32 handle_input(ACE_HANDLE handle);
    virtual ACE_HANDLE get_handle(void) const;

    /*! IPC Hook Method */
    virtual ACE_UINT32 processRequest(ACE_UINT8 *req, ACE_UINT32 reqLen);
};


class VapgTask : public IPC_
{
  public:
    VapgTask(char *ipAddr, ACE_UINT8 container, ACE_UINT8 component, ACE_UINT8 facility, ACE_UINT8 instance)
      : IPC_(ipAddr, container, component, facility, instance)
    {
      m_timer = NULL;
    }
    Timer_ *m_timer;

    VapgTask():IPC_()
    {
      m_timer = NULL;
    }

};







































#endif /*__IPC_H__*/
