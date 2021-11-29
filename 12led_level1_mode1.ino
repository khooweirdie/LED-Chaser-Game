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

void setup()
{
    Serial.begin(9600);
    
    //7 LEDs 
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
    pinMode(19, OUTPUT);
    pinMode(18, OUTPUT);
  
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
    digitalWrite(19, LOW);
    digitalWrite(18, LOW);
  
    //Declare the CATCH button
    attachInterrupt(digitalPinToInterrupt(2), check, RISING);  
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
      digitalWrite(19, led_6);
      digitalWrite(18, led_7);
      digitalWrite(4, led_8);
      digitalWrite(5, led_9);
      digitalWrite(6, led_10);
      digitalWrite(7, led_11);
      
      delay(tint); 
}

void check()
{
  
 if (led_1 == HIGH || led_4 == HIGH || led_7 == HIGH || led_10 == HIGH)
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
