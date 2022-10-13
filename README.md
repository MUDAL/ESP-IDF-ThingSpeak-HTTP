# ESP-IDF-ThingSpeak-HTTP  

## Description  
This project involves communicating with the ThingSpeak server using the HTTP protocol. Humidity and temperature readings are taken by a ``BME280`` sensor and uploaded to ThingSpeak using the REST APIs provided by ``MathWorks``. More information will be provided on these APIs are they are crucial in writing data to the server as well as reading data from it. The project is developed using ``ESP-IDF`` drivers (Wi-Fi, HTTP client, I2C, GPIO, etc.).  

## Requirements  
1. ESP32 Dev Board  
2. BME280 Sensor  
3. ThingSpeak account  

## Information on the BME280 sensor  
The BME280 library (which was used in this project) and its documentation can be found in one of my repos (). The default pins used for I2C communication with the sensor are GPIO 18 (SDA) and GPIO 19 (SCL).  

## ESP32 HTTP client

## ThingSpeak  

## Writing to a ThingSpeak channel  


