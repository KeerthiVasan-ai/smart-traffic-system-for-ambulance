#include <SoftwareSerial.h>

String message = "";
bool messageReceived = false;

int northRedPin = 10, northGreenPin = 9, northBluePin = A1;
int westRedPin = 12, westGreenPin = 11, westBluePin = A2;
int eastRedPin = 7, eastGreenPin = 6, eastBluePin = A3;

void setup() {
  // Set all RGB pins as output
  pinMode(eastRedPin, OUTPUT);
  pinMode(eastGreenPin, OUTPUT);
  pinMode(eastBluePin, OUTPUT);
  pinMode(westRedPin, OUTPUT);
  pinMode(westGreenPin, OUTPUT);
  pinMode(westBluePin, OUTPUT);
  pinMode(northRedPin, OUTPUT);
  pinMode(northGreenPin, OUTPUT);
  pinMode(northBluePin, OUTPUT);

  Serial.begin(115200); // For monitoring through serial monitor
  Serial.println("Enter direction (EAST, WEST, or NORTH):");
}

void loop() {
  // Cyclic color change before receiving any message
  changeColorsCyclic();
  
  // Check for user input in Serial Monitor
  if (Serial.available()) {
    message = Serial.readStringUntil('\n'); // Read user input from Serial Monitor
    messageReceived = true;
  }

  if (messageReceived) {
    Serial.println("Message received: " + message);

    // Check for direction in the message and update lights accordingly
    if (message.indexOf("EAST") != -1) {
      setDirectionColors(eastGreenPin, westRedPin, northRedPin);
      Serial.println("East is Green, others are Red");
      delay(5000);
    } 
    else if (message.indexOf("WEST") != -1) {
      setDirectionColors(westGreenPin, eastRedPin, northRedPin);
      Serial.println("West is Green, others are Red");
      delay(10000);
    } 
    else if (message.indexOf("NORTH") != -1) {
      setDirectionColors(northGreenPin, eastRedPin, westRedPin);
      Serial.println("North is Green, others are Red");
      delay(10000);
    }

    message = "";  // Clear message
    messageReceived = false;

    // Prompt for next input
    Serial.println("Enter direction (EAST, WEST, or NORTH):");
  }
}

// Function to change colors cyclically in the pattern (green, red, red), (red, green, red), (red, red, green)
void changeColorsCyclic() {
  // Pattern 1: East Green, West Red, North Red
  setCyclicPattern(eastGreenPin, westRedPin, northRedPin);
  delay(2000); // Delay between cycles
  
  // Pattern 2: East Red, West Green, North Red
  setCyclicPattern(westGreenPin, eastRedPin, northRedPin);
  delay(2000);
  
  // // Pattern 3: East Red, West Red, North Green
  setCyclicPattern(northGreenPin, eastRedPin, westRedPin);
  delay(2000);
}

// Function to set color based on cyclic pattern
void setCyclicPattern(int greenPin, int red1Pin, int red2Pin) {
  // Set one LED to green
  analogWrite(greenPin, 0); // Green ON (0 for common anode)
  
  // Set the other LEDs to red
  analogWrite(red1Pin, 0); // Red ON
  analogWrite(red2Pin, 0); // Red ON

  // Ensure the rest of the colors are OFF
  resetAllColorsExcept(greenPin, red1Pin, red2Pin);
}

// Function to set color based on direction (after receiving message)
void setDirectionColors(int greenPin, int red1Pin, int red2Pin) {
  // Set the directed LED to green
  analogWrite(greenPin, 0); // Green ON (0 for common anode)
  
  // Turn the other LEDs to red
  analogWrite(red1Pin, 0); // Red ON
  analogWrite(red2Pin, 0); // Red ON

  // Ensure the rest of the colors are OFF
  resetAllColorsExcept(greenPin, red1Pin, red2Pin);
}

// Function to turn off unused colors
void resetAllColorsExcept(int greenPin, int red1Pin, int red2Pin) {
  // East LED
  if (greenPin != eastGreenPin) analogWrite(eastGreenPin, 255); // Green OFF
  if (red1Pin != eastRedPin && red2Pin != eastRedPin) analogWrite(eastRedPin, 255); // Red OFF
  
  // West LED
  if (greenPin != westGreenPin) analogWrite(westGreenPin, 255); // Green OFF
  if (red1Pin != westRedPin && red2Pin != westRedPin) analogWrite(westRedPin, 255); // Red OFF
  
  // North LED
  if (greenPin != northGreenPin) analogWrite(northGreenPin, 255); // Green OFF
  if (red1Pin != northRedPin && red2Pin != northRedPin) analogWrite(northRedPin, 255); // Red OFF
  
  // Turn off Blue for all LEDs
  analogWrite(eastBluePin, 255); // Blue OFF
  analogWrite(westBluePin, 255); // Blue OFF
  analogWrite(northBluePin, 255); // Blue OFF
}
