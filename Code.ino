#include "arduino_secrets.h"
#include <splash.h>
#include "thingProperties.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define RELAY_PIN 18         // GPIO pin for relay
#define SOIL_MOISTURE_PIN 34 // ADC pin for soil moisture sensor
#define LDR_PIN 35           // LDR sensor pin (Digital Output)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1       // Reset pin (not used with I2C)
#define SCREEN_ADDRESS 0x3C // I2C address for OLED display

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool manualControl = false; // Track if manual mode is enabled

void setup() {
  Serial.begin(115200);
  delay(1500);

  pinMode(RELAY_PIN, OUTPUT_OPEN_DRAIN);
  pinMode(LDR_PIN, INPUT);
  
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  ArduinoCloud.update();
  
  int sensorValue = analogRead(SOIL_MOISTURE_PIN);
  moisture = map(sensorValue, 4095, 0, 0, 100);
  
  int ldrState = digitalRead(LDR_PIN);
  sunlight = (ldrState == LOW); // Inverted sunlight state
  
  Serial.print("Moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  Serial.print("Sunlight: ");
  Serial.println(sunlight ? "Bright" : "Dark");

  if (!manualControl) { // Only execute auto mode if manual mode is off
    if (moisture < 30 && sunlight) {
      water = true;
    } else {
      water = false;
    }
    digitalWrite(RELAY_PIN, water ? LOW : HIGH);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Moisture: ");
  display.print(moisture);
  display.println("%");

  display.setCursor(0, 16);
  display.print("Sunlight: ");
  display.print(sunlight ? "Bright" : "Dark");

  display.setCursor(0, 32);
  display.print("Water: ");
  display.print(water ? "ON" : "OFF");

  display.setCursor(0, 48);
  display.print("Mode: ");
  display.print(manualControl ? "Manual" : "Auto");

  display.display();
  delay(200);
}

void onWaterChange() {
  manualControl = true; // Enable manual mode when the dashboard toggles water
  digitalWrite(RELAY_PIN, water ? LOW : HIGH);
}
