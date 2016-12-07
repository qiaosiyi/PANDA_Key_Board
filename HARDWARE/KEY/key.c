#include "key.h"
#include "sys.h"
#include "delay.h"
void KEY_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

}
u8 KEY_Scan(u8 mode){
	static u8 key_up=1;
	if(mode)key_up = 1;
	if(key_up&&(KEY0==0)){
		delay_ms(10);
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
	}else if(KEY0==1)key_up=1;
	return 0;
}
