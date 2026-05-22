# 🌱 IoT Smart Farming System 💧

>Automated irrigation using real-time soil moisture data — powered by ESP32 and Arduino IoT Cloud.
>
![Platform](https://img.shields.io/badge/platform-ESP32-blue) ![Cloud](https://img.shields.io/badge/cloud-Arduino%20IoT-teal) ![Status](https://img.shields.io/badge/status-active-brightgreen)

---

## 📖 Overview

The **IoT Smart Farming System** automates irrigation by monitoring soil moisture and sunlight in real time. It uses an **ESP32 microcontroller**, soil moisture sensor, LDR sensor, and OLED display — integrated with **Arduino IoT Cloud** for remote monitoring and manual pump control.

---

## 🔧 Hardware Components

| Component | Description |
|---|---|
| ESP32 Microcontroller | Main controller — sensors, display, relay, Wi-Fi |
| Soil Moisture Sensor | Measures real-time soil moisture levels |
| LDR Sensor | Detects ambient sunlight intensity |
| SSD1306 OLED Display | Shows live sensor data and pump status |
| Water Pump | Delivers irrigation |
| Relay Module | Switches the water pump ON/OFF |
| Type-C Power Supply | Powers the entire system |

---

## 🖥️ Software & Libraries

| Library | Purpose |
|---|---|
| `Adafruit SSD1306` | OLED display rendering |
| `ArduinoIoTCloud` | Cloud variable sync |
| `Arduino_ConnectionHandler` | Wi-Fi connection management |

---

## ⚙️ Working Principle

```
Soil Moisture Sensor ──► ESP32 ──► Moisture < Threshold?
LDR Sensor          ──►            YES → Relay ON  → Pump ON
                                   NO  → Relay OFF → Pump OFF
                                    │
                               OLED Display (moisture, light, pump status)
                               Arduino IoT Cloud (remote sync)
```

---

## 🛠️ Setup

### 1. Hardware
- Soil moisture sensor → ESP32 analog GPIO
- LDR sensor → ESP32 analog GPIO
- SSD1306 OLED → ESP32 via I2C (SDA/SCL)
- Relay module → ESP32 digital GPIO → Water pump

### 2. Arduino IDE
Install these libraries via Library Manager:
- `Adafruit SSD1306`
- `Adafruit GFX Library`
- `ArduinoIoTCloud`
- `Arduino_ConnectionHandler`

### 3. Arduino IoT Cloud
1. Create a **Thing** at [create.arduino.cc/iot](https://create.arduino.cc/iot)
2. Add variables:
   - `soilMoisture` — int, read-only
   - `lightIntensity` — int, read-only
   - `pumpStatus` — bool, read/write
3. Copy your **Device ID** and **Secret Key** into the sketch
4. Set your Wi-Fi credentials in the sketch

### 4. Upload
Select your ESP32 board + COM port → Upload → Open Serial Monitor at `115200 baud`

---

## 📌 Configuration

```cpp
#define MOISTURE_THRESHOLD  40    // Pump activates below this moisture %
#define PUMP_PIN            26    // GPIO pin connected to relay
#define MOISTURE_PIN        34    // Analog pin for moisture sensor
#define LDR_PIN             35    // Analog pin for LDR sensor
```

---

## 🌐 IoT Dashboard

- 📊 Real-time soil moisture graph
- 💡 Live light intensity readings
- 🚰 Manual pump ON/OFF toggle
- 📱 Remote access from any device
