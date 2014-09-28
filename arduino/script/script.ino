//OVERVIEW
///////////////////////////////////////////////////////////////////////////////////////////
// This script reads and converts the states of the hall effect sensors into garage door
// open/close states and then output the data to serial.

// Since it takes a couple seconds for the garage door to open, it may be best to track a
// third state called "opening/closing". 
///////////////////////////////////////////////////////////////////////////////////////////

//SENSORS
///////////////////////////////////////////////////////////////////////////////////////////
// The hall effect sensor (US1881) used in this project is a latched sensor, which means
// once the sensor is toggled by a magnet, it will maintain its state until an opposite
// pole is used to unlatch it.

// Since what I want is a reed switch, I need to cycle the power pin on (for 10+ ms) and
// off (for 10+ ms) to reset the sensor to unlatched state after latching.
//////////////////////////////////////////////////////////////////////////////////////////

// Configuration setup
#define bypass true

// Input pins
#define topSensorPin 2
#define bottomSensorPin 3

// Output pins
#define topPowerPin 11
#define bottomPowerPin 12

#define outputPin 13 // for arduino led display

#define switchPin 7

// Constants
#define powerCycle 50U


void setupPins() {
  // make the topSensorPin an input:
  pinMode(topSensorPin, INPUT);
  pinMode(bottomSensorPin, INPUT);
  
  // make the power_pin an output to apply alternate power.
  pinMode(topPowerPin, OUTPUT);
  pinMode(bottomPowerPin, OUTPUT);
  
  pinMode(outputPin, OUTPUT);
  pinMode(switchPin, OUTPUT);
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // setup input and output pins
  setupPins();
}

// the loop routine runs over and over again forever:
void loop() {

  // apply power for 50 ms
  digitalWrite(topPowerPin, HIGH);
  delay(50);
  
  // read the input pin:
  int openState = digitalRead(topSensorPin);
  int closeState = digitalRead(bottomSensorPin);
  
  if (bypass) {
    closeState = !openState;
  }
  
  // print out the state of the door:
  if (!openState && closeState) { // close
    Serial.println(0);
    digitalWrite(outputPin, LOW);
  } else if (openState && !closeState) { // open
    digitalWrite(outputPin, HIGH);
    Serial.println(1);
  } else if (!openState && !closeState) { // opening/closing
    Serial.println(2);
  } else {
    Serial.println(3); // error
  }
  
  // turn off power for reset.
  digitalWrite(topPowerPin, LOW);
  delay(50);
}

