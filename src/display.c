#include "display.h"
#include "game.h"

#include <stdlib.h>
#include <string.h>

#include "stm32f7xx_hal.h"

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

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

void init_display(void) {
    SystemClock_Config(); //Config Clocks
    Touch_Initialize(); // Init Touchscreen
    GLCD_Initialize(); //Init GLCD
    
    GLCD_ClearScreen();
    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_SetBackgroundColor(GLCD_COLOR_WHITE);
    GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
};



char debug_buffers[DEBUG_BUFFER_COUNT][DEBUG_BUFFER_SIZE];

void debug_print() {
    int buffer;
    GLCD_SetFont(&GLCD_Font_6x8);
    for (buffer = 0; buffer < DEBUG_BUFFER_COUNT; buffer++) {
        GLCD_DrawString(6, 8 + (8 + 1) * buffer, debug_buffers[buffer]);
    }
}

void debug_clear(unsigned int buffer) {
    memset(debug_buffers[buffer], 0, sizeof(debug_buffers[buffer]));
}

void draw_button(Button *button) {
    int text_width = button->font->width * strlen(button->text);
    int text_height = button->font->height;
    GLCD_DrawRectangle(button->x, button->y, button->width, button->height);
    
    GLCD_SetFont(button->font);
    GLCD_DrawString((int)(button->x + button->width / 2) - text_width / 2,
        (int)(button->y + button->height / 2) - text_height / 2, button->text);
};


bool check_button_press(Button *button, TOUCH_STATE *tsc_state) {
    if (tsc_state->x > button->x && tsc_state->x < button->x + button->width) {
        if (tsc_state->y > button->y && tsc_state->y < button->y + button->height) {
            return 1;
        }
    }
    return 0;
};

void draw_game_screen(int timeCurrent, int timeLimit, int task) {
    
    char timeRemainingBuffer[256];
    char taskBuffer[256];
    
    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_DrawString(100, 50, "BOOPIT!");
    
    sprintf(timeRemainingBuffer, "  Remaining time: %i  ", (int)((timeLimit - timeCurrent) * 0.001));
    GLCD_DrawString(100, 80, timeRemainingBuffer);
    
    sprintf(taskBuffer, "Task: %s", TASK_NAMES[task]);
    GLCD_DrawString(100, 200, taskBuffer);
    
    debug_print();
}
