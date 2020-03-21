#ifndef __COMMONIF_H__
#define __COMMONIF_H__

#include <iostream>
#include <functional>
#include <ace/Basic_Types.h>

namespace CommonIF {

  static ACE_UINT8 FACILITY_DHCP       = 0x81;
  static ACE_UINT8 FACILITY_DNS        = 0x82;
  static ACE_UINT8 FACILITY_REDIR      = 0x83;
  static ACE_UINT8 FACILITY_RADIUS     = 0x84;
  static ACE_UINT8 FACILITY_AP         = 0x85;

  static ACE_UINT8 OFFSET              = 0x80;
  static ACE_UINT8 CONTAINER           = 0x80;
  static ACE_UINT8 INSTANCE1           = 0x01;
  static ACE_UINT8 INSTANCE2           = 0x02;
  static ACE_UINT8 INSTANCE3           = 0x03;
  static ACE_UINT8 INSTANCE4           = 0x04;

  static ACE_UINT32 SIZE_64MB          = (1 << 26);
  static ACE_UINT32 SIZE_32MB          = (1 << 25);
  static ACE_UINT32 SIZE_16MB          = (1 << 24);
  static ACE_UINT32 SIZE_8MB           = (1 << 23);
  static ACE_UINT32 SIZE_4MB           = (1 << 22);
  static ACE_UINT32 SIZE_2MB           = (1 << 21);
  static ACE_UINT32 SIZE_1MB           = (1 << 20);
  static ACE_UINT32 SIZE_1KB           = (1 << 10);

  ACE_UINT32 get_hash32(const ACE_UINT8 *nodeTag);
  ACE_UINT16 get_ipc_port(ACE_UINT8 facility, ACE_UINT8 instance);
  ACE_UINT16 get_ipc_port(ACE_UINT32 taskId);
  ACE_UINT32 get_task_id(ACE_UINT8 facility, ACE_UINT8 instance);
};



















#endif /*__COMMONIF_H__*/
