
#include "../../stm32f4/inc/gpio.h"

// actual speed depends on voltage

#define GPIO_SPEED_VERYLOW GPIO_SPEED_2MHZ	// ~400kHz
#define GPIO_SPEED_LOW     GPIO_SPEED_25MHZ	// ~2MHz
#define GPIO_SPEED_MEDIUM  GPIO_SPEED_50MHZ	// ~10MHz
#define GPIO_SPEED_HIGH    GPIO_SPEED_100MHZ	// ~50MHz

