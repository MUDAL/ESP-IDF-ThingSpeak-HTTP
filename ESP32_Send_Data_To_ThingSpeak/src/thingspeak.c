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
#include "thingspeak.h"

static char url[76] = "http://api.thingspeak.com/update?api_key=0000000000000000&field1=0";
//URL indices
const uint8_t api_key_index = 41;
const uint8_t field_number_index = 63;
const uint8_t field_value_index = 65;

static void integer_to_string(uint32_t integer, char* string)
{
	if (integer == 0)
	{//Edge case  
		string[0] = '0';
		return;
	}
	uint32_t copyOfInt = integer;
	uint8_t noOfDigits = 0;

	while(copyOfInt > 0)
	{
		copyOfInt /= 10;
		noOfDigits++;
	}
	while (integer > 0)
	{
		string[noOfDigits - 1] = '0' + (integer % 10);
		integer /= 10;
		noOfDigits--;
	}
}

static esp_err_t client_event_get_handler(esp_http_client_event_handle_t evt)
{
  switch (evt->event_id)
  {
    case HTTP_EVENT_ERROR:
        ESP_LOGI("HTTP_EVENT_ERROR","event error");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGI("HTTP_EVENT_ON_CONNECTED","connected to server");
        break;   
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGI("HTTP_EVENT_ON_FINISH","finished HTTP session");
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGI("HTTP_EVENT_DISCONNECTED","connection has been disconnected");
        break;
    default:
      break;
  }
  return ESP_OK;
}

void thingspeak_open_connection(esp_http_client_handle_t* client)
{
  //HTTP client setup
  esp_http_client_config_t config_get = 
  {
    .url = url,
    .method = HTTP_METHOD_GET,
    .cert_pem = NULL,
    .event_handler = client_event_get_handler
  };
  //HTTP client setup
  *client = esp_http_client_init(&config_get);
}

void thingspeak_send_data(esp_http_client_handle_t* client,char* write_api_key,thingspeak_field_t field_num,uint32_t field_val)
{ 
  //insert API key
  for(uint8_t i = 0; i < strlen(write_api_key); i++)
  {
    url[api_key_index + i] = write_api_key[i];
  }
  //insert field number
  url[field_number_index] = field_num + '0';
  //convert field value to string
  char field_val_str[11] = {0}; //max of 10 digits
  integer_to_string(field_val,field_val_str);
  //insert field value
  for(uint8_t i = 0; i < strlen(field_val_str); i++)
  {
    url[field_value_index + i] = field_val_str[i];
  }
  url[field_value_index + strlen(field_val_str)] = '\0';
  ESP_LOGI("FINAL","final url = %s\n",url);
  //HTTP request
  esp_http_client_set_url(*client,url);
  esp_http_client_set_method(*client,HTTP_METHOD_GET);    
  esp_err_t err = esp_http_client_perform(*client);
  if(err == ESP_OK) 
  {
    ESP_LOGI("HTTP RESPONSE", "Status = %d, content_length = %d",
              esp_http_client_get_status_code(*client),
              esp_http_client_get_content_length(*client));
  }
}

void thingspeak_close_connection(esp_http_client_handle_t* client)
{
  esp_http_client_cleanup(*client);
}