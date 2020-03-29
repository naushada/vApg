#ifndef __CPGATEWAY_STATE_ACTIVATED_CC__
#define __CPGATEWAY_STATE_ACTIVATED_CC__

#include "CPGatewayStateActivated.h"
#include "ace/Log_Msg.h"

CPGatewayStateActivated *CPGatewayStateActivated::m_instance = NULL;

CPGatewayStateActivated::CPGatewayStateActivated()
{
  ACE_TRACE("CPGatewayStateActivated::CPGatewayStateActivated\n");
  ACE_CString desc("CPGatewayStateActivated");
  description(desc);
}

virtual CPGatewayStateActivated::~CPGatewayStateActivated()
{
  ACE_TRACE("CPGatewayStateActivated::~CPGatewayStateActivated\n");
}

static CPGatewayStateActivated *CPGatewayStateActivated::instance()
{
  ACE_TRACE("CPGatewayStateActivated::instance\n");

  if(!m_instance)
  {
    m_instance = new CPGatewayStateActivated();
  }

  return(m_instance);
}

void CPGatewayStateActivated::onEntry(CPGateway *parent)
{
  ACE_TRACE("CPGatewayStateActivated::onEntry\n");

}

void CPGatewayStateActivated::onExit(CPGateway *parent)
{
  ACE_TRACE("CPGatewayStateActivated::onExit\n");

}

ACE_UINT32 CPGatewayStateActivated::lock(CPGateway *parent)
{
  ACE_TRACE("CPGatewayStateActivated::lock\n");

  return(0);
}

ACE_UINT32 CPGatewayStateActivated::unlock(CPGateway *parent)
{
  ACE_TRACE("CPGatewayStateActivated::unlock\n");

  return(0);
}

#endif /*__CPGATEWAY_STATE_ACTIVATED_CC__*/
