/*
Bluetooth Serial LED Blink

This example creates a simple connection to an ESP32 via classic bluetooth.
Messages sent to the ESP32 will correspond to number of blinks on the
board if it is a number. Otherwise will simply print out on the serial
monitor. Message sent to serial monitor will send to bluetooth connected 
device

By Zane Zook 2021
*/

// Library includes
#include <BluetoothSerial.h>

// Preprocessor Directives
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Bluetooth Serial object
BluetoothSerial SerialBT;

// GPIO where LED is connected to
const int LED_PIN = 5;
int BLINK_LENGTH = 200;     // ms to display blink

// Handle received and sent messages
String message = "";
char incomingChar;
bool messageRecieved = false;

// Helper function to blink specified number of times
void blink(int blinkCount) {
  while (blinkCount > 0) {
    digitalWrite(LED_PIN, HIGH);
    delay(BLINK_LENGTH);
    digitalWrite(LED_PIN, LOW);
    delay(BLINK_LENGTH);
    blinkCount--;
  }
}

// Setup function to start bluetooth
void setup() {
  // Setup pin modes
  pinMode(LED_PIN, OUTPUT);

  // Set serial baud
  Serial.begin(115200);
  
  // Initiate Bluetooth
  if(SerialBT.begin("ESP32test")) {
    Serial.println("The device started, now you can pair it with bluetooth!");
  }
  else {
    Serial.println("An error occurred initializing Bluetooth");
  }
}

// Main loop function
void loop() {
  // Send outgoing serial messages
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  // Recieve and parse incoming bluetooth messages
  while(SerialBT.available()) {
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n') {
      message += String(incomingChar);
    }
    messageRecieved = true;
  }
  
  // Loop blinks if the message is a number
  if (messageRecieved) {
    bool isNumber = false;

    // check for digits
    for(int i=0; i < message.length(); i++){
      if (isDigit(message[i])){
        isNumber = true;
      }
    }

    // blink if number input
    if(isNumber)
      blink(message.toInt());

    // reset message
    message = "";
    messageRecieved = false;
  }

  // Simple delay to slow Bluetooth check loop
  delay(20);
}