// C++ code

int i = 0;

int diff = 1; // Difficulty of the game (speed of LEDs blinking)
int tint = 0; // Time intervals

int led_0 = 1;
int led_1 = 0;
int led_2 = 0;
int led_3 = 0; // Target LED
int led_4 = 0;
int led_5 = 0;
int led_6 = 0;

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
  
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
  
    //Declare the CATCH button
    attachInterrupt(digitalPinToInterrupt(2), check, RISING);  
    
  
    //Difficulty setting button
    pinMode(5, INPUT);
}

void loop()
{
    // The difficulty only can be chosen before the first LED blinks
    
  i = digitalRead(5);
  
  if (digitalRead(5) == HIGH)
  {
    Serial.println("The button is pressed!");
    diff = diff + 1;
  }
  if(diff == 1)
    {
      Serial.println("Easy Mode :D");
      tint = 500;
    }
  else if(diff == 2)
    {
     Serial.println("Normal Mode :)"); 
     tint = 300;
    }
  else if(diff == 3)
    {
      Serial.println("Hard Mode :')");
      tint = 200;
    }
  
    
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

void check()
{
  // Trigger if CATCH
 if (led_3 == HIGH)
 {
  //Win
   Serial.println("You catched it!");
   digitalWrite(13, HIGH);
   digitalWrite(12, HIGH);
   digitalWrite(11, HIGH);
   digitalWrite(10, HIGH);
   digitalWrite(9, HIGH);
   digitalWrite(8, HIGH);
   digitalWrite(7, HIGH);

 }
 // Trigger if NOT CATCH
 else
 {
   //Lose
   Serial.println("Oops! Try again!");
   digitalWrite(13, LOW);
   digitalWrite(11, LOW);
   digitalWrite(10, LOW);
   digitalWrite(9, LOW);
   digitalWrite(8, LOW);
   digitalWrite(7, LOW);

 }
}
