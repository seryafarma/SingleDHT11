//---------------------------------------------------------------------------------------------------------------------
// main.cpp
// DHT11 weather webserver.
// Style: State Machine
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <DFRobot_DHT11.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

//---------------------------------------------------------------------------------------------------------------------
// Local Includes
//---------------------------------------------------------------------------------------------------------------------
#include "auth.hpp"

//---------------------------------------------------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------------------------------------------------
#define DHT11_PIN                                                                                                      \
    14 // For ESP32 WEMOS D1 board, this is connected to the D15/SCL/D3 pin and
       // somehow it is called pin 5...

//---------------------------------------------------------------------------------------------------------------------
// Class
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------------------------------------------------

DFRobot_DHT11 DHT;

// current temperature & humidity, updated in loop()
float t = 0.0;
float h = 0.0;

//---------------------------------------------------------------------------------------------------------------------
// Functions Declaration
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// Setup and Loop
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
void connect_wifi()
{
    WiFi.begin(Authentication::WIFI_SSID, Authentication::WIFI_PASSWORD);
    Serial.print("Connecting to ");
    Serial.println(Authentication::WIFI_SSID);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected!");
    Serial.println(WiFi.localIP());
    Serial.println();

    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

//---------------------------------------------------------------------------------------------------------------------
void setup()
{
    Serial.begin(9600);
    delay(1500);
    connect_wifi();
}

//---------------------------------------------------------------------------------------------------------------------
void loop()
{
    // put your main code here, to run repeatedly:
}