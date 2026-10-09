idf_component_register(
                    SRCS 
                    "main.c"
                    "dashboard-server.c"
                    "lcd.c"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES
                            freertos
                            log
                            esp_driver_gpio
                            dht
                            esp_wifi
                            esp_event
                            esp_netif
                            nvs_flash
                            esp_http_server
                            esp_driver_i2c
                        )


