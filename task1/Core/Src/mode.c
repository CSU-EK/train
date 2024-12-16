#include "mode.h"
#include "main.h"
#include "tim.h"


uint8_t mode_flag = 0;
uint16_t pulsewidth = 0;
uint8_t dir = 1;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		mode_flag = !mode_flag;
		if(mode_flag){
			HAL_TIM_Base_Stop_IT(&htim3);
			HAL_TIM_PWM_Start_IT(&htim14,TIM_CHANNEL_1);
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,1);
		}
		else{
			HAL_TIM_PWM_Stop(&htim14,TIM_CHANNEL_1);
			HAL_TIM_Base_Start_IT(&htim3);
		}
	}
	if(htim->Instance == TIM3)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	}
}
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance != TIM14){return;}
	if(dir)
	{
		pulsewidth++;
		if(pulsewidth>=195){
			pulsewidth = 195;
			dir = 0;}
	}else{
		pulsewidth--;
		if(pulsewidth<=5){
			pulsewidth = 5;
			dir = 1;}
	}
	__HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,pulsewidth);
}
