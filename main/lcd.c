#include "lcd.h"
#include "driver/i2c_master.h"

// ESP-S3 GPIO Config for LCD
#define I2c_SDA 8
#define I2C_SCL 9
#define LCD_ADDR 0x3F
// PCF8574 output bits
#define LCD_RS 0x01
#define LCD_EN 0x04
#define LCD_BL 0x08

static i2c_master_dev_handle_t lcd_dev;

static esp_err_t lcd_write_byte(uint8_t data)
{
    return  i2c_master_transmit(lcd_dev,
                                                     &data, 
                                                     1, 
                                                     1000);
}

esp_err_t lcd_init(void){
    i2c_master_bus_config_t bus_config =
    {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = I2C_ADDR_BIT_LEN_7,
        .sda_io_num = GPIO_NUM_8,
        .scl_io_num = GPIO_NUM_9,
        .i2c_port = I2C_NUM_0,
    };

    i2c_master_bus_handle_t bus_handle;
    
    ESP_ERROR_CHECK(
        i2c_new_master_bus(&bus_config, &bus_handle)
    );

    i2c_device_config_t dev_config = 
    {
        .dev_addr_length = I2C_ADDR_BIT_7,
        .device_address = LCD_ADDR,
        .scl_speed_hz = 100000, // 100,000 Hz (100kHz)
    };

    ESP_ERROR_CHECK(
        i2c_master_bus_add_device(
            bus_handle,
            &dev_config,
            &lcd_dev
        )
    );

    lcd_write_byte();

    return ESP_OK;
}

static void lcd_pulse(uint8_t data)
{
    // on state
    lcd_write_byte(data | LCD_EN);
    // off state
    lcd_write_byte(data & ~LCD_EN);
}