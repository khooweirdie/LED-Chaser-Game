// C++ code

int i = 0;
int score = 0;

// Difficulty of the game (speed of LEDs blinking)
int diff = 1; 

// Time intervals
int tint = 450; 

int led_0 = 1;
int led_1 = 0; // TargetLED
int led_2 = 0;
int led_3 = 0; 
int led_4 = 0; // TargetLED
int led_5 = 0;
int led_6 = 0; 
int led_7 = 0; // TargetLED
int led_8 = 0;
int led_9 = 0;
int led_10 = 0; // TargetLED
int led_11 = 0;
int led_12 = 0; // Temporary variable

byte inputState;
// ISR variables
volatile unsigned long minElapsed = 250;
volatile unsigned long maxElapsed = 1000;
volatile unsigned long elapsedTime;
volatile unsigned long previousTime;
volatile byte cleanOutput;
volatile byte timeout;

// Buzzer
const int buzzer = 3;

// CD4511 -- 7 segment display
int d0 = 17;
int d1 = 16;
int d2 = 15;
int d3 = 14;

void setup()
{
    Serial.begin(9600);
    
    //12 LEDs 
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(18, OUTPUT);
    pinMode(19, OUTPUT);
  
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
    digitalWrite(4, LOW);
    digitalWrite(18, LOW);
    digitalWrite(19, LOW);
  
    //Declare the CATCH button
    attachInterrupt(digitalPinToInterrupt(2), check, RISING);

    //Buzzer
    pinMode(buzzer, OUTPUT);
    digitalWrite(buzzer, LOW); 

    // CD4511 - 7 segment display
    pinMode(d0, OUTPUT);
    pinMode(d1, OUTPUT);
    pinMode(d2, OUTPUT);
    pinMode(d3, OUTPUT);
}

void loop()
{
      led_12 = led_11;
      led_11 = led_10;
      led_10 = led_9;
      led_9 = led_8;
      led_8 = led_7;
      led_7 = led_6;
      led_6 = led_5;
      led_5 = led_4;
      led_4 = led_3;
      led_3 = led_2;
      led_2 = led_1;
      led_1 = led_0;
      led_0 = led_12;
      
      digitalWrite(13, led_0);
      digitalWrite(12, led_1);
      digitalWrite(11, led_2);
      digitalWrite(10, led_3);
      digitalWrite(9, led_4);
      digitalWrite(8, led_5);
      digitalWrite(7, led_6);
      digitalWrite(6, led_7);
      digitalWrite(5, led_8);
      digitalWrite(4, led_9);
      digitalWrite(18, led_10);
      digitalWrite(19, led_11);
      
      delay(tint); 
}

void check()
{
    // If-else statement to accept only one input signal
    /* 
    minElapsed = 250 ms
    maxElapsed = 1000 ms
    */
  elapsedTime = millis() - previousTime;
  if (elapsedTime < minElapsed )  // False interruption
  {
    return;
  }
  if (elapsedTime >= minElapsed && elapsedTime <= maxElapsed )  // Effective interruption
  {
    previousTime = millis();
    timeout = 0;
    if (inputState)               // Falling
    {
      cleanOutput = 0;
    }
    else                          // Rising
    {
      cleanOutput = 1;
    }
    return;
  }
  
  if (elapsedTime > maxElapsed )  // Timeout interruption
  {
    previousTime = millis();
    timeout = 1;
  }
  
  // Check whether the CATCH button is pressed at the moment of target LEDs blink or not
  
  // If CATCH
  
 if (digitalRead(12) == HIGH || digitalRead(9) == HIGH || digitalRead(6) == HIGH || digitalRead(18) == HIGH)
 {

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
      
     case(10):
        
        // Increase the difficulty level if reach 10 pts
      
        diff = diff + 1;
     
     switch(diff)
     {
       case(1):
       tint = 450;
       score = 0;
       zero();
       break;
       
       case(2):
       tint = 350;
       score = 0;
       zero();
       break;
       
       case(3):
       tint = 275;
       score = 0;
       zero();
       break;

       case(4):
       tint = 150;
       score = 0;
       zero();
       break;

       default:
       tint = 450;
       score = 0;
       zero();
       break;
     }
   }
   
   // Buzzer will be triggered if CATCH 
   tone(buzzer, 1000, 100);
  
   // Message delivered on serial monitor if CATCH
   Serial.println("You catched it!");

   // All LEDs blink if CATCH
   digitalWrite(13, HIGH);
   digitalWrite(12, HIGH);
   digitalWrite(11, HIGH);
   digitalWrite(10, HIGH);
   digitalWrite(9, HIGH);
   digitalWrite(8, HIGH);
   digitalWrite(19, HIGH);
   digitalWrite(18, HIGH);
   digitalWrite(4, HIGH);
   digitalWrite(5, HIGH);
   digitalWrite(6, HIGH);
   digitalWrite(7, HIGH);
   delay(tint);
 }
 
 // If NOT CATCH
 else
 {

   // RESET mode
   // Reset the marks and allow players to CATCH again w/o reset difficulty level (Back to Easy Mode)
   
   switch(diff)
     {
       case(1):
     
       // Easy Mode
     
       tint = 450;
       score = 0;
       zero();
       break;
       
       case(2):
     
       // Normal Mode
     
       tint = 350;
       score = 0;
       zero();
       break;
       
       case(3):
     
       // Hard Mode
     
       tint = 275;
       score = 0;
       zero();
       break;

      case(4):
     
       // Challenger Mode
     
       tint = 150;
       score = 0;
       zero();
       break;
       default:
     
       // Back to Easy Mode
     
       tint = 450;
       score = 0;
       zero();
       break;
   }
   
   tone(buzzer, 3000, 100);
   
   Serial.println("Oops! Let's try again!");
   
   digitalWrite(13, LOW);
   digitalWrite(12, LOW);
   digitalWrite(11, LOW);
   digitalWrite(10, LOW);
   digitalWrite(9, LOW);
   digitalWrite(8, LOW);
   digitalWrite(19, LOW);
   digitalWrite(18, LOW);
   digitalWrite(4, LOW);
   digitalWrite(5, LOW);
   digitalWrite(6, LOW);
   digitalWrite(7, LOW);
   delay(tint);
 }
}

// 7 segment display mode
void one()
{
    // 0001
    digitalWrite(d0, LOW);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(d3, HIGH);
    delay(1000);
}
void two()
{
    // 0010
    digitalWrite(d0,LOW);
    digitalWrite(d1,LOW);
    digitalWrite(d2,HIGH);
    digitalWrite(d3,LOW);
     delay(1000);
}
void three()
{
    // 0011
    digitalWrite(d0,LOW);
    digitalWrite(d1,LOW);
    digitalWrite(d2,HIGH);
    digitalWrite(d3,HIGH);
     delay(1000);
}
void four()
{
    // 0100
    digitalWrite(d0,LOW);
    digitalWrite(d1,HIGH);
    digitalWrite(d2,LOW);
    digitalWrite(d3,LOW);
     delay(1000);
}
void five()
{
    // 0101
    digitalWrite(d0,LOW);
    digitalWrite(d1,HIGH);
    digitalWrite(d2,LOW);
    digitalWrite(d3,HIGH);
     delay(1000);
}
void six()
{
    // 0110
    digitalWrite(d0,LOW);
    digitalWrite(d1,HIGH);
    digitalWrite(d2,HIGH);
    digitalWrite(d3,LOW);
     delay(1000);
}
void seven()
{
    // 0111
    digitalWrite(d0,LOW);
    digitalWrite(d1,HIGH);
    digitalWrite(d2,HIGH);
    digitalWrite(d3,HIGH);
     delay(1000);
}
void eight()
{
    // 1000
    digitalWrite(d0,HIGH);
    digitalWrite(d1,LOW);
    digitalWrite(d2,LOW);
    digitalWrite(d3,LOW);
     delay(1000);
}
void nine()
{
    // 1001
    digitalWrite(d0,HIGH);
    digitalWrite(d1,LOW);
    digitalWrite(d2,LOW);
    digitalWrite(d3,HIGH);
     delay(1000);
}
  void zero()
{
    // 0000
    digitalWrite(d0,LOW);
    digitalWrite(d1,LOW);
    digitalWrite(d2,LOW);
    digitalWrite(d3,LOW);
     delay(1000);
}
