# Industrial-IIoT-Flood-Monitoring-System
Industrial Internet of Things Flood Monitoring System using ESP32, OLED, ThingSpeak and Wokwi.
# Industrial Internet of Things Flood Monitoring System

## Aim

To simulate an Industrial Internet of Things (IIoT) Flood Monitoring System that:

* Continuously measures the water level at a dam.
* Displays the water level and distance from the top of the dam on an OLED display.
* Provides local flood alerts using a buzzer whenever the water level exceeds a predefined threshold.
* Uploads real-time monitoring data to the ThingSpeak cloud platform for remote monitoring.

---

## Problem Statement

Simulate an Industrial Internet of Things Flood Monitoring System that:

(a) Continuously measures the water level at a dam using a simulated water level sensor.

(b) Provides real-time flood alerts through a buzzer and uploads water level information to the cloud whenever the water level exceeds a predefined threshold, indicating a potential flooding condition.

---

## Scope of the Solution

This project demonstrates how an IIoT-based flood monitoring system can:

* Continuously monitor the water level in a dam.
* Display live monitoring information on an OLED display.
* Generate local flood alerts using a buzzer.
* Upload water level information to the cloud in real time.
* Maintain a flood alert counter for monitoring purposes.
* Enable remote monitoring and future scalability such as SMS alerts, mobile notifications, and automatic dam gate control.

---

## Required Components

### Hardware

* ESP32 Development Board
* Potentiometer (Simulated Water Level Sensor)
* SSD1306 OLED Display (128×64)
* Active Buzzer
* Breadboard
* Jumper Wires

### Software

* Arduino IDE
* Wokwi Simulator
* Adafruit GFX Library
* Adafruit SSD1306 Library
* ThingSpeak Library

### Cloud Environment

* ThingSpeak Account

For real-time cloud monitoring of:

* Water Level
* Distance from Dam
* Flood Status
* Flood Alert Count

---

## Flowchart of the Code

```text
Start
   ↓
Initialize ESP32
   ↓
Connect to WiFi
   ↓
Initialize OLED Display
   ↓
Read Potentiometer Value
   ↓
Calculate Water Level
   ↓
Calculate Distance
   ↓
Is Water Level > Flood Threshold?
      ↓             ↓
     No            Yes
      ↓             ↓
Buzzer OFF     Buzzer ON
Status NORMAL  Status FLOOD
      ↓             ↓
Display Data on OLED
      ↓
Upload Data to ThingSpeak
      ↓
Wait 20 Seconds
      ↓
Repeat
```

---

## Code

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
  display.setCursor(0,0);
  display.println("SMART FLOOD MONITOR");

  display.setCursor(0,14);
  display.print("Raw ADC : ");
  display.println(raw);

  display.setCursor(0,26);
  display.print("Distance: ");
  display.print(distance,1);
  display.println(" cm");

  display.setCursor(0,38);
  display.print("Water   : ");
  display.print(waterLevel,1);
  display.println(" cm");

  display.setCursor(0,50);

  if(flood)
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
  if(flood)
    Serial.println("FLOOD");
  else
    Serial.println("NORMAL");
  Serial.print("Alert Count  : ");
  Serial.println(alertCount);
  
 
  
  
  if (millis() - lastUpload >= uploadInterval)
    
   { Serial.println("Uploading to ThingSpeak...");

    ThingSpeak.setField(1, waterLevel);
    ThingSpeak.setField(2, distance);
    ThingSpeak.setField(3, flood ? 1 : 0);
    ThingSpeak.setField(4, alertCount);

    int response = ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);

    Serial.print("ThingSpeak Response : ");
    Serial.println(response);

    if(response == 200)
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

## Simulated Circuit

*Insert the Wokwi circuit screenshot here.*

---

## Project Link (Wokwi)

Paste your Wokwi simulation link here.

Example:

```
https://wokwi.com/projects/xxxxxxxxxxxxxxxx
```

---

## Project Demo

Paste your Google Drive or YouTube demo video link here.

Example:

```
https://drive.google.com/xxxxxxxxxxxxxxxx
```

---

## Procedure

1. Open the Wokwi Simulator.
2. Add the ESP32, potentiometer, OLED display, and buzzer to the workspace.
3. Connect all components according to the circuit diagram.
4. Create a ThingSpeak channel with four fields.
5. Enter the Channel ID and Write API Key in the Arduino code.
6. Upload the code and start the simulation.
7. Rotate the potentiometer to simulate changes in the water level.
8. Observe the OLED display, buzzer operation, and Serial Monitor.
9. Verify that the sensor values are uploaded to the ThingSpeak dashboard.
10. Capture screenshots and document the observed results.

---

## Result

The Industrial Internet of Things Flood Monitoring System was successfully simulated using the Wokwi platform. The ESP32 continuously monitored the simulated water level using a potentiometer and calculated the corresponding water level and remaining distance from the top of the dam. The measured values were displayed on the OLED display in real time. Whenever the water level exceeded the predefined flood threshold, the buzzer was activated and the flood alert counter was incremented. The measured parameters, including water level, distance, flood status, and alert count, were successfully uploaded to the ThingSpeak cloud platform and visualized through live graphs. The project met all the objectives defined in the problem statement and demonstrated reliable real-time monitoring and cloud-based flood alert generation.
