/*
 * Copyright (c) 2001, Adam Dunkels.
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Adam Dunkels.
 * 4. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: main.c,v 1.16 2006/06/11 21:55:03 adam Exp $
 *
 */


#include "uip.h"
#include "uip_arp.h"
#include "enc28j60.h"
#include "timer.h"

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

#ifndef NULL
#define NULL (void *)0
#endif /* NULL */

/*用来做TCP连接计时和ARP更新使用*******/
clock_time_t tick_cnt;
uint clock_j = 0;
uint app_job_t = 0;

/*时间戳*/
clock_time_t clock_time(void)
{
	return tick_cnt;
}

/*---------------------------------------------------------------------------*/
int
main(void)
{
  int i;
  struct timer periodic_timer, arp_timer;

  timer_set(&periodic_timer, CLOCK_SECOND / 2);
  timer_set(&arp_timer, CLOCK_SECOND * 10);
  
  tapdev_init();
  uip_init();
  uip_arp_init();	  	//初始化arp协议
  app_server_init();

  while(1)
  {
		uip_len = tapdev_read();	//从网络设置读取信息
		if(uip_len > 0)
		{
			if(BUF->type == htons(UIP_ETHTYPE_IP)) 
			{
				uip_arp_ipin();
				uip_input();
				/* If the above function invocation resulted in data that
				   should be sent out on the network, the global variable
				   uip_len is set to a value > 0. */
				if(uip_len > 0) 
				{
					uip_arp_out();
					tapdev_send();
				}
			} 
			else if(BUF->type == htons(UIP_ETHTYPE_ARP)) 
			{
				uip_arp_arpin();
				/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
				if(uip_len > 0) 
				{
					 tapdev_send();
				}
			}
		}
		else if(timer_expired(&periodic_timer)) 
		{
			timer_reset(&periodic_timer);
			for(i = 0; i < UIP_CONNS; i++) 
			{
				uip_periodic(i);
				/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
				if(uip_len > 0)
				{
					uip_arp_out();
					tapdev_send();
				}
			}

			#if UIP_UDP
			for(i = 0; i < UIP_UDP_CONNS; i++) 
			{
				uip_udp_periodic(i);
				// If the above function invocation resulted in data that
				//should be sent out on the network, the global variable
				//uip_len is set to a value > 0.
				if(uip_len > 0) 
				{
					uip_arp_out();
					tapdev_send();
				}
			}
			#endif

			/* Call the ARP timer function every 10 seconds. */
			if(timer_expired(&arp_timer)) 
			{
				timer_reset(&arp_timer);
				uip_arp_timer();
			}
		}
     /*张官海添加，用于作定期的ARP更新*/
	 if( ++clock_j == 1500){
	 	//大约这里为1000ms，当值为1000的时候
		tick_cnt++;		//每隔一段时间加1
		clock_j = 0;	//将计数清零
		//blink_led();	//新光灯，以判断是否工作
	 }

	 if( ++app_job_t == 1500){
	 	//定期的执行一些任务，最大为65500 毫秒 ，当然这个时钟不准确
		app_job();
		app_job_t = 0;	//将计数清零
	 }
  }
}
