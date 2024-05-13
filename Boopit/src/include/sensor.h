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
 * @brief 
 */
void MX_ADC_Init_Photo(void);

/**
 * @brief 
 */
void MX_ADC_Init_JoyY(void);

/**
 * @brief 
 */
void MX_GPIO_Init_Photo(void);

/**
 * @brief 
 */
void MX_GPIO_Init_JoyY(void);

/**
 * @brief 
 */
void SensorInit(void);

#endif /* __SENSOR */
