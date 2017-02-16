#include "uip.h"
#include "app_server.h"
#include "spi.h"
#include <string.h>
#include <reg52.h>

code char ascii_code[10]={'1','2','3','4','5','6','7','8','9'};
//char ascii_num[6] = {0,0,0,0,0,0};

void delay(uint x)  //延时子程序
{
   	uint i,j;
   	for (i=0; i<x; i++)
   		for(j=0;j<=1105;j++);
}

void blink_led() 				//闪光灯，亮10ms
{
 	led_work = 0;
	delay(10);
	led_work = 1;
	delay(10);
}

void app_job(void) 
{
	//blink_led();
	//uip_send("GET /uip_server/put_data.php?mod=putdata&value=23.5695 HTTP/1.0\r\n\r\n",67);
	//uip_send("OK",2);	
}

void app_server_init(void) 
{
	struct uip_conn *conn;
	static uip_ipaddr_t addr;
	uip_ipaddr_t *ipaddr;
	ipaddr = &addr;	   	//避免空指针和出错，否则数据包发送不出来

	uip_ipaddr(ipaddr, 192, 168, 30, 129);  	//服务器IP地址
	conn = uip_connect(ipaddr, HTONS(8080));	//服务器端口
	if(conn == NULL){
    	return;
  	}else{
		blink_led();
		delay(500); 		//延时，以保证网络连接的正确性
		blink_led();	
	}
	//blink_led();	//初始化，闪灯	
	led_work = 1; 	//初始化，将灯熄灭	
}

void tcp_server_appcall(void) 
{
	/*
	if(uip_connected()){
		blink_led();
		uip_send("OK\n",3);	
	}

	if(uip_newdata() || uip_rexmit()){
	
		uip_send("ok\n", 3);
	}
	*/
	//uip_send("OK\n",3);
	uip_send("GET /uip_server/put_data.php?mod=putdata&value=23.5695 HTTP/1.0\r\n\r\n",67);
	delay(100);
}

