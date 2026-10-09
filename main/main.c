#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "dht.h"
#define DHT11_GPIO GPIO_NUM_5

static const char *TASK_DHT = "DHT11";

static QueueHandle_t data_queue;

typedef struct{
    float temperature;
    float humidity;
} dht_sensor_d;


static void dht_task(void *pvParameters)
{            
    dht_sensor_d data;
    float temperature = 0.0f;
    float humidity = 0.0f;

    vTaskDelay(pdMS_TO_TICKS(2000));

    while (1) {
        if (dht_read_float_data(DHT_TYPE_DHT11,DHT11_GPIO, &humidity,&temperature) == ESP_OK) {
            data.temperature = temperature;
            data.humidity = humidity;

            xQueueOverwrite(data_queue, &data);
        } else {
            ESP_LOGE(TASK_DHT, "DHT11 read failed on GPIO");
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void display_task(void *pvParameters){
    dht_sensor_d received;

    while(1){
        if(xQueueReceive(data_queue, &received, portMAX_DELAY) == pdTRUE){
            ESP_LOGI("LCD", "Temp: %.1f", received.temperature);
            ESP_LOGI("LCD", "Humidity: %.1f", received.humidity);
            vTaskDelay(pdMS_TO_TICKS(200));
        }
    }
}

void app_main(void)
{
    data_queue = xQueueCreate(1, sizeof(dht_sensor_d));

    configASSERT(data_queue != NULL);

    xTaskCreate(dht_task,
                            "DHT Task",
                            4096,
                            NULL,
                            5,
                            NULL);
    
    xTaskCreate(
        display_task,
        "Display Task",
        4096,
        NULL,
        2, // lowest priority
        NULL);
}
