#include <stdbool.h>

#include "Board_LED.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"

#include "sensor.h"

/** @file */

ADC_HandleTypeDef hadcPhoto;
ADC_HandleTypeDef hadcJoyY;

bool photo_sensor_pressed(void) {
    if (HAL_ADC_GetValue(&hadcPhoto) > 900) {
        return true;
    } else {
        return false;
    }
}
bool button_sensor_pressed(void) {
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7)) {
        return false;
    } else {
        return true;
    }
}
bool joystick_sensor_pressed(void) {
    if (HAL_ADC_GetValue(&hadcJoyY) < 100 ||
        HAL_ADC_GetValue(&hadcJoyY) > 1000) {
        return true;
    } else {
        return false;
    }
}

bool touch_sensor_pressed(void) {
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6)) {
        return true;
    } else {
        return false;
    }
}

// Photo Resistor
void MX_ADC_Init_Photo(void) {
    ADC_ChannelConfTypeDef sConfig;

    // Enable ADC CLOCK
    //__HAL_RCC_ADC1_CLK_ENABLE();
    //__HAL_RCC_ADC2_CLK_ENABLE();
    __HAL_RCC_ADC3_CLK_ENABLE();

    /// Configure the global features of the ADC (Clock, Resolution, Data
    /// Alignment and number of conversion)
    hadcPhoto.Instance = ADC3; // # Select the ADC (ADC1, ADC2, ADC3)
    hadcPhoto.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadcPhoto.Init.Resolution = ADC_RESOLUTION_12B;
    hadcPhoto.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadcPhoto.Init.NbrOfConversion = 3;
    hadcPhoto.Init.ScanConvMode = ENABLE;
    hadcPhoto.Init.ContinuousConvMode = ENABLE;
    hadcPhoto.Init.DiscontinuousConvMode = DISABLE;
    HAL_ADC_Init(&hadcPhoto);
    // configure channal
    sConfig.Rank = 1;
    sConfig.Channel = ADC_CHANNEL_0; // # Select the ADC Channel (ADC_CHANNEL_X)
    sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
    HAL_ADC_ConfigChannel(&hadcPhoto, &sConfig);
    HAL_ADC_Start(&hadcPhoto);
    HAL_ADC_PollForConversion(&hadcPhoto, HAL_MAX_DELAY);
}

GPIO_InitTypeDef GPIO_InitStruct_Photo;
void MX_GPIO_Init_Photo(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct_Photo.Mode =
        GPIO_MODE_ANALOG;                   // configure to analog input mode
    GPIO_InitStruct_Photo.Pin = GPIO_PIN_0; // #select GPIO GPIO_PIN_X
    GPIO_InitStruct_Photo.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct_Photo); // #select GPIO Group
}

// Joystick Y
void MX_ADC_Init_JoyY(void) {
    ADC_ChannelConfTypeDef sConfigJoyY;

    /* Enable ADC CLOCK */
    //__HAL_RCC_ADC1_CLK_ENABLE();
    //__HAL_RCC_ADC2_CLK_ENABLE();
    __HAL_RCC_ADC3_CLK_ENABLE();

    /* Configure the global features of the ADC (Clock, Resolution, Data
    Alignment and number of conversion) */
    hadcJoyY.Instance = ADC3; // # Select the ADC (ADC1, ADC2, ADC3)
    hadcJoyY.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadcJoyY.Init.Resolution = ADC_RESOLUTION_10B;
    hadcJoyY.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadcJoyY.Init.NbrOfConversion = 3;
    hadcJoyY.Init.ScanConvMode = ENABLE;
    hadcJoyY.Init.ContinuousConvMode = ENABLE;
    hadcJoyY.Init.DiscontinuousConvMode = DISABLE;
    HAL_ADC_Init(&hadcJoyY);
    // configure channal
    sConfigJoyY.Rank = 3;
    sConfigJoyY.Channel =
        ADC_CHANNEL_7; // # Select the ADC Channel (ADC_CHANNEL_X)
    sConfigJoyY.SamplingTime = ADC_SAMPLETIME_28CYCLES;
    HAL_ADC_ConfigChannel(&hadcJoyY, &sConfigJoyY);
    HAL_ADC_Start(&hadcJoyY);
    HAL_ADC_PollForConversion(&hadcJoyY, HAL_MAX_DELAY);
}

GPIO_InitTypeDef GPIO_InitStructJoyY;
void MX_GPIO_Init_JoyY(void) {
    __HAL_RCC_GPIOF_CLK_ENABLE();
    GPIO_InitStructJoyY.Mode =
        GPIO_MODE_ANALOG;                 // configure to analog input mode
    GPIO_InitStructJoyY.Pin = GPIO_PIN_9; // #select GPIO GPIO_PIN_X
    GPIO_InitStructJoyY.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStructJoyY); // #select GPIO Group
}

void SensorInit(void) {
    // general
    GPIO_InitTypeDef gpio;
    LED_Initialize();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // analog
    MX_ADC_Init_Photo();
    MX_ADC_Init_JoyY();
    MX_GPIO_Init_Photo();
    MX_GPIO_Init_JoyY();

    HAL_Init();

    // digital
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLDOWN;
    gpio.Speed = GPIO_SPEED_HIGH;

    gpio.Pin = GPIO_PIN_6;
    HAL_GPIO_Init(GPIOC, &gpio);
}
