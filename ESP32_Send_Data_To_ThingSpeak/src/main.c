#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_client.h"
#include "string.h"
#include "wifi_conn.h"
#include "thingspeak.h"
#include "bme280.h"
#include "credentials.h"

/**
 * @brief Task to handle periodic transmission of BME280
 * sensor data to Thingspeak server.
 * 
 * @param arg 
 */
void upload_sensor_data_to_thingspeak(void* arg)
{
  char url[200] = {0};
  esp_http_client_handle_t http_client;
  bme280_data_t bme280_data = {};
  TickType_t previous_tick = xTaskGetTickCount();
  thingspeak_config(url);
  while(1)
  {
    bme280_get_data(&bme280_data);
    if(wifi_connected() && wifi_got_ip())
    {
      ESP_LOGI("SEND","uploading data to cloud\n");
      thingspeak_open_connection(url,&http_client,WRITE_API_KEY);
      thingspeak_set_field(url,THINGSPEAK_FIELD1,bme280_data.temperature); 
      thingspeak_set_field(url,THINGSPEAK_FIELD2,bme280_data.humidity);
      thingspeak_send_data(url,&http_client);
      thingspeak_close_connection(&http_client);
    }
    vTaskDelayUntil(&previous_tick,pdMS_TO_TICKS(500));
  }
}

void app_main(void)
{
  nvs_flash_init();
  wifi_config();
  bme280_init();
  xTaskCreate(upload_sensor_data_to_thingspeak,"sensor-data-to-cloud",4000,NULL,configMAX_PRIORITIES,NULL);
  TickType_t previous_tick = xTaskGetTickCount();
  while(1)
  {
    if(wifi_disconnected_after_max_retries())
    {
      wifi_reconnect_after_specified_time(3000);
    }
    vTaskDelayUntil(&previous_tick,pdMS_TO_TICKS(50));
  }
}