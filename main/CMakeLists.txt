idf_component_register(SRCS "GreenSense-V2-Fleet-Environment-Monitoring-System.c" "dashboard-server.c"
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
                        )


