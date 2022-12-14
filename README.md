# ESP-IDF-ThingSpeak-HTTP  

## Description  
This project involves the communication between an ``ESP32 + BME280 sensor`` and the ThingSpeak server using the ``HTTP`` protocol. Humidity and temperature readings are taken by a ``BME280`` sensor and uploaded to ``ThingSpeak`` (periodically) by the ``ESP32`` using ``REST APIs``. More information will be provided on these APIs are they are crucial in writing data to the server as well as reading data from it. The project is developed using ``ESP-IDF`` drivers (Wi-Fi, HTTP client, I2C, GPIO, etc.).  

## Requirements  
1. ESP32 Dev Board  
2. BME280 Sensor  
3. ThingSpeak account  
4. Visual Studio Code  

## Information on the BME280 sensor  
The BME280 library (which was used in this project) and its documentation can be found in one of my repos (https://github.com/MUDAL/ESP32-and-BME280-communication-using-ESP-IDF-). The default pins used for I2C communication with the sensor are GPIO 18 (SDA) and GPIO 19 (SCL).  

## ESP32 Wi-Fi  
Before the ESP32 can communicate with the ThingSpeak server, several network configurations need to be made (e.g. TCP/IP, Wi-Fi, HTTP client). To initialize the Wi-Fi functionality of the ESP32, there are a couple of ESP-IDF drivers that need to be called. The following link will direct you to the a starter code for utilizing the ESP32 as a station (https://github.com/espressif/esp-idf/blob/6cfa88ed49b7d1209732347dae55578f4a679c98/examples/wifi/getting_started/station/main/station_example_main.c).  

## ESP32 HTTP client
The ESP32 can be configured as an HTTP client using the appropriate library functions. ``Espressif Systems`` have detailed documentation and sample codes that explain what these functions do and how they can be setup. The primary documentation for the ESP HTTP client can be accessed using this link: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/protocols/esp_http_client.html?highlight=http.  

## ThingSpeak  
ThingSpeak is an IoT platform that can be used for visualizing data over time. It is ideal for our project as we'd be able to monitor sensor readings periodically. To test this project, an account is needed (a free one is fine). Once you have an account, you'd have to create a ``channel`` and populate it with ``fields``. These ``fields`` will house the sensor readings.  
Since we're only sending humidity and temperature, only two fields are required. For more information on how to setup a channel, the following documentation can provide more information (https://www.mathworks.com/help/thingspeak/collect-data-in-a-new-channel.html).  

## API keys  
``API keys`` allow us to access ThingSpeak channels. With a ``Write API Key``, data can be written to fields within a channel. After setting up a channel, API keys are automatically generated (although new ones can be generated). Check the image below on how to get the ``Write API keys`` within your ``ThingSpeak channel``.  

![Screenshot (264)](https://user-images.githubusercontent.com/46250887/195721762-a3151491-b468-4b5d-9a57-2128990dcd55.png)


## Writing to a ThingSpeak channel  
The image below shows the format for the HTTP requests that must be sent to ThingSpeak in order to read/write data. We're interested in writing data, therefore, we'd focus on the first ``API request`` in the image.  

![Screenshot (265)](https://user-images.githubusercontent.com/46250887/195721864-8b86d7de-3074-4465-8035-029f84962c16.png) 

## Format of HTTP request to write data to ThingSpeak (examples)  
1. Writing the value 87 to field1: ``GET https://api.thingspeak.com/update?api_key=<WRITE_API_KEY>&field1=87``   
2. Writing 75 to field1 and 71 to field2: ``GET https://api.thingspeak.com/update?api_key=<WRITE_API_KEY>&field1=75&field2=71``  
The pattern can be used to access more fields (maximum of 8).  
Note: ``WRITE_API_KEY`` is a 16-digit code. A ``POST`` request can also be used for writing data to the server.  

## Project structure (Visual Studio Code)  
1. Source files can be found in ``ESP32_Send_Data_To_ThingSpeak\src``.
2. Header files can be found in ``ESP32_Send_Data_To_ThingSpeak\include``.  
3. The ``platformio.ini`` file is a project configuration file that sets necessary parameters for our board within the ``visual studio code`` environment.  

## Building the project     
1. Open ``ESP32_Send_Data_To_ThingSpeak\include\credentials.h``  
2. Rename the network parameters in the ``credentials.h`` file using you own network name, password, and ThingSpeak API key.  

Modify the ``#defines`` in the ``credentials.h`` as shown below. Once this is done, build the project and upload the code to your ESP32 board.   
```
#define SSID                      "YOUR-SSID"
#define PASS                      "YOUR-PASSWORD"
#define WRITE_API_KEY             "YOUR-WRITE-API-KEY"  
```

## Debugging the code using the serial terminal  
Debug messages are present in different parts of the code to allow the user understand what happens when the program runs. These messages are displayed when calls are made to ``ESP_LOGI()``.   

## Visualizing the sensor's data  

![Screenshot (263)](https://user-images.githubusercontent.com/46250887/195719147-5c192529-4e3c-4007-9b85-9c6767c81857.png)  

## Additional helpful resources
1. https://github.com/SIMS-IOT-Devices/FreeRTOS-ESP-IDF-HTTP-Client    
2. https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/wifi.html?highlight=wifi_event_sta_disconnected#esp32-wi-fi-event-description  
3. https://esp32.com/viewtopic.php?t=23110    
4. https://www.mathworks.com/help/thingspeak/index.html?s_tid=CRUX_lftnav    
5. https://espressif-docs.readthedocs-hosted.com/projects/esp-idf/en/v3.1.6/api-reference/protocols/esp_http_client.html  
6. Postman (for API testing).  






