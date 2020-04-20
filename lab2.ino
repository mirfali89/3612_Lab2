
// set pin numbers:
const int buttonOne = 33;     // the number of the pushbutton pin
const int buttonTwo = 32;     // the number of the pushbutton pin
const int ledGreen =  38;     // the number of the LED pin
const int ledBlue =  37;      // the number of the LED pin
const int buzzer =   40;      // Buzzer
const int res = PUSH1;        // Reset button (left)
// variables will change:
int buttonOneState = HIGH;    // variable for reading the pushbutton #1 status
int buttonTwoState = HIGH;    // variable for reading the pushbutton #2 status

int buttonOnePrev = HIGH;
int buttonTwoPrev = HIGH;

int buttonOneStateR = HIGH;
int buttonTwoStateR = HIGH; 

int resState = HIGH;          // variable for reading the pushbutton reset status
unsigned int cnt1 = 0;        // counter for s1
unsigned int cnt2 = 0;        // counter for s2
unsigned int freq1 = 500;     // First Frequency
unsigned int freq2 = 550;     // Alternative Frequency
int ledState1 = LOW;          // State of LED Blue on/off
int ledState2 = LOW;          // State of LED Green on/off

unsigned int button1 = 1;     // S1 Button is being pressed
unsigned int button2 = 0;     // S2 Button is being pressed
int led = 0;                  // number of blinks s1

long lastDebounceTime = 0;  // the last time the output pin was toggled
long interval = 1000;         // Debouncer interval

// -----------------------------------------------------------------------------------
int series(unsigned int &n)   // Series Function
{
 return ((sq(n)+1)/2);
}
// -----------------------------------------------------------------------------------
                              // Button Function
void button(int &buttonState,const int &ledPin, int &ledState, unsigned int &counter, unsigned int &which)
{  
  
  if(which == 1)
  {
   led = series(counter); // where led is the number of blinks after (n^2+1)/2 function
  }
  else
  {
      led = counter;
         Serial.println(led, DEC);
  }
   Serial.println(led, DEC);
  
   tone(buzzer, freq1 , 100);
   tone(buzzer, freq2, 100);
    for( int i = 0; i < led; i++) // LED blinks "led" times
    {
        // Blinks Led once
        if (ledState == LOW)
        {
          ledState = HIGH;
          digitalWrite(ledPin, ledState);
          delay(250);
          ledState = LOW;
          digitalWrite(ledPin, ledState);
          delay(250);
        }
     }
}
// -----------------------------------------------------------------------------------
void setup()
{
   Serial.begin(9600);  
                // initialize the LED pins as  output:
  pinMode(ledBlue, OUTPUT);  
  pinMode(ledGreen, OUTPUT);     
                // initialize the pushbutton pin as an input:
  pinMode(buttonOne, INPUT_PULLUP);     
  pinMode(buttonTwo, INPUT_PULLUP); 
  pinMode(res, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
}
// ----------------------------------------------------------------------------------
void loop()
{
  // put your main code here, to run repeatedly:
    // unsigned long currentMillis = millis();
    unsigned long previousMillis;
    unsigned long currentMillis = millis();
    
    buttonOneStateR = digitalRead(buttonOne);
    buttonTwoStateR = digitalRead(buttonTwo);
    resState = digitalRead(res);
    
    if (buttonOneStateR != buttonOnePrev )
    {
    // reset the debouncing timer
    lastDebounceTime = currentMillis;
    } 
  
  if(buttonTwoStateR != buttonTwoPrev)
  {
    lastDebounceTime = currentMillis; 
  }
   
  
  if(currentMillis - lastDebounceTime > interval) 
  {
    // save the last time you blinked the LED 
    
      buttonOneState = buttonOneStateR;
     
      buttonTwoState = buttonTwoStateR;
      
    
  
  
       
    
    if (buttonOneState == LOW)
    {
      
       cnt1++;
      Serial.println(cnt1, DEC);
      button(buttonOneState, ledBlue, ledState1, cnt1, button1);
    }
    
    if (buttonTwoState == LOW)
    {
      cnt2++;
      button(buttonTwoState, ledGreen, ledState2, cnt2, button2);
    }
  
   
  }
  
       if( resState == LOW)
     {
       Serial.println(res,DEC);
     tone(buzzer, freq1 , 100);
     //tone(buzzer, freq2, 100);
       cnt1 = 0;
       cnt2 = 0;
      
     }
        buttonOnePrev = buttonOneStateR;
        buttonTwoPrev = buttonTwoStateR;
  
  
}
