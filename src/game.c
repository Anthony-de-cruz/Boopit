#include "game.h"
#include "sensor.h"
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

extern ADC_HandleTypeDef hadcPhoto;
extern ADC_HandleTypeDef hadcJoyY;

#ifdef __RTX
extern uint32_t os_time;
uint32_t HAL_GetTick(void) {
	return os_time;
}
#endif


int score = 0;
int lives = 3;



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
    int startTime = 0, timeCurrent = 0, timeLimit = 0;
    int endTime;
    enum Task task = TOUCH;

    bool taskCompleted = false;

   
    //Game settings
    srand(HAL_GetTick());
    task = rand() % 4;
    //task = 3;
    timeLimit = 2000; // in ms
    startTime = HAL_GetTick();
    endTime = startTime + timeLimit;
    

    //timeCurrent = 0;
    
    
    while(timeCurrent < endTime){
    //while(1){


        switch (task) {
            case TOUCH:
                taskCompleted = touch_sensor();
                break;
            case PHOTO:
                taskCompleted = photo_sensor();
                break;
            case BUTTON:
                taskCompleted = button_sensor();
                break;
            case JOYSTICK:
                taskCompleted = Joystick_sensor();
                break;
        }

    
        //check completed
        if(taskCompleted){
            LED_On(0u);
            score++;
            return;
            
        }
        else{
            LED_Off(0U);
        }
        
        //wait_delay(10);

        timeCurrent = HAL_GetTick();
        sprintf(debug_buffers[0], "System Time: %ims", timeCurrent);
        sprintf(debug_buffers[2], "livees: %i", lives);
        
        draw_game_screen(endTime - timeCurrent,  task);
    }

    lives--;


}
