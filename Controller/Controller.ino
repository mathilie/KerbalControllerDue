#include <Joystick.h>
#include<Keyboard.h>

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
char buttonKeys[LEN_BUTTONPINS];
//ThreeAxisJoystick stick1, stick2;
Joystick_ joysticklib;

void checkAnalogInputs()
{
  joysticklib.setXAxis(analogRead(analogPins[0]));
  joysticklib.setYAxis(analogRead(analogPins[1]));
  joysticklib.setZAxis(analogRead(analogPins[2]));
  joysticklib.setThrottle(analogRead(analogPins[3]));
}


void checkToggleInputs()
{
  for(int i=0; i<LEN_TOGGLEPINS;i++)
  {
    int currentval = digitalRead(togglePins[i]);
    if(currentval!=toggleVals[i]){
      Keyboard.print("ajaja");
      delay(200);
      toggleVals[i]=currentval;
      delay(1000);
    }
  }
}

void checkButtonInputs()
{
  for(int i=0; i<LEN_BUTTONPINS;i++)
  {
    if(digitalRead(buttonPins[i])==LOW) {
      Keyboard.print("hei");
      delay(10);
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
  buttonKeys[0] = 'a'; //Space
  buttonKeys[1] = 'b';//R


  //------setting up joysticks-------------

  joysticklib.setXAxisRange(0,1023);
  joysticklib.setYAxisRange(0,1023);
  joysticklib.setZAxisRange(0,1023);

  //----------Setting up throttle----------
  joysticklib.setThrottleRange(0,1023);

}


/******************************************
*                                         *
*    HELPING CLASSES                      *
*                                         *
******************************************/
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
