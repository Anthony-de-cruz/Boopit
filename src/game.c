#include "game.h"

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"
#include "Board_LED.h"
#include <stdbool.h>
#include <stdlib.h>

int score = 0;
int lives = 3;

ADC_HandleTypeDef hadc;


bool photo_sensor(void){
    
    		if(HAL_ADC_GetValue(&hadc) > 2000){
            //LED_On(0U);
                return true;
        }
        else{
            //LED_Off(0U);
            return false;
        }
}
bool button_sensor(void){
    return true;
}
bool microphone_sensor(void){ return true;
}

bool touch_sensor(void){
    
    //while(1){
        
       if( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6)  ){
          //  LED_On(0U);
           return true;
       }
       
       else{
        //   LED_Off(0U); 
           return false;
       }
    //}
}


void play_game(void){
    int timeLimit, random, timeCurrent;
    bool taskCompleted;
    
    //general	
    GPIO_InitTypeDef gpio;
    LED_Initialize();     
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    //analogue	
    MX_GPIO_Init();
	MX_ADC_Init();
    HAL_Init();
   
    //digital
	gpio.Mode = GPIO_MODE_INPUT;
	gpio.Pull = GPIO_PULLDOWN; 
	gpio.Speed = GPIO_SPEED_HIGH; 
    
    gpio.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOC, &gpio);
    
    random = rand() % 3;
    
    
    while(1){
            
    //find random 
    if(random ==0) {
    taskCompleted = touch_sensor();
    }
    else if(random ==1) {
        taskCompleted = photo_sensor();
    }
    else if(random ==2) {
        taskCompleted = button_sensor();
    }
    else if(random ==3) {
        taskCompleted = microphone_sensor();
    }
    
    
    //check completed
        if(taskCompleted){
            LED_On(0u);
        }
        else{
            LED_Off(0U);
        }
    }
}

ADC_HandleTypeDef hadc;
void MX_ADC_Init(void)
{
    ADC_ChannelConfTypeDef sConfig;
 
	/* Enable ADC CLOCK */
	//__HAL_RCC_ADC1_CLK_ENABLE();
	//__HAL_RCC_ADC2_CLK_ENABLE();
	__HAL_RCC_ADC3_CLK_ENABLE();

	/* Configure the global features of the ADC (Clock, Resolution, Data Alignment and number
	of conversion) */		
	hadc.Instance = ADC3; //# Select the ADC (ADC1, ADC2, ADC3)
	hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadc.Init.Resolution = ADC_RESOLUTION_12B;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.NbrOfConversion = 1;
    hadc.Init.ScanConvMode = ENABLE;
	hadc.Init.ContinuousConvMode = ENABLE;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	HAL_ADC_Init(&hadc);
	//configure channal
	sConfig.Rank = 1;
	sConfig.Channel = ADC_CHANNEL_0;//# Select the ADC Channel (ADC_CHANNEL_X)
	sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);
	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
}

// init GPIO for analog 
GPIO_InitTypeDef GPIO_InitStruct;
void MX_GPIO_Init(void){
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; // configure to analog input mode
    GPIO_InitStruct.Pin = GPIO_PIN_0;// #select GPIO GPIO_PIN_X
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);// #select GPIO Group
}
