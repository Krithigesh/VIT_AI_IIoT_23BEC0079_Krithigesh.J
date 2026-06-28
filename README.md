# Industrial-IIoT-Flood-Monitoring-System
Industrial Internet of Things Flood Monitoring System using ESP32, OLED, ThingSpeak and Wokwi.

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

The complete Arduino source code is available in the repository:

`Flood_Monitor.ino`



## Simulated Circuit

<img width="978" height="717" alt="image" src="https://github.com/user-attachments/assets/2737c738-d905-445a-b91e-c3a77c52b8a8" />


## Project Link (Wokwi)


```
https://wokwi.com/projects/467895784163129345
```

---

## Project Demo


```
https://drive.google.com/file/d/1a08yp4T6cvDvf3fuOD1364BKWfdY8c3u/view?usp=drive_link
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
