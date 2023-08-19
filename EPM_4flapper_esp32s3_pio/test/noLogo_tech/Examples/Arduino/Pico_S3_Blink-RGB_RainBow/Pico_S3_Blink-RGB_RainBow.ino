/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LEDS_COUNT  8
#define LEDS_PIN	48
#define CHANNEL		0

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT); 
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);

  pinMode(33, OUTPUT);  
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);  
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);

  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);
  pinMode(48, OUTPUT);
    strip.begin();
  strip.setBrightness(20);  
}

// the loop function runs over and over again forever
void loop() {
 digitalWrite(1, HIGH);   
  digitalWrite(2, HIGH);  
  digitalWrite(3, HIGH);   
  digitalWrite(4, HIGH);  
  digitalWrite(5, HIGH);     
  digitalWrite(6, HIGH);   
  digitalWrite(7, HIGH);   
  digitalWrite(8, HIGH); 
  digitalWrite(9, HIGH);     
  digitalWrite(10, HIGH);   
  digitalWrite(11, HIGH);   
  digitalWrite(12, HIGH); 
  digitalWrite(13, HIGH);     
  digitalWrite(14, HIGH);   
  digitalWrite(15, HIGH);   
  digitalWrite(16, HIGH);
  digitalWrite(17, HIGH);  
  digitalWrite(19, HIGH);
  digitalWrite(20, HIGH);    
  digitalWrite(18, HIGH);   
  digitalWrite(33, HIGH);   
  digitalWrite(34, HIGH); 
  digitalWrite(35, HIGH);  
  digitalWrite(36, HIGH);   
  digitalWrite(37, HIGH); 
  digitalWrite(38, HIGH);   
  digitalWrite(39, HIGH);   
  digitalWrite(40, HIGH); 
  digitalWrite(41, HIGH);     
    digitalWrite(42, HIGH); 
    
  digitalWrite(45, HIGH);   
  digitalWrite(46, HIGH); 
  digitalWrite(47, HIGH);     


      for (int j = 0; j < 255; j += 2) {
    for (int i = 0; i < LEDS_COUNT; i++) {
      strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255));
    }
    strip.show();
    delay(10);
  } 
  delay(1000);     
 digitalWrite(1, LOW);   
  digitalWrite(2, LOW);  
  digitalWrite(3, LOW);   
  digitalWrite(4, LOW);  
  digitalWrite(5, LOW);     
  digitalWrite(6, LOW);   
  digitalWrite(7, LOW);   
  digitalWrite(8, LOW); 
  digitalWrite(9, LOW);     
  digitalWrite(10, LOW);   
  digitalWrite(11, LOW);   
  digitalWrite(12, LOW); 
  digitalWrite(13, LOW);     
  digitalWrite(14, LOW);   
  digitalWrite(15, LOW);   
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);     
  digitalWrite(18, LOW);   
  digitalWrite(19, LOW);     
  digitalWrite(20, LOW); 
  digitalWrite(33, LOW);   
  digitalWrite(34, LOW); 
  digitalWrite(35, LOW);  
    digitalWrite(36, LOW);   
  digitalWrite(37, LOW); 
  digitalWrite(38, LOW);   
    digitalWrite(39, LOW);   
  digitalWrite(40, LOW); 
  digitalWrite(41, LOW);     
    digitalWrite(42, LOW); 
  digitalWrite(45, LOW); 
  digitalWrite(46, LOW);     
    digitalWrite(47, LOW); 
  delay(1000);                       // wait for a second
  
}
