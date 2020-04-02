#ifndef __DHCP_COMMON_H__
#define __DHCP_COMMON_H__

namespace RFC2131
{
  /*DHCP Message Type*/
  static const ACE_UINT8 DISCOVER = 1;
  static const ACE_UINT8 OFFER = 2;
  static const ACE_UINT8 REQUEST = 3;
  static const ACE_UINT8 DECLINE = 4;
  static const ACE_UINT8 ACK = 5;
  static const ACE_UINT8 NACK = 6;
  static const ACE_UINT8 RELEASE = 7;

  /*DHCP OPTIONS*/
  static const ACE_UINT8 OPTION_PADD = 0;
  static const ACE_UINT8 OPTION_SUBNET_MASK = 1;
  static const ACE_UINT8 OPTION_ROUTER = 3;
  static const ACE_UINT8 OPTION_TIME_SERVER = 4;
  static const ACE_UINT8 OPTION_NAME_SERVER = 5;
  static const ACE_UINT8 OPTION_DNS = 6;
  static const ACE_UINT8 OPTION_LOG_SERVER = 7;
  static const ACE_UINT8 OPTION_QUOTE_SERVER = 8;
  static const ACE_UINT8 OPTION_IMPRESS_SERVER = 10;
  static const ACE_UINT8 OPTION_ROUTER_LOCATION_SERVER = 11;
  static const ACE_UINT8 OPTION_HOST_NAME = 12;
  static const ACE_UINT8 OPTION_DOMAIN_NAME = 15;
  /*Interface MTU*/
  static const ACE_UINT8 OPTION_MTU = 26;
  static const ACE_UINT8 OPTION_BROADCAST_ADDRESS = 28;
  static const ACE_UINT8 OPTION_NIS_DOMAIN = 40;
  static const ACE_UINT8 OPTION_NIS = 41;
  static const ACE_UINT8 OPTION_NTP_SERVER = 42;
  static const ACE_UINT8 OPTION_VENDOR_SPECIFIC_INFO = 43;
  static const ACE_UINT8 OPTION_REQUESTED_IP_ADDRESS = 50;
  static const ACE_UINT8 OPTION_IP_LEASE_TIME = 51;
  static const ACE_UINT8 OPTION_OVERLOAD = 52;
  static const ACE_UINT8 OPTION_MESSAGE_TYPE = 53;
  static const ACE_UINT8 OPTION_SERVER_IDENTIFIER = 54;
  static const ACE_UINT8 OPTION_PARAMETER_REQUEST_LIST = 55;
  static const ACE_UINT8 OPTION_MESSAGE = 56;
  static const ACE_UINT8 OPTION_MESSAGE_SIZE = 57;
  static const ACE_UINT8 OPTION_RENEWAL_TIME_T1 = 58;
  static const ACE_UINT8 OPTION_RENEWAL_TIME_T2 = 59;
  static const ACE_UINT8 OPTION_CLASS_IDENTIFIER = 60;
  static const ACE_UINT8 OPTION_CLIENT_IDENTIFIER = 61;
  static const ACE_UINT8 OPTION_RAPID_COMMIT = 80;
  static const ACE_UINT8 OPTION_AUTO_CONFIGURE = 116;
  static const ACE_UINT8 OPTION_END = 255;

}

#endif /*__DHCP_COMMON_H__*/
