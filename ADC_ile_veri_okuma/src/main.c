
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint8_t ADC_Deger;

GPIO_InitTypeDef pot;
ADC_InitTypeDef ADCInitstructure;
ADC_CommonInitTypeDef ADC_Commoninitstructure;


static void Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE );

	pot.GPIO_Mode=GPIO_Mode_OUT;
	pot.GPIO_OType=GPIO_OType_PP;
	pot.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	pot.GPIO_PuPd=GPIO_PuPd_NOPULL;
	pot.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &pot);

	pot.GPIO_Mode=GPIO_Mode_AN; //analog mode
	pot.GPIO_Pin=GPIO_Pin_0;
	pot.GPIO_OType=GPIO_OType_PP;
	pot.GPIO_PuPd=GPIO_PuPd_NOPULL;
	pot.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &pot);

	ADCInitstructure.ADC_Resolution=ADC_Resolution_8b;
	ADC_Init(ADC1, &ADCInitstructure);

	ADC_Commoninitstructure.ADC_Mode=ADC_Mode_Independent;
	ADC_Commoninitstructure.ADC_Prescaler=ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_Commoninitstructure);

	ADC_Cmd(ADC1, ENABLE);
}


uint16_t Read_ADC(void)
{
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 1 , ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);

	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);

	return ADC_GetConversionValue(ADC1);

}

int main()
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_All);

	Config();
	while(1)
	{
		ADC_Deger=Read_ADC(); // 0-255

		switch(ADC_Deger)
		{

		case 25:
			 GPIO_ResetBits(GPIOD, GPIO_Pin_All);
			break;
		case 75:
			 GPIO_SetBits(GPIOD, GPIO_Pin_12);
			 GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 );
			break;
		case 120:
			GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13);
			GPIO_ResetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15 );
			break;
		case 175:
			GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15 );
			break;
		case 200:
			GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
			break;

		}

	}

}























void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
