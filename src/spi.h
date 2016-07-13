#include <mraa.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
void Write(char* data, char length);
char* WriteRead(char* data, char length);
typedef struct {
    mraa_result_t (*gpio_init_internal_replace) (mraa_gpio_context dev, int pin);
    mraa_result_t (*gpio_init_pre) (int pin);
    mraa_result_t (*gpio_init_post) (mraa_gpio_context dev);

    mraa_result_t (*gpio_close_pre) (mraa_gpio_context dev);
    mraa_result_t (*gpio_close_replace) (mraa_gpio_context dev);

    mraa_result_t (*gpio_mode_replace) (mraa_gpio_context dev, mraa_gpio_mode_t mode);
    mraa_result_t (*gpio_mode_pre) (mraa_gpio_context dev, mraa_gpio_mode_t mode);
    mraa_result_t (*gpio_mode_post) (mraa_gpio_context dev, mraa_gpio_mode_t mode);

    mraa_result_t (*gpio_edge_mode_replace) (mraa_gpio_context dev, mraa_gpio_edge_t mode);

    mraa_result_t (*gpio_dir_replace) (mraa_gpio_context dev, mraa_gpio_dir_t dir);
    mraa_result_t (*gpio_dir_pre) (mraa_gpio_context dev, mraa_gpio_dir_t dir);
    mraa_result_t (*gpio_dir_post) (mraa_gpio_context dev, mraa_gpio_dir_t dir);

    int (*gpio_read_replace) (mraa_gpio_context dev);
    mraa_result_t (*gpio_write_replace) (mraa_gpio_context dev, int value);
    mraa_result_t (*gpio_write_pre) (mraa_gpio_context dev, int value);
    mraa_result_t (*gpio_write_post) (mraa_gpio_context dev, int value);
    mraa_result_t (*gpio_mmap_setup) (mraa_gpio_context dev, mraa_boolean_t en);
    mraa_result_t (*gpio_interrupt_handler_init_replace) (mraa_gpio_context dev);
    mraa_result_t (*gpio_wait_interrupt_replace) (mraa_gpio_context dev);

    mraa_result_t (*i2c_init_pre) (unsigned int bus);
    mraa_result_t (*i2c_init_bus_replace) (mraa_i2c_context dev);
    mraa_i2c_context (*i2c_init_raw_replace) (unsigned int bus);
    mraa_result_t (*i2c_init_post) (mraa_i2c_context dev);
    mraa_result_t (*i2c_set_frequency_replace) (mraa_i2c_context dev, mraa_i2c_mode_t mode);
    mraa_result_t (*i2c_address_replace) (mraa_i2c_context dev, uint8_t addr);
    int (*i2c_read_replace) (mraa_i2c_context dev, uint8_t* data, int length);
    int (*i2c_read_byte_replace) (mraa_i2c_context dev);
    int (*i2c_read_byte_data_replace) (mraa_i2c_context dev, const uint8_t command);
    int (*i2c_read_word_data_replace) (mraa_i2c_context dev, const uint8_t command);
    int (*i2c_read_bytes_data_replace) (mraa_i2c_context dev, uint8_t command, uint8_t* data, int length);
    mraa_result_t (*i2c_write_replace) (mraa_i2c_context dev, const uint8_t* data, int length);
    mraa_result_t (*i2c_write_byte_replace) (mraa_i2c_context dev, uint8_t data);
    mraa_result_t (*i2c_write_byte_data_replace) (mraa_i2c_context dev, const uint8_t data, const uint8_t command);
    mraa_result_t (*i2c_write_word_data_replace) (mraa_i2c_context dev, const uint16_t data, const uint8_t command);
    mraa_result_t (*i2c_stop_replace) (mraa_i2c_context dev);

    mraa_result_t (*aio_init_internal_replace) (mraa_aio_context dev, int pin);
    int (*aio_read_replace) (mraa_aio_context dev);
    mraa_result_t (*aio_get_valid_fp) (mraa_aio_context dev);
    mraa_result_t (*aio_init_pre) (unsigned int aio);
    mraa_result_t (*aio_init_post) (mraa_aio_context dev);

    mraa_pwm_context (*pwm_init_replace) (int pin);
    mraa_pwm_context (*pwm_init_internal_replace) (void* func_table, int pin);
    mraa_result_t (*pwm_init_pre) (int pin);
    mraa_result_t (*pwm_init_post) (mraa_pwm_context pwm);
    mraa_result_t (*pwm_period_replace) (mraa_pwm_context dev, int period);
    float (*pwm_read_replace) (mraa_pwm_context dev);
    mraa_result_t (*pwm_write_replace) (mraa_pwm_context dev, float duty);
    mraa_result_t (*pwm_write_pre) (mraa_pwm_context dev, float percentage);
    mraa_result_t (*pwm_enable_replace) (mraa_pwm_context dev, int enable);
    mraa_result_t (*pwm_enable_pre) (mraa_pwm_context dev, int enable);

    mraa_result_t (*spi_init_pre) (int bus);
    mraa_result_t (*spi_init_post) (mraa_spi_context spi);
    mraa_result_t (*spi_lsbmode_replace) (mraa_spi_context dev, mraa_boolean_t lsb);

    mraa_result_t (*uart_init_pre) (int index);
    mraa_result_t (*uart_init_post) (mraa_uart_context uart);
} mraa_adv_func_t;





struct _spi {
    /*@{*/
    int devfd;          /**< File descriptor to SPI Device */
    uint32_t mode;      /**< Spi mode see spidev.h */
    int clock;          /**< clock to run transactions at */
    mraa_boolean_t lsb; /**< least significant bit mode */
    unsigned int bpw;   /**< Bits per word */
    mraa_adv_func_t* advance_func; /**< override function table */
    /*@}*/
};

mraa_spi_context dev;
char spi_rx[256];
struct spi_ioc_transfer spi_msg;
