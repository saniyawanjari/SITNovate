#include <WiFi.h>
#include <HTTPClient.h>

// 🔹 WiFi Credentials
const char* ssid = "ESP";      // Replace with your WiFi name
const char* password = "123456789";  // Replace with your WiFi password

// 🔹 ThingSpeak API Details
const char* server = "http://api.thingspeak.com/update";
String apiKey = "99VEMKCSK1IJI3DJ";  // Replace with your ThingSpeak Write API Key

// 🔹 Sensor Pins Setup
#define SOIL_MOISTURE_PIN 34  // Soil Moisture Sensor
#define WIND_SPEED_PIN     35  // Wind Speed Sensor
#define SALINITY_PIN       32  // Salinity Sensor
#define LIGHT_INTENSITY_PIN 33 // Light Sensor
#define HUMIDITY_PIN       36  // Humidity Sensor
#define TEMPERATURE_PIN    39  // Temperature Sensor

void setup() {
    Serial.begin(115200);  

    // 🔹 Connect to WiFi
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\n✅ WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    // 🔹 Read Sensor Data
    int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
    int windSpeed = analogRead(WIND_SPEED_PIN);
    int salinity = analogRead(SALINITY_PIN);
    int lightIntensity = analogRead(LIGHT_INTENSITY_PIN);
    int humidity = analogRead(HUMIDITY_PIN);
    int temperature = analogRead(TEMPERATURE_PIN);

    Serial.println("📊 Sensor Data:");
    Serial.print("Soil Moisture: "); Serial.println(soilMoisture);
    Serial.print("Wind Speed: "); Serial.println(windSpeed);
    Serial.print("Salinity: "); Serial.println(salinity);
    Serial.print("Light Intensity: "); Serial.println(lightIntensity);
    Serial.print("Humidity: "); Serial.println(humidity);
    Serial.print("Temperature: "); Serial.println(temperature);

    // 🔹 Send Data to ThingSpeak
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = String(server) + "?api_key=" + apiKey + 
                     "&field1=" + String(soilMoisture) + 
                     "&field2=" + String(windSpeed) + 
                     "&field3=" + String(salinity) + 
                     "&field4=" + String(lightIntensity) + 
                     "&field5=" + String(humidity) + 
                     "&field6=" + String(temperature);

        Serial.println("📤 Sending data to ThingSpeak...");
        http.begin(url);
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
            Serial.println("✅ Data Sent Successfully!");
        } else {
            Serial.print("❌ Error sending data: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    }

    delay(20000);  // 🔹 20-second delay (ThingSpeak has a 15-second update limit)
}