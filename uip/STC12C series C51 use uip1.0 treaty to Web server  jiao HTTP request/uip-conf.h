/**
 * \addtogroup uipopt
 * @{
 */

/**
 * \name Project-specific configuration options
 * @{
 *
 * uIP has a number of configuration options that can be overridden
 * for each project. These are kept in a project-specific uip-conf.h
 * file and all configuration names have the prefix UIP_CONF.
 */

/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack
 *
 * $Id: uip-conf.h,v 1.6 2006/06/12 08:00:31 adam Exp $
 */

/**
 * \file
 *         An example uIP configuration file
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#ifndef __UIP_CONF_H__
#define __UIP_CONF_H__

//zgh  #include <inttypes.h>

/**
 * 8 bit datatype
 *
 * This typedef defines the 8-bit type used throughout uIP.
 *
 * \hideinitializer
 */
typedef unsigned char u8_t;

/**
 * 16 bit datatype
 *
 * This typedef defines the 16-bit type used throughout uIP.
 *
 * \hideinitializer
 */
typedef unsigned int u16_t;

/**
 * 32 bit datatype
 *
 */

typedef unsigned long u32_t;

/**
 * Statistics datatype
 *
 * This typedef defines the dataype used for keeping statistics in
 * uIP.
 *
 * \hideinitializer
 */
typedef unsigned short uip_stats_t;

//张官海为C51添加
#define uchar unsigned char
#define uint unsigned int

/**
 * Maximum number of TCP connections.
 *
 * \hideinitializer
 */
#define UIP_CONF_MAX_CONNECTIONS 10 /* 40 原来*/

/**
 * Maximum number of listening TCP ports.
 *
 * \hideinitializer
 */
#define UIP_CONF_MAX_LISTENPORTS 10 /* 40 原来*/

/**
 * uIP buffer size.
 *
 * \hideinitializer
 */
#define UIP_CONF_BUFFER_SIZE    200		/* 420 原来*/

/**
 * CPU byte order.
 *
 * \hideinitializer
 */
#define UIP_CONF_BYTE_ORDER      UIP_BIG_ENDIAN /* 改过 原来*/

/**
 * Logging on or off
 *
 * \hideinitializer
 */
#define UIP_CONF_LOGGING         0 /*暂时关闭日志文件*/

/**
 * UDP support on or off
 *
 * \hideinitializer
 */
#define UIP_CONF_UDP             0		//是否支持UDP


#define UIP_CONF_UDP_CONNS		10		//最大允许同时连接的UDP数量

/**
 * UDP checksums on or off
 *
 * \hideinitializer
 */
#define UIP_CONF_UDP_CHECKSUMS   0	  	//不需要验证

/**
 * uIP statistics on or off
 *
 * \hideinitializer
 */
#define UIP_CONF_STATISTICS      1

/*消除告警，增加以下定义*/
#define UIP_CONF_IPV6            0 	  	//是否启用IPV6
#define UIP_ARCH_ADD32           0
#define UIP_ARCH_CHKSUM          0

/* Here we include the header file for the application(s) we use in
   our project. */
/*#include "smtp.h"*/
/*#include "hello-world.h"*/
/*#include "telnetd.h"*/
/*#include "webserver.h"*/
/*#include "dhcpc.h"*/
/*#include "resolv.h"*/
/*#include "webclient.h"*/

#include "app_server.h"
#include <reg52.h>

//是否采用宏配置网络地址
#define UIP_FIXEDADDR    1

//IP地址
#define UIP_IPADDR0     192		/**< The first octet of the IP address of this uIP node, if UIP_FIXEDADDR is */
#define UIP_IPADDR1     168		/**< The second octet of the IP address of this uIP node, if UIP_FIXEDADDR is*/
#define UIP_IPADDR2     30		/**< The third octet of the IP address of this uIP node, if UIP_FIXEDADDR is*/
#define UIP_IPADDR3     139		/**< The fourth octet of the IP address of this uIP node, if UIP_FIXEDADDR is*/

//子网掩码
#define UIP_NETMASK0    255		/**< The first octet of the netmask of this uIP node, if UIP_FIXEDADDR is 1. hideinitializer */
#define UIP_NETMASK1    255		/**< The second octet of the netmask of this uIP node, if UIP_FIXEDADDR is*/
#define UIP_NETMASK2    255		/**< The third octet of the netmask of this uIP node*/
#define UIP_NETMASK3    0		/**< The fourth octet of the netmask of this uIP node */

//默认网关
#define UIP_DRIPADDR0   192		/**< The first octet of the IP address of the default router */
#define UIP_DRIPADDR1   168		/**< The second octet of the IP address of the default router*/
#define UIP_DRIPADDR2   30		/**< The third octet of the IP address of the default router*/
#define UIP_DRIPADDR3   1		/**< The fourth octet of the IP address of the default router*/

/**
 * Specifies if the uIP ARP module should be compiled with a fixed
 * Ethernet MAC address or not.
 *
 * If this configuration option is 0, the macro uip_setethaddr() can
 * be used to specify the Ethernet address at run-time.
 *
 * \hideinitializer
 */
#define UIP_FIXEDETHADDR 1

#define UIP_ETHADDR0    0x45  /**< The first octet of the Ethernet address if UIP_FIXEDETHADDR is 1. \hideinitializer */
#define UIP_ETHADDR1    0x34  /**< The second octet of the Ethernet address */
#define UIP_ETHADDR2    0x56  /**< The third octet of the Ethernet address*/
#define UIP_ETHADDR3    0x78  /**< The fourth octet of the Ethernet address */
#define UIP_ETHADDR4    0x90  /**< The fifth octet of the Ethernet address*/
#define UIP_ETHADDR5    0xAB  /**< The sixth octet of the Ethernet address*/

#endif /* __UIP_CONF_H__ */

/** @} */
/** @} */
