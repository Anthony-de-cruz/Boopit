#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stm32f7xx_hal.h"

#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_Touch.h"

#include "display.h"

#define wait_delay HAL_Delay

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

#ifdef __RTX
extern uint32_t os_time;
uint32_t HAL_GetTick(void) {
	return os_time;
}
#endif

/**
* System Clock Configuration
*/
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

int main(void){
    bool running = 1;
    int tick = 0;
    int presses = 0;
    bool playing = 0;
    int score = 0;
    char *title = "BOOPIT!";
    int title_size = strlen(title) * 24;
    
    Button play_button = {
            (int)(480 * 0.25) - (100 / 2),
            100,
            100,
            50,
            "Play",
            &GLCD_Font_16x24,
            0
        };
    Button stop_button = {
            (int)(480 * 0.75) - (100 / 2),
            100,
            100,
            50,
            "Stop",
            &GLCD_Font_16x24,
            0
        };
    Button increment_score_button = {
            (int)(480 / 2) - (250 / 2),
            175,
            250,
            50,
            "Increment Score",
            &GLCD_Font_16x24,
            0
        };
  
    TOUCH_STATE tsc_state;
    
    HAL_Init(); //Init Hardware Abstraction Layer
    SystemClock_Config(); //Config Clocks
    Touch_Initialize(); // Init Touchscreen
    GLCD_Initialize(); //Init GLCD
    
    GLCD_ClearScreen();
    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_SetBackgroundColor(GLCD_COLOR_WHITE);
    GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
    
    // Main Loop
    while(running){
        //GLCD_ClearScreen();
        
        // Tick counter
        tick++;
        sprintf(debug_buffers[5], "%i", tick);
        
        // Handle Touch Screen Input
        Touch_GetState(&tsc_state);
        if (tsc_state.pressed) {
            tsc_state.pressed = 0;
            presses++;
            sprintf(debug_buffers[0], "Touch @ X:%i,Y:%i -> Presses: %i    ",
                tsc_state.x, tsc_state.y, presses);
            
            if (check_button_press(&play_button, &tsc_state)) {
                playing = 1;
            } else if (check_button_press(&stop_button, &tsc_state)) {
                playing = 0;
            } else if (check_button_press(&increment_score_button, &tsc_state) && playing) {
                score++;
            } 
            
            sprintf(debug_buffers[1], "Playing: %i ", playing);
            sprintf(debug_buffers[2], "Score: %i ", score);
        }
        
        // Draw UI
        GLCD_SetFont(&GLCD_Font_16x24);
        
        GLCD_DrawString((int)(480 / 2) - (title_size / 2), 50, "BOOPIT!");
        
        draw_button(&play_button);
        draw_button(&stop_button);
        draw_button(&increment_score_button);
       
        debug_print();
        wait_delay(100);
    }
}
