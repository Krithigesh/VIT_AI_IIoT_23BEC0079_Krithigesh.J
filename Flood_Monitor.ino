#include <WiFi.h>
#include <ThingSpeak.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define POT_PIN 34
#define BUZZER 14

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* WIFI_NAME = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

unsigned long CHANNEL_ID = 3417067;
const char* WRITE_API_KEY = "WEQDNNXFX7PDZSC8";

WiFiClient client;

const float DAM_HEIGHT = 100.0;
const float FLOOD_LEVEL = 50.0;

float distance = 0;
float waterLevel = 0;

bool flood = false;
bool previousFlood = false;

int alertCount = 0;

unsigned long lastUpload = 0;
const unsigned long uploadInterval = 20000;

void setup()
{
    Serial.begin(115200);

    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);

    Wire.begin();

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("OLED Failed");
        while (1);
    }

    display.clearDisplay();
    display.display();

    Serial.println("Connecting WiFi...");

    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi Connected");
    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());

    ThingSpeak.begin(client);
}

void loop()
{
    int raw = analogRead(POT_PIN);

    distance = 100.0 - ((float)raw * 100.0 / 4095.0);
    waterLevel = DAM_HEIGHT - distance;

    flood = (waterLevel >= FLOOD_LEVEL);

    if (flood && !previousFlood)
    {
        alertCount++;
        previousFlood = true;
    }

    if (!flood)
    {
        previousFlood = false;
    }

    digitalWrite(BUZZER, flood);

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);

    display.setCursor(0, 0);
    display.println("SMART FLOOD MONITOR");

    display.setCursor(0, 14);
    display.print("Raw ADC : ");
    display.println(raw);

    display.setCursor(0, 26);
    display.print("Distance: ");
    display.print(distance, 1);
    display.println(" cm");

    display.setCursor(0, 38);
    display.print("Water   : ");
    display.print(waterLevel, 1);
    display.println(" cm");

    display.setCursor(0, 50);

    if (flood)
    {
        display.print("Status : FLOOD");
    }
    else
    {
        display.print("Status : NORMAL");
    }

    display.display();

    Serial.println("--------------------------------");

    Serial.print("ADC Raw      : ");
    Serial.println(raw);

    Serial.print("Distance     : ");
    Serial.print(distance);
    Serial.println(" cm");

    Serial.print("Water Level  : ");
    Serial.print(waterLevel);
    Serial.println(" cm");

    Serial.print("Flood Status : ");

    if (flood)
    {
        Serial.println("FLOOD");
    }
    else
    {
        Serial.println("NORMAL");
    }

    Serial.print("Alert Count  : ");
    Serial.println(alertCount);

    if (millis() - lastUpload >= uploadInterval)
    {
        Serial.println("Uploading to ThingSpeak...");

        ThingSpeak.setField(1, waterLevel);
        ThingSpeak.setField(2, distance);
        ThingSpeak.setField(3, flood ? 1 : 0);
        ThingSpeak.setField(4, alertCount);

        int response = ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);

        Serial.print("ThingSpeak Response : ");
        Serial.println(response);

        if (response == 200)
        {
            Serial.println("Upload Successful");
        }
        else
        {
            Serial.println("Upload Failed");
        }

        lastUpload = millis();
    }

    delay(500);
}

