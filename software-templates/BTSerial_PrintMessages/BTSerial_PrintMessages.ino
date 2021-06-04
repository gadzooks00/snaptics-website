/*
Bluetooth Serial Print Messages

This example creates opens classic bluetooth on the ESP32.
Messages sent to the ESP32 will print to the ESP32 Serial monitor.
Program for debugging purposes

By Zane Zook 2021
*/

// Include required libraries
#include "BluetoothSerial.h"
 
// Bluetooth Serial object
BluetoothSerial SerialBT;
 
// Setup function to start bluetooth
void setup() {
  // Set serial baud
  Serial.begin(115200);

  // Initiate Bluetooth
  if (SerialBT.begin("ESP32test")) {
    Serial.println("The device started, now you can pair it with bluetooth!");
  } else {
    Serial.println("An error occurred initializing Bluetooth");
  }
}
 
// Main loop function
void loop() {
 
  // Recieve incoming serial messages
  while (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    Serial.print(incomingChar);
  }
 
  // Simple delay to slow Bluetooth check loop
  delay(20);
}