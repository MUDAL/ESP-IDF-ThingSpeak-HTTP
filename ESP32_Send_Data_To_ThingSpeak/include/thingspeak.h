#ifndef THINGSPEAK_H
#define THINGSPEAK_H

#include "credentials.h"

//ThingSpeak channel fields
typedef enum 
{
  THINGSPEAK_FIELD1 = 1,
  THINGSPEAK_FIELD2,
  THINGSPEAK_FIELD3,
  THINGSPEAK_FIELD4,
  THINGSPEAK_FIELD5,
  THINGSPEAK_FIELD6,
  THINGSPEAK_FIELD7,
  THINGSPEAK_FIELD8
}thingspeak_field_t;

/**
 * @brief 
 * 
 * @param client pointer to HTTP client handle.
 */
void thingspeak_open_connection(esp_http_client_handle_t* client);
/**
 * @brief 
 * 
 * @param client pointer to HTTP client handle.
 * @param write_api_key API key of channel whose fields(s) are to be written.
 * @param field_num Specific field to be written to. [Ranges from 1 to 8]
 * @param field_val Value to be written to the specified channel field.
 */
void thingspeak_send_data(esp_http_client_handle_t* client,char* write_api_key,thingspeak_field_t field_num,uint32_t field_val);
/**
 * @brief 
 * 
 * @param client pointer to HTTP client handle.
 */
void thingspeak_close_connection(esp_http_client_handle_t* client);

#endif