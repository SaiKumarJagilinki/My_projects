
 *DELAY*/
#include<lpc21xx.h>
#include"header.h"
void delay_sec(unsigned int sec)
{
T0PR=15000000-1;
T0PC=0;
T0TC=0;
T0TCR=1;
while(T0TC<sec);
T0TCR=0;
}
void delay_ms(unsigned int ms)
{
T0PR=15000-1;
T0PC=0;
T0TC=0;
T0TCR=1;
while(T0TC<ms);
T0TCR=0;
}
/*HEADER.H*/
#pragma once
#include<stdio.h>
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct t1
{
u8 sec;
u8 min;
u8 h12;
u8 date;
u8 month;
u8 day;
u8 year;
u8 dow;
} D_Type;
void delay_sec(unsigned int sec);
void delay_ms(unsigned int ms);
void timer1_init(void);
int extract_num(int n);
/*LCD*/
#define RS (1<<17)
#define RW (1<<18)
#define EN (1<<19)
void lcd_cmd(unsigned int );
void lcd_data(unsigned char);
void lcd_init(void);
void lcd_int(int);
void lcd_float(float);
void lcd_str(char*);
void lcd_cgram1(void);
void lcd_cgram2(void);
void lcd_cgram3(void);
void display_time(void);
void display_date(void);
/*uart protocol*/
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)
void uart_init(unsigned int);
void uart_tx(unsigned char);
unsigned char uart_rx(void);
void uart_tx_str(char*);
void uart_tx_int(int);
void uart_tx_float(float);
/*SPI PROTOCOL*/
#define SPIF (S0SPSR>>7&1)
#define CS (1<<7)
#define DONE (ADDR>>31&1)
void spi0_init(void);
u8 spi0_tx_rx(u8 data);
u32 mcp3204_adc_read(u8 ch_num);
void on_chip_adc_init(void);
u32 on_chip_adc_read(u8 ch_num);
/*I2C protocol*/
#define START (1<<5)
#define STOP (1<<4)
#define I2EN  (1<<6)
#define SI (1<<3)
#define AA (1<<2)
#define SIF ((I2CONSET>>3)&1)
void i2c_init(void);
void i2c_send(u8 SA,u8 MR,u8 data);
void i2c_data_send(u8 temp);
u8 i2c_data_read(u8 temp);
void i2c_start_condition(void);
void i2c_stop_condition(void);
u8 i2c_recieve(u8 SAR,u8 MR);
/*uart_driver.c*/
#include<lpc21xx.h>
#include"header.h"
void uart_init(unsigned int baud)
{
int pclk,res;
int a[]={15,60,30};
pclk=a[VPBDIV]*1000000;
res=pclk/(16*baud);
PINSEL0|=0x05;
U0LCR=0x83;
U0DLL=res&0xff;
U0DLM=(res>>8)&0xff;
U0LCR=0x03;
}
void uart_tx(unsigned char data)
{
U0THR=data;
while(THRE==0);
}
unsigned char uart_rx()
{
while(RDR==0);
return U0RBR;
}
void uart_tx_str(char*ptr)
{
while(*ptr)
uart_tx(*ptr++);
}
void uart_tx_int(int n)
{
char s[10];
sprintf(s,"%d",n);
uart_tx_str(s);
}
void uart_tx_float(float f)
{
int n1;
n1=f;
uart_tx_int(n1);
uart_tx('.');
n1=(f-n1)*10;
uart_tx_int(n1);
}
/*i2c_driver.c*/
#include<lpc21xx.h>
#include"header.h"
void i2c_init(void)
{
PINSEL0|=0x50;
I2CONSET=I2EN;
I2SCLL=I2SCLH=75;  //100KBPS
}
void i2c_send(u8 SAW,u8 MR,u8 data)
{
i2c_start_condition();
i2c_data_send(SAW);
if(I2STAT==0x20)
{
uart_tx_str("Error(send):SA+W\r\n");
goto end;
}
i2c_data_send(MR);
if(I2STAT==0x30)
{
uart_tx_str("Error(send):Memory\r\n");
goto end;
}
i2c_data_send(data);
if(I2STAT==0x30)
{
uart_tx_str("Error(send):Data write\r\n");
goto end;
}
end:
i2c_stop_condition();
}
u8 i2c_recieve(u8 SAR,u8 MR)
{
u8 res=0,temp;
i2c_start_condition();
temp=SAR^1;
i2c_data_send(temp);
if(I2STAT==0x20)
{
uart_tx_str("Error(recieve):SA+W\r\n");
goto end;
}
i2c_data_send(MR);
if(I2STAT==0x30)
{
uart_tx_str("Error(recieve):Memory\r\n");
goto end;
}
i2c_start_condition();
i2c_data_send(SAR);
if(I2STAT==0x48)
{
uart_tx_str("Error(recieve):SA+R\r\n");
goto end;
}
res=i2c_data_read(SAR);
end:
i2c_stop_condition();
return res;
}
void i2c_start_condition(void)
{
I2CONSET=START;
I2CONCLR=SI;
while(SIF==0);
I2CONCLR=START;
}
void i2c_stop_condition(void)
{
I2CONSET=STOP;
I2CONCLR=SI;
}
void i2c_data_send(u8 temp)
{
I2DAT=temp;
I2CONCLR=SI;
while(SIF==0);
}
u8 i2c_data_read(u8 temp)
{
I2CONCLR=SI;
while(SIF==0);
return I2DAT;
}
/*lcd_driver.c*/
#include<lpc21xx.h>
#include"header.h"
void lcd_init()
{
IODIR1=0xfe0000;
lcd_cmd(0x02);
lcd_cmd(0x01);
lcd_cmd(0x0e);
lcd_cmd(0x28);
}
void lcd_cmd(unsigned int cmd)
{
unsigned int temp;
IOCLR1=0xfe0000;
temp=(cmd&0xf0)<<16;
IOSET1=temp;
IOCLR1=RS;
IOCLR1=RW;
IOSET1=EN;
delay_ms(2);
IOCLR1=EN;
IOCLR1=0xfe0000;
temp=(cmd&0x0f)<<20;
IOSET1=temp;
IOCLR1=RS;
IOCLR1=RW;
IOSET1=EN;
delay_ms(2);
IOCLR1=EN;
}
void lcd_data(unsigned char data)
{
unsigned int temp;
IOCLR1=0xfe0000;
temp=(data&0xf0)<<16;
IOSET1=temp;
IOSET1=RS;
IOCLR1=RW;
IOSET1=EN;
delay_ms(2);
IOCLR1=EN;
IOCLR1=0xfe0000;
temp=(data&0x0f)<<20;
IOSET1=temp;
IOSET1=RS;
IOCLR1=RW;
IOSET1=EN;
delay_ms(2);
IOCLR1=EN;
}
void lcd_str(char*p)
{
while(*p!=0)
lcd_data(*p++);
}
void lcd_int(int n)
{
char s[10];
sprintf(s,"%d",n);
lcd_str(s);
}
void lcd_float(float f)
{
int n;
n=f;
lcd_int(n);
lcd_data('.');
n=(f-n)*10;
lcd_int(n);
}
void lcd_cgram1(void)
{
int i;
unsigned char a[]={0x1c,0x14,0x1c,0x00,0x00,0x00,0x00,0x00};
lcd_data(0);
lcd_cmd(0x40);
for(i=0;i<=7;i++)
lcd_data(a[i]);
}
void lcd_cgram2(void)
{
int i;
unsigned char a[]={0x1c,0x15,0x15,0x1c,0x11,0x11,0x10,0x00};
lcd_data(1);
lcd_cmd(0x48);
for(i=0;i<=7;i++)
lcd_data(a[i]);
}
void lcd_cgram3(void)
{
int i;
unsigned char a[]={0x10,0x11,0x11,0x10,0x11,0x11,0x1e,0x00};
lcd_data(2);
lcd_cmd(0x50);
for(i=0;i<=7;i++)
lcd_data(a[i]);
}
/*RTC_driver.c*/
#include"header.h"
char time_str[12];
char date_str[25];
char*days[]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
u8 h24,temp;
D_Type time;
void display_time(void)
{
time.h12=i2c_recieve(0xD1,0x02);
time.min=i2c_recieve(0xD1,0x01);
time.sec=i2c_recieve(0xD1,0x00);
temp=time.h12;
if(time.h12>>6&1)
{
time.h12=time.h12&0x1f;
time.h12= extract_num(time.h12);
}
else
time.h12=extract_num(time.h12);
time.min=extract_num(time.min);
time.sec=extract_num(time.sec);
sprintf(time_str,"%02d:%02d:%02d%s",time.h12,time.min,time.sec,(temp>>5&1)?"PM":"AM");
lcd_cmd(0x80);
lcd_str(time_str);
sprintf(time_str,"%02d:%02d:%02d %s ",time.h12,time.min,time.sec,(temp>>5&1)?"PM":"AM");
uart_tx_str(time_str);
}
void display_date(void)
{
time.dow=i2c_recieve(0xD1,0x03);
time.date=i2c_recieve(0xD1,0x04);
time.month=i2c_recieve(0xD1,0x05);
time.year=i2c_recieve(0xD1,0x06);
time.date= extract_num(time.date);
time.month= extract_num(time.month);
time.year= extract_num(time.year);
sprintf(date_str,"%02d/%02d/%02d",time.date,time.month,time.year);
lcd_cmd(0xc0);   
lcd_str(date_str);
sprintf(date_str," %02d/%02d/%02d %s\r\n",time.date,time.month,time.year,days[time.dow]);
uart_tx_str(date_str);
}
int extract_num(int n)
{
n=((n>>4)*10+(n&0x0f));
return n;
}
/*mcp3204_driver.c*/
#include<lpc21xx.h>
#include"header.h"
u32 mcp3204_adc_read(u8 ch_num)
{
u32 res=0;
u8 HB,LB;
ch_num<<=6;
IOCLR0=CS;
spi0_tx_rx(0x06);
HB=spi0_tx_rx(ch_num);
LB=spi0_tx_rx(0x00);
IOSET0=CS;
HB&=0x0F;
res=(HB<<8)|LB;
return res;
}
/*on_chip_adc_driver*/
#include<lpc21xx.h>
#include"header.h"
void on_chip_adc_init(void)
{
PINSEL1|=0x05000000;//p0.28 as ain1/ch1 &p0.29 as ain2/ch2
ADCR=0x00200900;//clkdiv=9,freq=1.5mhz
}
u32 on_chip_adc_read(u8 ch_num)
{
unsigned int res;
ADCR|=(1<<ch_num);//channel select
ADCR|=(1<<24); // start ADC reading
while(DONE==0);
ADCR&=~((1<<24)|(1<<ch_num)); //stop ADC reading
res=(ADDR>>6)&0x3ff;
return res;
}
/*spio_driver.c*/
#include <LPC21xx.H>
#include"header.h"
void spi0_init()
{
IODIR0=CS;
PINSEL0|=0x1500;
IOSET0=CS;
S0SPCR=0x20;
S0SPCCR=15;  //1 mhz
}
u8 spi0_tx_rx(u8 data)
{
S0SPDR=data;
while(SPIF==0);
return S0SPDR;
}
/*main.c*/
#include<lpc21xx.h>
#include"header.h"
#define Hour 0x72
#define Min 0x13
#define Sec 0x50
#define Date 0x03
#define Month 0x12
#define Year  0x25
#define Day  0x03
float T_vtg,P_vtg;
u32 LDR_adc_out,T_adc_out,LDR_PER,P_adc_out,T_deg;
char buf[60];
int main()
{
i2c_init();
lcd_init();
uart_init(9600);
spi0_init();
on_chip_adc_init();
i2c_send(0xD0,0x02,Hour);
i2c_send(0xD0,0x01,Min);
i2c_send(0xD0,0x00,Sec);
i2c_send(0xD0,0x03,Day);
i2c_send(0xD0,0x04,Date);
i2c_send(0xD0,0x05,Month);
i2c_send(0xD0,0x06,Year);
while(1)
{
display_time();
display_date();
LDR_adc_out=mcp3204_adc_read(2);  
T_adc_out=on_chip_adc_read(1);
P_adc_out=on_chip_adc_read(2);
T_vtg=(T_adc_out*3.3)/1023 ;
T_deg=(T_vtg-0.5)/0.01;
P_vtg=(P_adc_out*3.3)/1023;
LDR_PER=100-((LDR_adc_out*100)/4095);
lcd_cmd(0x8a);
sprintf(buf,"T:%d",T_deg);
lcd_str(buf);
lcd_cgram1();
lcd_cmd(0x8f);
lcd_data('C');
lcd_cmd(0xc8);
lcd_cgram2();
lcd_cmd(0xc9);
lcd_int((int)P_vtg);
lcd_data('V');
lcd_cmd(0xcb);
lcd_cgram3();
lcd_cmd(0xcc);
if(LDR_PER<=99)
sprintf(buf,"%02d%c ",LDR_PER,'%');
else
sprintf(buf,"%03d%c",LDR_PER,'%');
lcd_str(buf);
sprintf(buf,"TEMP= %d°C Pot=%.1fV LIGHT=%d%c\r\n",T_deg,P_vtg,LDR_PER,'%');
uart_tx_str(buf);
delay_ms(1000);
}
}
