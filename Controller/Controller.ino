#include <Joystick.h>
#include <Keyboard.h>

#define FIRSTPIN_RIGHTHEADER 22
#define LASTPIN_RIGHTHEADER 53

#define LEN_TOGGLEPINS 1 //half of the bottom pins on the arduino due
#define LEN_BUTTONPINS 2 //half of the bottom pins on the arduino due
#define LEN_ANALOGPINS 5


int togglePins[LEN_TOGGLEPINS];
int toggleVals[LEN_TOGGLEPINS];
char toggleKeys[LEN_TOGGLEPINS];
int analogPins[LEN_ANALOGPINS] = {A6,A7,A8,A9,64};
int buttonPins[LEN_BUTTONPINS];
int buttonVals[LEN_BUTTONPINS];
char buttonKeys[LEN_BUTTONPINS];
//ThreeAxisJoystick stick1, stick2;
Joystick_ joysticklib;


void checkAnalogInputs()
{
  joysticklib.setXAxis(analogRead(analogPins[0]));
  joysticklib.setYAxis(analogRead(analogPins[1]));
  joysticklib.setZAxis(analogRead(analogPins[3]));
}


void checkToggleInputs()
{
  for(int i=0; i<LEN_TOGGLEPINS;i++)
  {
    int currentval = digitalRead(togglePins[i]);
    if(currentval!=toggleVals[i]){
      Keyboard.write(toggleKeys[i]);
      delay(20);
      toggleVals[i]=currentval;
      delay(10);
    }
  }
}

void checkButtonInputs()
{
  for(int i=0; i<LEN_BUTTONPINS;i++)
  {
    int currentval = digitalRead(buttonPins[i]);
    if(currentval!=buttonVals[i]) {
      switch(currentval){
        case HIGH:
          Keyboard.release(buttonKeys[i]);
          break;
        case LOW:
          Keyboard.press(buttonKeys[i]);
      }
      buttonVals[i] = currentval;
    }
  }
}


void setup()
{
  testSetup();
}

void loop()
{
checkButtonInputs();
checkToggleInputs();
checkAnalogInputs();
}


void testSetup(){
  Keyboard.begin();
  joysticklib.begin(true);

  //---------Setting up digital pins----------
  pinMode(22,INPUT_PULLUP);
  togglePins[0] = 22;
  toggleVals[0] = LOW;
  toggleKeys[0] = 't'; //t

  pinMode(26,INPUT_PULLUP);
  pinMode(30,INPUT_PULLUP);
  buttonPins[0] = 26;
  buttonPins[1] = 30;
  buttonKeys[0] = 'm'; //Space
  buttonKeys[1] = 'b';//R




}
