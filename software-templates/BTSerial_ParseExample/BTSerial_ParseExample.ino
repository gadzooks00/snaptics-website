/*
Bluetooth Serial Parse Example

This example creates a simple connection to an ESP32 via classic bluetooth.
Messages sent to the ESP32 will be parsed and if a recognized command 
will control the LED, the vibration motor, or the servo motor as relevant. 
All other message will simply print the message out on the serial monitor.

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
Servo SERVO;              // create Servo objects
const int LED_PIN = 5;    // pin for the LED
int CUE_LENGTH = 200;     // ms to display cue

// Handle received and sent messages
String message = "";
char incomingChar;
bool messageRecieved = false;

// Helper function to blink specified number of times
void blink(int blinkCount) {
  while (blinkCount > 0) {
    digitalWrite(LED_PIN, HIGH);
    delay(CUE_LENGTH);
    digitalWrite(LED_PIN, LOW);
    delay(CUE_LENGTH);
    blinkCount--;
  }
}

// Helper function to run the relevant motor
void runMotor(String motor, double command) {
  // standardize motor string input
  motor.trim();
  motor.toLowerCase();

  // checks if command motor is vibration based
  if(motor == "vibration" || motor == "v" ||
    motor == "erm" || motor == "e") {
      if(command <= 1.0 && command >= 0){
        // run erm if applicable for CUE_LENGTH
        ERM.writeScaled(command);
        delay(CUE_LENGTH);        
        ERM.writeScaled(0);
      }
      else{
        // return error if command is outside of proper range
        Serial.println("Invalid command input for erm");
      }
  }

  //checks if command motor is a servo
  else if(motor == "servo" || motor == "s") {
      if(command <= 180 && command >= 0){
        // run servo if applicable for CUE_LENGTH
        SERVO.write(command);    
        delay(CUE_LENGTH);   
        SERVO.write(0);       
      }
      else{
        // return error if command is outside of proper range
        Serial.println("Invalid command input for servo");
      }
  }

  // returns a warning if command motor is invalid
  else {
    Serial.println("Invalid motor input");
  }
}

// Helper function to parse the incoming message
void parseMessage(){
  bool isNumber = false;
  bool isCommand = false;
  int commandIndex;

  // check for digits or for commands
  for(int i=0; i < message.length(); i++){
    if (message[i] == '-'){
      isCommand = true;
      commandIndex = i;
    }
    else if (isDigit(message[i])){
      isNumber = true;
    }
  }

  // if the message is a command run the command
  if (isCommand){    
    // Parse what motor is being specified
    String motor = message.substring(0,commandIndex);

    // Parse the command to the motor
    double command = message.substring(commandIndex + 1).toDouble();
    Serial.println("Motor: " + motor + " | Command: " + command);

    // Send command to motor
    runMotor(motor, command);
  }

  // if the message is just a number, blink the LED
  else if (!isCommand && isNumber){
    Serial.println("Blinks: " + message);    
    blink(message.toInt());
  }
}

// Setup function to start bluetooth
void setup() {
  // Possible PWM GPIO pins on the ESP32: 0(used by on-board button),2,4,5(used by on-board LED),12-19,21-23,25-27,32-33
  // Pins available on Snaptics board V2.0 (TO BE UPDATED)
  // ERM:34,35,25,26,27,14,12,13 | Servo:18,5,15,2,0,4,17,16
  int ermPin = 13;
  int servoPin = 16;

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
  
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  // Setup PWM objects
  int freq = 1000;                   // pwm refresh frequency 1kHz
  ERM.attachPin(ermPin, freq, 10);   // 1KHz 8 bit
  
  // Setup Servo objects
  // using SG90 servo min/max of 500us and 2400us
  SERVO.setPeriodHertz(50); // Standard 50hz servo
  SERVO.attach(servoPin, 500, 2400);// attaches the servo to pin
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
    parseMessage(); 

    // reset message
    message = "";
    messageRecieved = false;
  }

  // Simple delay to slow Bluetooth check loop
  delay(20);
}