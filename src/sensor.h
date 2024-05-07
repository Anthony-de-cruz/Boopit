#ifndef __SENSOR
#include <stdbool.h>
#define __SENSOR


bool touch_sensor(void);
bool photo_sensor(void);
bool button_sensor(void);
bool Joystick_sensor(void);


void MX_ADC_Init_Photo(void);
void MX_ADC_Init_JoyY(void);
void MX_GPIO_Init_Photo(void);
void MX_GPIO_Init_JoyY(void);


#endif /* __SENSOR */
