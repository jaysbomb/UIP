#ifndef __APP_SERVER_H__
#define __APP_SERVER_H__

void blink_led(void);

void app_server_init(void);
void app_job(void);
void tcp_server_appcall(void);

#define UIP_APPCALL tcp_server_appcall		//TCP数据处理程序入口

typedef int uip_tcp_appstate_t;

#endif
