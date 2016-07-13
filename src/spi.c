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
return 0;
}
void initGPIO(){

}
