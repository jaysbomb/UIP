#include "uip.h"
#include "app_server.h"
#include "spi.h"
#include <string.h>
#include <reg52.h>

code char ascii_code[10]={'1','2','3','4','5','6','7','8','9'};
//char ascii_num[6] = {0,0,0,0,0,0};

void delay(uint x)  //��ʱ�ӳ���
{
   	uint i,j;
   	for (i=0; i<x; i++)
   		for(j=0;j<=1105;j++);
}

void blink_led() 				//����ƣ���10ms
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
	ipaddr = &addr;	   	//�����ָ��ͳ����������ݰ����Ͳ�����

	uip_ipaddr(ipaddr, 192, 168, 30, 129);  	//������IP��ַ
	conn = uip_connect(ipaddr, HTONS(8080));	//�������˿�
	if(conn == NULL){
    	return;
  	}else{
		blink_led();
		delay(500); 		//��ʱ���Ա�֤�������ӵ���ȷ��
		blink_led();	
	}
	//blink_led();	//��ʼ��������	
	led_work = 1; 	//��ʼ��������Ϩ��	
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

