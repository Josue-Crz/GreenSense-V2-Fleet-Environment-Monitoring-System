#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"

#include "dht.h"

#define DHT11_GPIO GPIO_NUM_5

static const char *TASK_DHT = "DHT11";

static void dht_task(void *pvParameters)
{
    float temperature = 0.0f;
    float humidity = 0.0f;

    vTaskDelay(pdMS_TO_TICKS(2000));

    while (1) {
        if (dht_read_float_data(DHT_TYPE_DHT11,DHT11_GPIO, &humidity,&temperature) == ESP_OK) {
            ESP_LOGI(TASK_DHT,"Temperature: %.1f °C, Humidity: %.1f%%", temperature, humidity);
        } else {
            ESP_LOGE(TASK_DHT, "DHT11 read failed on GPIO");
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main(void)
{
    xTaskCreate(dht_task,"dht_task",4096, NULL, 5, NULL);
}
