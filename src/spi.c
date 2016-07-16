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
    char datab;
    spi_msg.rx_buf = 0; // Block SPI from reading anything.
    spi_msg.tx_buf = (unsigned long)data;
    spi_msg.len = length;
    mraa_gpio_write(gpio, 0);
    printf("Sending data\n");
    if (ioctl(dev->devfd, SPI_IOC_MESSAGE(1), &spi_msg) < 0) {
        printf("ERROR\n");
    }
    printf("Data sent\n");
    mraa_gpio_write(gpio, 1);
}
char *WriteRead(char* data, char length) {

    spi_msg.rx_buf = (unsigned long) &receive; // Block SPI from reading anything.
    spi_msg.tx_buf = (unsigned long) spi_rx;
    spi_msg.len = length;
    mraa_gpio_write(gpio, 0);
    if (ioctl(dev->devfd, SPI_IOC_MESSAGE(1), &spi_msg) < 0) {
    }
    mraa_gpio_write(gpio, 1);
    return spi_rx;

}
void initGPIO(){
    gpio = mraa_gpio_init_raw(1);
    mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
    
    dev = (mraa_spi_context) calloc(1, sizeof(struct _spi));
    
    memset(&spi_msg, 0, sizeof(spi_msg));

    char path[64];
    sprintf(path, "/dev/spidev%u.%u", 32766,1);

    dev->devfd = open(path, O_RDWR);

    char length = 1;
    spi_msg.tx_buf = 0;
    spi_msg.rx_buf = 0;
    spi_msg.speed_hz = 7000000;
    spi_msg.bits_per_word = 8;
    spi_msg.delay_usecs = 0;
    spi_msg.len = length;
}
