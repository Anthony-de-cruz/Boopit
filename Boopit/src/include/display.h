#ifndef __DISPLAY
#include <stdbool.h>

#include "Board_GLCD.h"
#include "Board_Touch.h"
#define __DISPLAY

/** @file */

// Constants

/*! @def SCREEN_WIDTH
    @brief The display width in pixels.
*/
#define SCREEN_WIDTH 480

/*! @def SCREEN_WIDTH
    @brief The display height in pixels.
*/
#define SCREEN_HEIGHT 272

// System Config

/**
 * @brief  Configure the system clock to run at the desired configuration.
 * @param  None
 * @retval None
 */
void SystemClock_Config(void);

/**
 * @brief  Initialise the display hardware via the HAL.
 * @param  None
 * @retval None
 */
void init_display(void);

// Debug

/*! @def DEBUG_MODE
    @brief This macro sets the debug mode. When text is written to the debug
   buffers, the text gets printed to the screen. Made for easier debugging.
*/
#define DEBUG_MODE true

/*! @def DEBUG_BUFFER_SIZE
    @brief The size of the debug buffers in bytes.
*/
#define DEBUG_BUFFER_SIZE 256

/*! @def DEBUG_MODE
    @brief The number of debug buffers that can be written to.
*/
#define DEBUG_BUFFER_COUNT 6

/**
 * @brief  2 dimensional array that has DEBUG_BUFFER_COUNT buffers that can be
 * written to do print your debugging information.
 */
extern char debug_buffers[DEBUG_BUFFER_COUNT][DEBUG_BUFFER_SIZE];

/**
 * @brief  Print out the contents of all the debug buffers onto the screen.
 * @param  None
 * @retval None
 */
void debug_print(void);

/**
 * @brief  Clear out of specific buffer by index.
 * @param  buffer The desired buffer to write to
 * @retval None
 */
void debug_clear(unsigned int buffer);

/**
 * @brief  debug_clear all of the buffers according to DEBUG_BUFFER_COUNT.
 * @param  None
 * @retval None
 */
void debug_clear_all(void);

// Widgets

/**
 * @brief Struct to represent a pressable button, with associated functions to
 * draw and trigger presses.
 */
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

/**
 * @brief Draws the button to the screen based on the Button's values.
 *
 * @param button A pointer to the button
 */
void draw_button(Button *button);

/**
 * @brief Check that the touch screen has been pressed in the boundaries of the
 * button.
 *
 * @param button A pointer to the button.
 * @param tsc_state The state of the touch screen.
 * @return true
 * @return false
 */
bool check_button_press(Button *button, TOUCH_STATE *tsc_state);

#endif /* __DISPLAY */
