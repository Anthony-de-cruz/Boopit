#include "game.h"
#include "display.h"

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"
#include "Board_LED.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define wait_delay HAL_Delay

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

int score = 0;
int lives = 3;

ADC_HandleTypeDef hadcPhoto;
//ADC_HandleTypeDef hadcJoyX;
ADC_HandleTypeDef hadcJoyY;


bool photo_sensor(void){
    
    	if(HAL_ADC_GetValue(&hadcPhoto) > 1000){
            //LED_On(0U);
                return true;
        }
        else{
            //LED_Off(0U);
            return false;
        }
}
bool button_sensor(void){
        //while(1){
        
       if( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)  ){
          //  LED_On(0U);
           return false;
       }
       
       else{
        //   LED_Off(0U);   
           return true;
       }
    //}
}
bool Joystick_sensor(void){ 
        
    	if(HAL_ADC_GetValue(&hadcJoyY) < 400  || HAL_ADC_GetValue(&hadcJoyY) > 800 ){
            //LED_On(0U);
                return true;
        }
        else{
            //LED_Off(0U);
            return false;
        }
}

//D1
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
    
    
        char *title = "BOOPIT!";
    
    TOUCH_STATE tsc_state;
    
    //general	
    GPIO_InitTypeDef gpio;
    LED_Initialize();     
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    //analogue	
    MX_ADC_Init_Photo();
    //MX_ADC_Init_JoyX(); 
    MX_ADC_Init_JoyY();
    MX_GPIO_Init_Photo();
    //MX_GPIO_Init_JoyX();
    MX_GPIO_Init_JoyY();
    HAL_Init();
   
    //digital
	gpio.Mode = GPIO_MODE_INPUT;
	gpio.Pull = GPIO_PULLDOWN; 
	gpio.Speed = GPIO_SPEED_HIGH; 
    
    gpio.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOC, &gpio);
    
    //display
    SystemClock_Config(); //Config Clocks
    Touch_Initialize(); // Init Touchscreen
    GLCD_Initialize(); //Init GLCD
    
    GLCD_ClearScreen();
    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_SetBackgroundColor(GLCD_COLOR_WHITE);
    GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
  
    //Game settings
    //srand(time(NULL));
    //random = rand() % 3;
    random = 3;
    timeLimit = 7000; // in ms
    timeCurrent = 0;
    
    
    //while(timeCurrent < timeLimit){
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
            taskCompleted = Joystick_sensor();
        }
    
    
        //check completed
        if(taskCompleted){
            LED_On(0u);
            score++;
            //wait_delay(1);
            //exit(1);
        }
        else{
            LED_Off(0U);
            lives--;
        }
        
        wait_delay(10);
        timeCurrent += 10;
        sprintf(debug_buffers[1], "timeCurrent: %i   ", timeCurrent);        
        sprintf(debug_buffers[0], "JOYSTICK: %i   ", HAL_ADC_GetValue(&hadcJoyY));

        
        GLCD_SetFont(&GLCD_Font_16x24);
       
        
        draw_game_screen();
    }
}



//Photo Resistor
void MX_ADC_Init_Photo(void)
{
    ADC_ChannelConfTypeDef sConfig;
 
	// Enable ADC CLOCK
	//__HAL_RCC_ADC1_CLK_ENABLE();
	//__HAL_RCC_ADC2_CLK_ENABLE();
	__HAL_RCC_ADC3_CLK_ENABLE();

	/// Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)	
	hadcPhoto.Instance = ADC3; //# Select the ADC (ADC1, ADC2, ADC3)
	hadcPhoto.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadcPhoto.Init.Resolution = ADC_RESOLUTION_12B;
	hadcPhoto.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadcPhoto.Init.NbrOfConversion = 3;
    hadcPhoto.Init.ScanConvMode = ENABLE;
	hadcPhoto.Init.ContinuousConvMode = ENABLE;
	hadcPhoto.Init.DiscontinuousConvMode = DISABLE;
	HAL_ADC_Init(&hadcPhoto);
	//configure channal
	sConfig.Rank = 1;
	sConfig.Channel = ADC_CHANNEL_0;//# Select the ADC Channel (ADC_CHANNEL_X)
	sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	HAL_ADC_ConfigChannel(&hadcPhoto, &sConfig);
	HAL_ADC_Start(&hadcPhoto);
	HAL_ADC_PollForConversion(&hadcPhoto, HAL_MAX_DELAY);
}

 
GPIO_InitTypeDef GPIO_InitStruct_Photo;
void MX_GPIO_Init_Photo(void){
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct_Photo.Mode = GPIO_MODE_ANALOG; // configure to analog input mode
    GPIO_InitStruct_Photo.Pin = GPIO_PIN_0;// #select GPIO GPIO_PIN_X
    GPIO_InitStruct_Photo.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct_Photo);// #select GPIO Group
}

/*
//Joystick X
void MX_ADC_Init_JoyX(void)
{
    ADC_ChannelConfTypeDef sConfigJoyX;
 
	// Enable ADC CLOCK
	//__HAL_RCC_ADC1_CLK_ENABLE();
	//__HAL_RCC_ADC2_CLK_ENABLE();
    __HAL_RCC_ADC3_CLK_ENABLE();

	// Configure the global features of the ADC (Clock, Resolution, Data Alignment and number
	of conversion) 	
	hadcJoyX.Instance = ADC3; //# Select the ADC (ADC1, ADC2, ADC3)
	hadcJoyX.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadcJoyX.Init.Resolution = ADC_RESOLUTION_10B;
	hadcJoyX.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadcJoyX.Init.NbrOfConversion = 3;
    hadcJoyX.Init.ScanConvMode = ENABLE;
	hadcJoyX.Init.ContinuousConvMode = ENABLE;
	hadcJoyX.Init.DiscontinuousConvMode = DISABLE;
	HAL_ADC_Init(&hadcJoyX);
	//configure channal
	sConfigJoyX.Rank = 3;
	sConfigJoyX.Channel = ADC_CHANNEL_8;//# Select the ADC Channel (ADC_CHANNEL_X)
	sConfigJoyX.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	HAL_ADC_ConfigChannel(&hadcJoyX, &sConfigJoyX);
	HAL_ADC_Start(&hadcJoyX);
	HAL_ADC_PollForConversion(&hadcJoyX, HAL_MAX_DELAY);
}

GPIO_InitTypeDef GPIO_InitStructJoyX;
void MX_GPIO_Init_JoyX(void){
    __HAL_RCC_GPIOF_CLK_ENABLE();
    GPIO_InitStructJoyX.Mode = GPIO_MODE_ANALOG; // configure to analog input mode
    GPIO_InitStructJoyX.Pin = GPIO_PIN_10;// #select GPIO GPIO_PIN_X
    GPIO_InitStructJoyX.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStructJoyX);// #select GPIO Group
}
*/

//Joystick Y
void MX_ADC_Init_JoyY(void)
{
    ADC_ChannelConfTypeDef sConfigJoyY;
 
	/* Enable ADC CLOCK */
	//__HAL_RCC_ADC1_CLK_ENABLE();
	//__HAL_RCC_ADC2_CLK_ENABLE();
    __HAL_RCC_ADC3_CLK_ENABLE();

	/* Configure the global features of the ADC (Clock, Resolution, Data Alignment and number
	of conversion) */		
	hadcJoyY.Instance = ADC3; //# Select the ADC (ADC1, ADC2, ADC3)
	hadcJoyY.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
	hadcJoyY.Init.Resolution = ADC_RESOLUTION_10B;
	hadcJoyY.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadcJoyY.Init.NbrOfConversion = 3;
    hadcJoyY.Init.ScanConvMode = ENABLE;
	hadcJoyY.Init.ContinuousConvMode = ENABLE;
	hadcJoyY.Init.DiscontinuousConvMode = DISABLE;
	HAL_ADC_Init(&hadcJoyY);
	//configure channal
	sConfigJoyY.Rank = 3;
	sConfigJoyY.Channel = ADC_CHANNEL_7;//# Select the ADC Channel (ADC_CHANNEL_X)
	sConfigJoyY.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	HAL_ADC_ConfigChannel(&hadcJoyY, &sConfigJoyY);
	HAL_ADC_Start(&hadcJoyY);
	HAL_ADC_PollForConversion(&hadcJoyY, HAL_MAX_DELAY);
}

GPIO_InitTypeDef GPIO_InitStructJoyY;
void MX_GPIO_Init_JoyY(void){
    __HAL_RCC_GPIOF_CLK_ENABLE();
    GPIO_InitStructJoyY.Mode = GPIO_MODE_ANALOG; // configure to analog input mode
    GPIO_InitStructJoyY.Pin = GPIO_PIN_9;// #select GPIO GPIO_PIN_X
    GPIO_InitStructJoyY.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStructJoyY);// #select GPIO Group
}

