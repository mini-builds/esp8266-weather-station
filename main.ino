#include <DHT.h>

#include <Adafruit_Sensor.h>

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    delay(10);

    dht.begin();

    WiFi.begin("** ssid **", "** key **");

    int attempt = 0;
    while ((WiFi.status() != WL_CONNECTED) && (attempt < 10))
    {
        delay(2000);
        Serial.println("Connecting to WiFi..");
        attempt++;
    }

    if (WiFi.status() == WL_CONNECTED)
        Serial.println("Connected to WiFi!");
    else
        Serial.println("Failed to connect to WiFi!");
}

long timeLastMeasured = 0;
float humidity, temperature;
String apiUrl = "** url to post measurements to  **"; // e.g. the ip for your computer on the local network

void loop()
{
    if (millis() - timeLastMeasured >= 10000)
    {
        timeLastMeasured = millis();

        humidity = dht.readHumidity();
        temperature = dht.readTemperature();

        Serial.println(humidity);
        Serial.println(temperature);

        if(isnan(humidity) || isnan(temperature)) {
            Serial.println("DHT22 measurement failed");
            return;
        }
        
        HTTPClient client;

        client.begin(apiUrl);
        int httpCode = client.POST("{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + "}");

        String payload = client.getString();
        Serial.println(payload);
        
        client.end();
    }
    delay(1000);
}