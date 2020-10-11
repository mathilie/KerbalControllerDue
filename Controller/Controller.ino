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
int buttonVals[LEN_BUTTONPINS];
char buttonKeys[LEN_BUTTONPINS];
//ThreeAxisJoystick stick1, stick2;
Joystick_ joysticklib;

void serialAnalogInputs(){
  int x = analogRead(analogPins[0]);
  int y = analogRead(analogPins[1]);
  int z = analogRead(analogPins[2]);
  int throttle = analogRead(analogPins[3]);
  Serial.println("X-axis:"+String(x));
  Serial.println("Y-axis:"+String(y));
  Serial.println("Z-axis:"+String(z));
  Serial.println("Throttle-axis:"+String(throttle));
}
void checkAnalogInputs()
{
  joysticklib.setXAxis(512-analogRead(analogPins[0]));
  joysticklib.setYAxis(512-analogRead(analogPins[1]));
  joysticklib.setZAxis(512-analogRead(analogPins[3]));
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


  //------setting up joysticks-------------

  joysticklib.setXAxisRange(-511,512);
  joysticklib.setYAxisRange(-511,512);
  joysticklib.setZAxisRange(-511,512);

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
