//---------------------------------------------------------------------------------------------------------------------
// main.cpp
// DHT11 weather webserver.
// Style: Procedural
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
#include "web_page.hpp"

using WebPage::index_html;

//---------------------------------------------------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------------------------------------------------
#define DHT11_PIN                                                                                                      \
    14 // For ESP32 WEMOS D1 board, this is connected to the D15/SCL/D3 pin and
       // somehow it is called pin 5...
// State Machine.
#define STATE_DELAY_MS 50
//---------------------------------------------------------------------------------------------------------------------
// Class
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------------------------------------------------
DFRobot_DHT11 DHT;

float current_temperature = 0.0;
float current_humidity = 0.0;

uint32_t previous_millis = 0;
bool time_to_gather = false;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
//---------------------------------------------------------------------------------------------------------------------
// Functions Declaration
//---------------------------------------------------------------------------------------------------------------------
void update_temperature();
void update_humidity();
//---------------------------------------------------------------------------------------------------------------------
// Setup and Loop
//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
String processor(const String& var)
{
    Serial.println(var);
    if (var == "TEMPERATURE")
    {
        return String(current_temperature);
    }
    else if (var == "HUMIDITY")
    {
        return String(current_humidity);
    }
    return String();
}

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

    // Print ESP8266 Local IP Address
    Serial.println(WiFi.localIP());

    // Route for root / web page
    server.on("/", HTTP_GET,
              [](AsyncWebServerRequest* request) { request->send_P(200, "text/html", index_html, processor); });
    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send_P(200, "text/plain", String(current_temperature).c_str());
    });
    server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send_P(200, "text/plain", String(current_humidity).c_str());
    });

    // Start server
    server.begin();
}

//---------------------------------------------------------------------------------------------------------------------
void loop()
{
    static const uint32_t THIRTY_SECONDS = 30UL * 1000UL;
    uint32_t current_millis = millis();

    // A simple timer actually for a minute...
    if (current_millis - previous_millis > THIRTY_SECONDS)
    {
        // Save the last time tick.
        previous_millis = current_millis;

        DHT.read(DHT11_PIN);
        update_temperature();
        update_humidity();
    }
    delay(STATE_DELAY_MS);
}

//---------------------------------------------------------------------------------------------------------------------
void update_temperature()
{
    float new_temp = DHT.temperature;
    if (isnan(new_temp))
    {
        Serial.println("Failed to read from DHT sensor!");
    }
    else
    {
        current_temperature = new_temp;
        Serial.print("Current temperature: ");
        Serial.println(current_temperature);
    }
}

//---------------------------------------------------------------------------------------------------------------------
void update_humidity()
{
    float new_humidity = DHT.humidity;
    if (isnan(new_humidity))
    {
        Serial.println("Failed to read from DHT sensor!");
    }
    else
    {
        current_humidity = new_humidity;
        Serial.print("Current humidity: ");
        Serial.println(current_humidity);
    }
}
