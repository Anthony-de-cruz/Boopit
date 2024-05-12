#ifndef __DISPLAY
#include <stdbool.h>

#include "Board_GLCD.h"
#include "Board_Touch.h"
#define __DISPLAY

// Constants

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

// System Config

void SystemClock_Config(void);

void init_display(void);

// Debug

#define DEBUG_MODE true

#define DEBUG_BUFFER_SIZE 256
#define DEBUG_BUFFER_COUNT 6

extern char debug_buffers[DEBUG_BUFFER_COUNT][DEBUG_BUFFER_SIZE];

void debug_print(void);
void debug_clear(unsigned int buffer);
void debug_clear_all(void);

// Widgets

typedef struct Button {
    int x;
    int y;
    int width;
    int height;
    char *text;
    GLCD_FONT *font;
    int input_delay;
    int time_pressed;
} Button;

void draw_button(Button *button);

bool check_button_press(Button *button, TOUCH_STATE *tsc_state);

#endif /* __DISPLAY */
