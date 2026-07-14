idf_component_register(SRCS "GreenSense-V2-Fleet-Environment-Monitoring-System.c"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES freertos log esp_driver_gpio dht)
