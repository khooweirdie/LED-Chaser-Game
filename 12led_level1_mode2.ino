// C++ code

int i = 0;
int score = 0;

int diff = 1; //difficulty of the game (speed of LEDs blinking)
int tint = 750; //time intervals

int led_0 = 1;
int led_1 = 0; //target
int led_2 = 0;
int led_3 = 0; 
int led_4 = 0; //target
int led_5 = 0;
int led_6 = 0; 
int led_7 = 0; //target
int led_8 = 0;
int led_9 = 0;
int led_10 = 0; //target
int led_11 = 0;
int led_12 = 0; //temporary variable

byte inputState;
//----- ISR variables ---------
volatile unsigned long minElapsed = 250;
volatile unsigned long maxElapsed = 1000;
volatile unsigned long elapsedTime;
volatile unsigned long previousTime;
volatile byte cleanOutput;
volatile byte timeout;

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

    //Difficulty setting button
    attachInterrupt(digitalPinToInterrupt(3), set, RISING); 
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
 elapsedTime = millis() - previousTime;
  if (elapsedTime < minElapsed )  //false interrupt
  {
    return;
  }
  if (elapsedTime >= minElapsed && elapsedTime <= maxElapsed )  //in range
  {
    previousTime = millis();
    timeout = 0;
    if (inputState)               //falling
    {
      cleanOutput = 0;
    }
    else                          //rising
    {
      cleanOutput = 1;
    }
    return;
  }
  if (elapsedTime > maxElapsed )  //timeout
  {
    previousTime = millis();
    timeout = 1;
  }
 if (digitalRead(12) == HIGH || digitalRead(9) == HIGH || digitalRead(6) == HIGH || digitalRead(18) == HIGH)
 {
  //Win
   Serial.println("You catched it!");
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
 else
 {
   //Lose
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

void set()
{
   elapsedTime = millis() - previousTime;
  if (elapsedTime < minElapsed )  //false interrupt
  {
    return;
  }
  if (elapsedTime >= minElapsed && elapsedTime <= maxElapsed )  //in range
  {
    previousTime = millis();
    timeout = 0;
    if (inputState)               //falling
    {
      cleanOutput = 0;
    }
    else                          //rising
    {
      cleanOutput = 1;
    }
    return;
  }
  if (elapsedTime > maxElapsed )  //timeout
  {
    previousTime = millis();
    timeout = 1;
  }
   Serial.println("The button is pressed!");
   diff = diff + 1;
  
   switch(diff)
   {
   case 2:
     Serial.println("Normal Mode :)"); 
     tint = 300;
     break;
    case 3:
      Serial.println("Hard Mode :')");
      tint = 200;
      break;
   default:
      Serial.println("Back to Easy Mode :P");
      tint = 500;
      diff = 1;
      break;
   }
  }
