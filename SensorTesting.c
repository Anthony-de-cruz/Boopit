#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"
#include "Board_LED.h"                  // Board Support:LED
#define wait_delay HAL_Delay


#define TIME 1000000

void touchSensor(void);  //works with button too
void photoresistorSensor(void);
void MX_ADC_Init(void);
void MX_GPIO_Init(void);
ADC_HandleTypeDef hadc;

int main(void){

    
    photoresistorSensor();
}



void touchSensor(void){
    GPIO_InitTypeDef gpio; 
    
    
    	  LED_Initialize(); 
	
	__HAL_RCC_GPIOC_CLK_ENABLE();
 

	gpio.Mode = GPIO_MODE_INPUT;
	gpio.Pull = GPIO_PULLDOWN; 
	gpio.Speed = GPIO_SPEED_HIGH; 
    
    gpio.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOC, &gpio);
    
    while(1){
        
       if( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6)  ){
       
            LED_On(0U);
       }
       
       else{
           LED_Off(0U); 
       }
    }

}

void photoresistorSensor(void){
    GPIO_InitTypeDef gpio; 
    unsigned int value;
    uint16_t adc_read;


 
   	  LED_Initialize(); 
	
	__HAL_RCC_GPIOC_CLK_ENABLE();
    MX_GPIO_Init();
	MX_ADC_Init();
    HAL_Init();
   
    
        
    while(1){
   
		if(HAL_ADC_GetValue(&hadc) > 700){
            LED_On(0U);
        }
        else{
            LED_Off(0U);
        }
        
        
		//wait_delay(1);        

    }
}
    
    
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();
	/* The voltage scaling allows optimizing the power
	consumption when the device is clocked below the
	maximum system frequency. */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/* Enable HSE Oscillator and activate PLL
	with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);
	/* Select PLL as system clock source and configure
	the HCLK, PCLK1 and PCLK2 clocks dividers */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | 
	RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}



// init ADC configuration 
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
	hadc.Init.Resolution = ADC_RESOLUTION_10B;
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


