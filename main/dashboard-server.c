#include <stdbool.h>
#include <stdio.h>

#include "esp_err.h"
#include "esp_http_server.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "dashboard-server.h"
