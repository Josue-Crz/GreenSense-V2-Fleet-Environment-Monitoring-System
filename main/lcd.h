#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "esp_err.h"

esp_err_t lcd_init(void);
esp_err_t lcd_print(const char *text);
esp_err_t lcd_clear(void);

#endif