#ifndef __DISPLAY
#include <stdbool.h>

#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_Touch.h"
#define __DISPLAY


// System Config

// #ifdef __RTX
// extern uint32_t os_time;
// uint32_t HAL_GetTick(void) {
	// return os_time;
// }
// #endif


void SystemClock_Config(void);

void init_display(void);

// Debug

#define DEBUG_MODE true

#define DEBUG_BUFFER_SIZE 256
#define DEBUG_BUFFER_COUNT 6

extern char debug_buffers[DEBUG_BUFFER_COUNT][DEBUG_BUFFER_SIZE];

void debug_print(void);
void debug_clear(unsigned int buffer);


// Widgets

typedef struct Button {
    int x;
    int y;
    int width;
    int height;
    char *text;
    GLCD_FONT *font;
    bool pressed;
} Button;

void draw_button(Button *button);

bool check_button_press(Button *button, TOUCH_STATE *tsc_state);

// Game Screens





void draw_end_screen(void);

#endif /* __DISPLAY */
