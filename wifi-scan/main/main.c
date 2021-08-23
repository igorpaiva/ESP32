#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

void scan(){

    wifi_scan_config_t scan_config = {

        .ssid = 0,
        .bssid = 0,
        .channel = 0,
        .show_hidden = true

    };

    printf("Start scanning\n");
    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));
    printf("Complete.\n");

    uint16_t ap_num;
    wifi_ap_record_t ap_records[20];
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_num, ap_records));

    printf("Found %d access points: \n", ap_num);

    printf("        SSID        |   CHANNEL |   RSSI    |   MAC\n\n");

    for(int i = 0; i < ap_num; i++){

        printf("%32s    |   %7d |   %4d |   %02x:%02x:%02x:%02x:%02x:%02x   ", ap_records[i].ssid, ap_records[i].primary, ap_records[i].rssi, *(ap_records[i].bssid), *(ap_records[i].bssid+1), *(ap_records[i].bssid+2), *(ap_records[i].bssid+3), *(ap_records[i].bssid+4), *(ap_records[i].bssid+5));

    }

}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    esp_netif_init();
    wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    while(true){

        vTaskDelay(3000 / portTICK_RATE_MS);
        scan();

    }

}
