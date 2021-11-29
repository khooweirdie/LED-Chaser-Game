/* C++ code

Declaration of the variables

Level of difficulty:
1 - Easy Mode
2 - Normal Mode
3 - Hard Mode

*/

// Initiate the difficulty as Easy Mode

int diff = 1;

/*

Time intervals in each difficulty:
1 - tint = 500
2 - tint = 300
3 - tint = 200

*/

int tint = 0; 


// Temporary variables for blinking loop

int led_0 = 1;
int led_1 = 0;
int led_2 = 0;
int led_3 = 0; 
int led_4 = 0;
int led_5 = 0;
int led_6 = 0;

// ISR variables set in the interruption of pin 3

byte inputState;

volatile unsigned long minElapsed = 450;
volatile unsigned long maxElapsed = 900;
volatile unsigned long elapsedTime;
volatile unsigned long previousTime;
volatile byte cleanOutput;
volatile byte timeout;

// Buzzer

const int buzzer = 6;

// 7 segment display

// Variable setting for score

int score = 0;

// Declaration of pins connected

int a = 17;
int b = 18;
int c = 16;
int d = 15;
int e = 14;
int f = 4;
int g = 5;

void setup()
{
    Serial.begin(9600);
    
    // Declare the 7 LED as output
    
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    
    // Set the initial state of the 7 LEDs - LOW
    
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
  
    // Declare the CATCH button as an interruption in pin 2
    
    attachInterrupt(digitalPinToInterrupt(2), check, RISING);  
    
  
    // Declare the Difficulty Setting button as an interruption in pin 3
    
    attachInterrupt(digitalPinToInterrupt(3), set, RISING);
  
    /* 
    For Arduino UNO, only pin 2 and 3 can be set as interruption pins.
    The pin number varies to the model of microcontroller used.
  */

    // Declare the pins connected with 7 segment display as output
    
    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    pinMode(d, OUTPUT);
    pinMode(e, OUTPUT);
    pinMode(f, OUTPUT);
    pinMode(g, OUTPUT);
    
}

void loop()
{
    if(diff == 1)
    {
      tint = 500;
    }

    // LEDs blinking loop (Single route: From left to right)
    
    while (led_6 != 1) 
    {
      led_6 = led_5;
      led_5 = led_4;
      led_4 = led_3;
      led_3 = led_2;
      led_2 = led_1;
      led_1 = led_0;
      led_0 = 0;
      
      digitalWrite(13, led_0);
      digitalWrite(12, led_1);
      digitalWrite(11, led_2);
      digitalWrite(10, led_3);
      digitalWrite(9, led_4);
      digitalWrite(8, led_5);
      digitalWrite(7, led_6);
      
      delay(tint);
    }
    
    // LEDs blinking loop (Single route: From right to left)
    
    while (led_0 != 1)
    {
     led_0 = led_1;
     led_1 = led_2;
     led_2 = led_3;
     led_3 = led_4;
     led_4 = led_5;
     led_5 = led_6;
     led_6 = 0;
      
     digitalWrite(13, led_0);
     digitalWrite(12, led_1);
     digitalWrite(11, led_2);
     digitalWrite(10, led_3);
     digitalWrite(9, led_4);
     digitalWrite(8, led_5);
     digitalWrite(7, led_6);
      
     delay(tint);
    }
}

// ISR mode of the CATCH button
void check()
{

// Trigger only if the button is switched when the target LED is HIGH
  
  if (led_3 == HIGH) 
 {
    // If-else statement to solve the unstable signal from physical push button
  
  elapsedTime = millis() - previousTime;
  
  if (elapsedTime < minElapsed )  //Consider as a false interrupt
  {
    return; 
  }
  if (elapsedTime >= minElapsed && elapsedTime <= maxElapsed )  //Consider as an effective interrupt
  {
    previousTime = millis();
    timeout = 0;
    if (inputState)               //From HIGH to LOW
    {
      cleanOutput = 0;
    }
    else                          //From LOW to HIGH
    {
      cleanOutput = 1;
    }
    return;
  }
  
  if (elapsedTime > maxElapsed )  //Timeout
  {
    previousTime = millis();
    timeout = 1;
  }
  
   // Get 1 point if CATCH! 
    
   score = score + 1;
   
   // Display the score by using 7 segment display
    
    switch(score)
   {
     case(1):
      one();
        break;
      
     case(2):
        two();
        break;
      
     case(3):
        three();
        break;
      
     case(4):
        four();
        break;
      
     case(5):
        five();
        break;
      
     case(6):
        six();
        break;
      
     case(7):
        seven();
        break;
      
     case(8):
        eight();
        break;
      
     case(9):
        nine();
        break;
      
     default:
        zero();
        score = 0;
        break;
   }
    
   tone(buzzer, 5000, 200);
    
   Serial.println("You catched it!");
    
   digitalWrite(13, HIGH);
   digitalWrite(12, HIGH);
   digitalWrite(11, HIGH);
   digitalWrite(10, HIGH);
   digitalWrite(9, HIGH);
   digitalWrite(8, HIGH);
   digitalWrite(7, HIGH);

 }
  
// If not, the LEDs will be LOW and players are allowed to catch it again
 
  else
 {
   // If-else statement to solve the unstable signal from physical push button
  
  elapsedTime = millis() - previousTime;
  
  if (elapsedTime < minElapsed )  //Consider as a false interrupt
  {
    return; 
  }
  if (elapsedTime >= minElapsed && elapsedTime <= maxElapsed )  //Consider as an effective interrupt
  {
    previousTime = millis();
    timeout = 0;
    if (inputState)               //From HIGH to LOW
    {
      cleanOutput = 0;
    }
    else                          //From LOW to HIGH
    {
      cleanOutput = 1;
    }
    return;
  }
  
  if (elapsedTime > maxElapsed )  //Timeout
  {
    previousTime = millis();
    timeout = 1;
  }
  
   tone(buzzer, 4000, 200);
   
   Serial.println("Oops! Try again!");
   
   digitalWrite(13, LOW);
   digitalWrite(11, LOW);
   digitalWrite(10, LOW);
   digitalWrite(9, LOW);
   digitalWrite(8, LOW);
   digitalWrite(7, LOW);

 }
}

// ISR mode

void set()
{
  
  // If-else statement to solve the unstable signal from physical push button
  
  elapsedTime = millis() - previousTime;
  
  if (elapsedTime < minElapsed )  //Consider as a false interrupt
  {
    return; 
  }
  if (elapsedTime >= minElapsed && elapsedTime <= maxElapsed )  //Consider as an effective interrupt
  {
    previousTime = millis();
    timeout = 0;
    if (inputState)               //From HIGH to LOW
    {
      cleanOutput = 0;
    }
    else                          //From LOW to HIGH
    {
      cleanOutput = 1;
    }
    return;
  }
  
  if (elapsedTime > maxElapsed )  //Timeout
  {
    previousTime = millis();
    timeout = 1;
  }
   
   // Increase the difficulty level 
  
   diff = diff + 1;
  
   // Difficulty switching
  
   switch(diff) 
   {
   case 2:
      Serial.println("Normal Mode :)"); 
      tint = 300;
      score = 0; // Reset the score
      zero();
      break;
     
   case 3:
      Serial.println("Hard Mode :')");
      tint = 200;
      score = 0; // Reset the score
      zero();
      break;
     
   default:
      Serial.println("Back to Easy Mode :P");
      tint = 500;
      score = 0; // Reset the score
      zero();
      diff = 1;
      break;
   }
  }

// 7 segments display mode
void one()
{
    digitalWrite(a,LOW);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
    delay(1000);
}
void two()
{
  digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,LOW);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,LOW);
    digitalWrite(g,HIGH);
    delay(1000);
}
void three()
{
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,HIGH);
    delay(1000);
}
void four()
{
    digitalWrite(a,LOW);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
    delay(1000);
}
void five()
{
    digitalWrite(a,HIGH);
    digitalWrite(b,LOW);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
    delay(1000);
}
void six()
{
    digitalWrite(a,HIGH);
    digitalWrite(b,LOW);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
    delay(1000);
}
void seven()
{
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
    delay(1000);
}
void eight()
{
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
    delay(1000);
}
void nine()
{
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
    delay(1000);
}
  void zero()
{
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,LOW);
    delay(1000);
}
