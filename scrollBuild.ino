// This is the code for my LED scroller-througher.
// I have 10 LED lights, each one of which corresponds to a digit from 0 - 9.
// The analog joystick is used to scroll through the LEDs.
// I was rather uncertain how to use the joystick, thus I watched a short YouTube video to help me out. Video -- https://youtu.be/MlDi0vO9Evg
// Please refer to the attached Read Me for full analysis, documentation, and comments on this project.

//  Declaring joystick funtionality.
const int joystickInput = A0;
const int joystickButton = 2;
const int joystickMin = 100;
const int joystickMax = 923;

// Declaring LEDs and establishing the active LED.
const int ledGroup[] = {13,12,11,10,9,8,7,6,5,4};
const int arraySize = sizeof(ledGroup)/sizeof(ledGroup[0]);
int activeLed = 0;

// Declaring the variables needed for multitasking: the interval the program waits before checking, and initializing previous millis to use in comparison.
long interval1 = 150;
long previousMillis1 = 0;


void setup() {
//  Putting all the pins into output mode and making sure they're all off.
   for (int counter = 0; counter < sizeof(ledGroup); counter++){
    pinMode(ledGroup[counter], OUTPUT);
    digitalWrite(ledGroup[counter], LOW);
  }
}

void loop() {
 // This is where the program measures when to execute, decided by the interval, and when appropriate it samples the joystick input using the joystickRead function and then executes the scrollLed function.
  unsigned long currentMillis1 = millis();  
  if (currentMillis1 - previousMillis1 > interval1){
    previousMillis1 = currentMillis1;
    int joystickDirection = joystickRead();
    scrollLed(joystickDirection);
    
  }
}
  
int joystickRead(){
 // This is the function to read the input from the joystick's X-axis pin.
  int joystickValue = analogRead(joystickInput);
  return joystickValue;
}

void scrollLed(int joystickDirection){
  // This is where the LED gets changed. 
  digitalWrite(ledGroup[activeLed], LOW);
  
  int direction = 0;
   // Establishing the direction variable when either min/max value is reached on the joystick.
  if (joystickDirection < joystickMin){
    direction = -1;
  }
  if (joystickDirection > joystickMax){
    direction = +1;
  }
  
  //Here is where the LED actually gets changed.
  activeLed = (activeLed + direction);
  
  // Here we establish what happens when the ends of the array are reached, and a roll-over effect is attained.
  if (activeLed < 0){
    activeLed = arraySize - 1;
  }
  if (activeLed == arraySize){
    activeLed = 0;
  }

  // And finally here we turn on the new LED!
  digitalWrite(ledGroup[activeLed], HIGH);
}
