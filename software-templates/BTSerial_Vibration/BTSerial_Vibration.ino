/*
Bluetooth Serial Simple Vibration

This example creates a simple connection to an ESP32 via classic bluetooth.
Messages sent to the ESP32 will control the vibration motor. Valid inputs 
are doubles greater than 0 and less than or equal to 1.0.

By Zane Zook 2021
*/

// Include required libraries
#include <BluetoothSerial.h>
#include <ESP32Servo.h>

// Preprocessor Directives
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Bluetooth Serial object
BluetoothSerial SerialBT;

// Define relevant variables for control
ESP32PWM ERM;             // create ERM objects
int CUE_LENGTH = 200;     // ms to display cue

// Handle received and sent messages
String message = "";
char incomingChar;
bool messageRecieved = false;

// Setup function to start bluetooth
void setup() {
  // Possible PWM GPIO pins on the ESP32: 0(used by on-board button),2,4,5(used by on-board LED),12-19,21-23,25-27,32-33
  // Pins available on Snaptics board V2.0 (TO BE UPDATED)
  // ERM:34,35,25,26,27,14,12,13 | Servo:18,5,15,2,0,4,17,16
  int ermPin = 13;
  
  // Set serial baud
  Serial.begin(115200);
  
  // Initiate Bluetooth
  if(SerialBT.begin("ESP32test")) {
    Serial.println("The device started, now you can pair it with bluetooth!");
  }
  else {
    Serial.println("An error occurred initializing Bluetooth");
  }

	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  // Setup PWM objects
  int freq = 1000;                   // pwm refresh frequency 1kHz
  ERM.attachPin(ermPin, freq, 10);   // 1KHz 8 bit
}

// Main loop function
void loop() {
  // Recieve incoming serial monitor messages
  while(Serial.available()) {
    char incomingChar = Serial.read();
    if (incomingChar != '\n') {
      message += String(incomingChar);
    }
    messageRecieved = true;
  }

  // Recieve incoming bluetooth messages
  while (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n') {
      message += String(incomingChar);
    }
    messageRecieved = true;
  }

  // If a message has been recieved, parse it 
  if(messageRecieved) {    
    Serial.println("Message: " + message);  
    
    // convert input into double
    double command = message.toDouble();

    // if command is proper for the erm, run erm
    if(command <= 1.0 && command > 0){
      // run erm if applicable for CUE_LENGTH
      ERM.writeScaled(command);
      delay(CUE_LENGTH);        
      ERM.writeScaled(0);
    }

    // throw error if command is invalid
    else{
      Serial.println("Invalid input");      
    }

    // reset message
    message = "";
    messageRecieved = false;
  }

  // Simple delay to slow Bluetooth check loop
  delay(20);
}