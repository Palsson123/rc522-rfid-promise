#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "spi.h"
#define LED_PIN      44        /**< The pin where the LED is connected */

void Write(char* data, char length) {
    spi_msg.rx_buf = 0; // Block SPI from reading anything.
    spi_msg.tx_buf = (unsigned long)data;
    spi_msg.len = length;
          if (ioctl(dev->devfd, SPI_IOC_MESSAGE(1), &spi_msg) < 0) {
    }
}
char* WriteRead(char* data, char length) {
    spi_msg.rx_buf = (unsigned long) spi_rx; // Block SPI from reading anything.
    spi_msg.tx_buf = (unsigned long) data;
    spi_msg.len = length;
    if (ioctl(dev->devfd, SPI_IOC_MESSAGE(1), &spi_msg) < 0) {
    }
    return spi_rx;
}
