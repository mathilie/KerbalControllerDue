#include <Joystick.h>
#include<Keyboard.h>

#define FIRSTPIN_RIGHTHEADER 22
#define LASTPIN_RIGHTHEADER 53

#define LEN_TOGGLEPINS 16; //half of the bottom pins on the arduino due
#define LEN_BUTTONPINS 16; //half of the bottom pins on the arduino due
#define LEN_ANALOGPINS 12;


int togglePins[LEN_TOGGLEPINS];
int toggleVals[LEN_TOGGLEPINS];
int toggleKeys[LEN_TOGGLEPINS];
int buttonPins[LEN_BUTTONPINS];
int buttonKeys[LEN_BUTTONPINS];
int throttlePin;
ThreeAxisJoystick stick1, stick2;
Joystick_ joysticklib;

void checkAnalogInputs()
{
  stick1.readValues();
  stick2.readValues();
  joysticklib.setThrottle(digitalRead(throttlePin));
}


void checkToggleInputs()
{
  for(int i=0; i<LEN_TOGGLEPINS;i++)
  {
    int currentval = digitalRead(togglePins[i]);
    if(currentval!=toggleVals[i]){
      Keyboard.write(toggleKeys[i]);
      toggleVals[i]=currentval;
    }
  }
}

void checkButtonInputs()
{
  for(int i=0; i<LEN_BUTTONPINS;i++)
  {
    if(digitalRead(togglePins[i])==LOW) {
      Keyboard.write(toggleKeys[i]);
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

  //setting up communication and initial stuff
  Serial.begin(9600);  // initialize serial communications at 9600 bps
  Serial.print("Setup");
  joysticklib.begin();


  //---------Setting up digital pins----------
  int counter = 0;
  for(int i = FIRSTPIN_RIGHTHEADER; i < LASTPIN_RIGHTHEADER; i++){
    pinMode(i, INPUT_PULLUP);
    togglePins[counter] = i;
    toggleVals[counter] = 0;
    counter++;
  }
  counter =0;
  for(int i = A0; i<A11; i++){
    analogPins[counter] = i;
    analogVals[counter] = false;
    counter++;
  }

  //------setting up joysticks-------------



  //----------Setting up throttle----------




}

class Joystick
{
    public:
      Joystick() = delete;
      Joystick(int analogPinX, int analogPinY, int digitalPin, int maxAnalogValue, int minAnalogValue):
        m_analogPinX(analogPinX),
        m_analogPinY(analogPinY),
        m_digitalPin(digitalPin),
        m_maxAnalogValue(maxAnalogValue),
        m_minAnalogValue(minAnalogValue)
        {}

      int getAnalogValueX()
      {
        int rawValue = analogRead(m_analogPinX);
        int value = map(rawValue, 0, 1023, m_minAnalogValue, m_maxAnalogValue);
        return value;
      }

      int getAnalogValueY()
      {
        int rawValue = analogRead(m_analogPinY);
        int value = map(rawValue, 0, 1023, m_minAnalogValue, m_maxAnalogValue);
        return value;
      }

      void readDigitalValue

      bool getDigitalValue()
      {
        bool value = digitalRead(m_digitalPin);
        return value;
      }

    protected:
      int m_maxAnalogValue;
      int m_minAnalogValue;
      int m_analogPinX;
      int m_analogPinY;
      int m_digitalPin;
};

class ThreeAxisJoystick: public Joystick {
  public:
    ThreeAxisJoystick() = delete;
    ThreeAxisJoystick(int analogPinX, int analogPinY, int analogPinZ, int digitalPin, int maxAnalogValue, int minAnalogValue):
        Joystick(analogPinX, analogPinY, digitalPin, maxAnalogValue, minAnalogValue),
        m_analogPinZ(analogPinZ)
        {}

      int getAnalogValueZ()
      {
        int rawValue = analogRead(m_analogPinZ);
        int value = map(rawValue, 0, 1023, m_minAnalogValue, m_maxAnalogValue);
        return value;
      }

  private:
    int m_analogPinZ;

};

