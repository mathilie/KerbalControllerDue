#include <Joystick.h>
#include<Keyboard.h>

#define FIRSTPIN_RIGHTHEADER 22
#define LASTPIN_RIGHTHEADER 53

#define LEN_DIGITALPINS LASTPIN_RIGHTHEADER - LASTPIN_RIGHTHEADER
#define LEN_ANALOGPINS 12

int digitalPins[LEN_DIGITALPINS];
bool digitalVals[LEN_DIGITALPINS];
int analogPins[LEN_ANALOGPINS];
int analogVals[LEN_ANALOGPINS];

void checkAnalogInputs()
{
  for(int i=0; i<LEN_ANALOGPINS;i++)
  {
    analogVals[i]=analogRead(i);
  }
}


void checkDigitalInputs()
{
  for(int i=0; i<LEN_DIGITALPINS;i++)
  {
    digitalVals[i] = digitalRead(digitalPins[i]);
  }
}

class Joystick
{
    public:
      Joystick() = delete;
      Joystick(int analogPinX, int analogPinY, int digtialPin, int maxAnalogValue, int minAnalogValue): 
        m_analogPinX(analogPinX), 
        m_analogPinY(analogPinY), 
        m_digtialPin(digtialPin), 
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
        bool value = digitalRead(m_digtialPin);
        return value;
      }
        
    protected:
      int m_maxAnalogValue;
      int m_minAnalogValue;
      int m_analogPinX;
      int m_analogPinY;
      int m_digtialPin;
};

class ThreeAxisJoystick: public Joystick {
  public:
    ThreeAxisJoystick() = delete;
    ThreeAxisJoystick(int analogPinX, int analogPinY, int analogPinZ, int digtialPin, int maxAnalogValue, int minAnalogValue): 
        Joystick(analogPinX, analogPinY, digtialPin, maxAnalogValue, minAnalogValue),
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



/******************************************
* 
* Baktanken med koden er at man har én metode for hver inputtype.
* De digitale sender bare hvis de er endret.
* Pythonkoden holder styr på om det skal sendes signal videre.
* Muligens bør trottle skilles ut fra analoge
*
*******************************************/

void setup()
{
  Serial.begin(9600);  // initialize serial communications at 9600 bps
  Serial.print("Setup");
  //Setting up digital pins
  int counter = 0;
  for(int i = FIRSTPIN_RIGHTHEADER; i < LASTPIN_RIGHTHEADER; i++){
    pinMode(i, INPUT_PULLUP);
    digitalPins[counter] = i;
    digitalVals[counter] = 0;
    counter++;
  }
  counter =0;
  for(int i = A0; i<A11; i++){
    analogPins[counter] = i;
    analogVals[counter] = false;
    counter++;
  }
   pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  //checkAnalogInputs();
  //checkDigitalInputs;
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(1000);                       // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1);
  int value = digitalRead(30);
  Serial.print("Value of pin 30: ");
  Serial.println(value);
}
