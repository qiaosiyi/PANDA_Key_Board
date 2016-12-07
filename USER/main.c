#include "sys.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "wakeup.h"
#include "usart.h"
int main(void){
	u8 key=0;
	u8 keydown=0;
	u32 waittime=0;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);
	LED_Init();
	KEY_Init();
	WAKEUP_Init();
	LED0=1;
	WAKEUP=1;//蓝牙开启
	while(1){
		key=KEY_Scan(1);

		if(key != 0 && WAKEUP == 1){//如果有按键按下,而且蓝牙正在工作
			waittime = 0;//将等待时间清零
		}else if(key != 0 && WAKEUP == 0){//如果有按键按下,而且蓝牙正在待机
			waittime = 0;//将等待时间清零
			WAKEUP=1;//启动蓝牙
			LED0=1;
			delay_ms(20);//等待蓝牙启动成功
		}else if(key == 0){//如果没有按键被按下，等待时间加1个单位，1个单位按10ms计算
			if(WAKEUP==1){//如果蓝牙开机，才开始算等待时间
				waittime++;
			}
		}

		if(waittime>=1000){//如果等了超过300秒
			WAKEUP=0;//关闭蓝牙
			LED0=0;//
			waittime=0;
		}

		if(key==KEY0_PRES){
			LED0=0;
			if(keydown==0){
				printf("%c%c%c%c%c%c%c%c%c%c%c%c",
					0x0c,0x00,0xa1,0x01,0x00,0x00,0x29,0x00,0x00,0x00,0x00,0x00);
				keydown=1;
			}  
		}else{
			LED0=1;
			if(keydown==1){
				printf("%c%c%c%c%c%c%c%c%c%c%c%c",
					0x0c,0x00,0xa1,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
				keydown=0;
			}
		}
		delay_ms(10);
	}
}
