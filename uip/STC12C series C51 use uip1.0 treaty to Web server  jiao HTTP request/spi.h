#ifndef SPI_H
#define SPI_H
#include <reg52.h>

sbit CSN =  	P2^0;	// 28J60-- CS(SS)
sbit SIN = 		P2^1;	// MOSI
sbit SON =  	P2^2;	// MISO
sbit SCKN =		P2^3;	// SCK
sbit led_work = P0^0; 	//工作闪光灯的接口

sbit INTN = 	P3^3;	// INT 

void WriteByte(u8_t temp);
u8_t ReadByte(void);
#endif
