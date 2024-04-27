#include "display.h"

#include <stdlib.h>
#include <string.h>

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

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
