#ifndef __SENSOR
#include <stdbool.h>
#define __SENSOR

/** @file */

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool touch_sensor_pressed(void);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool photo_sensor_pressed(void);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool button_sensor_pressed(void);

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool joystick_sensor_pressed(void);

/**
 * @brief Initialise the photo resistor profile
 */
void MX_ADC_Init_Photo(void);

/**
 * @brief Initialise the joystickY profile
 */
void MX_ADC_Init_JoyY(void);

/**
 * @brief Initialise the photo resistor pin
 */
void MX_GPIO_Init_Photo(void);

/**
 * @brief Initialise the joystickY pin
 */
void MX_GPIO_Init_JoyY(void);

/**
 * @brief Call all other initialisation functions and initialise digital pins
 */
void SensorInit(void);

#endif /* __SENSOR */
