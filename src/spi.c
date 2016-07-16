#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <mraa.h>
#include <mraa/gpio.h>
#include "spi.h"
#define LED_PIN      44        /**< The pin where the LED is connected */

void Write(char* data, char length) {

}
char* WriteRead(char* data, char length) {
    char a[2];
    a[0]=1;
    a[1] = 2;
return a;
}
void initGPIO(){
    gpio = mraa_gpio_init_raw(1);
    mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
}
