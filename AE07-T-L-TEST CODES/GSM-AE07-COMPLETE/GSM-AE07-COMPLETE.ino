
/*
 * AE07-GSM-SIM800 R/T
 * RS485
 * SIM800C
 * All Output Turn ON Series
 * All input status serial print
 * 
  Turns ON All Outputs in series
  Serial prints all the input status
  SIM800C External Antenna Test
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "FS.h"
#include <Adafruit_GFX.h>

#define ANALOG_PIN_0 36

#define INPUT1 35
#define INPUT2 34
#define INPUT3 21
#define INPUT4 14
#define INPUT5 13
#define INPUT6 4
#define INPUT7 15
#define INPUT8 26

#define OUTPUT1 12
#define OUTPUT2 2
#define OUTPUT3 27
#define OUTPUT4 5
#define OUTPUT5 23
#define OUTPUT6 18 

#define RS485_RX 25
#define RS485_TX 19
#define RS485_FC 22

#define GSM_RX 33
#define GSM_TX 32

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int analog_value = 0;
  
int readSwitch(){
  analog_value = analogRead(ANALOG_PIN_0); 
  return analog_value; //Read analog
}

unsigned long int timer1 = 0;

// ================================================ SETUP ================================================
void setup() {
  Serial.begin(115200);

  Serial.println("Hello");
  
  pinMode(RS485_FC, OUTPUT);
  digitalWrite(RS485_FC, HIGH);   // RS-485 
    
  Serial1.begin(9600, SERIAL_8N1, RS485_RX, RS485_TX); 
  Serial2.begin(9600, SERIAL_8N1, GSM_TX, GSM_RX); 
   
  pinMode(OUTPUT1, OUTPUT);
  pinMode(OUTPUT2, OUTPUT);
  pinMode(OUTPUT3, OUTPUT);
  pinMode(OUTPUT4, OUTPUT);
  pinMode(OUTPUT5, OUTPUT);
  pinMode(OUTPUT6, OUTPUT);
  
  pinMode(INPUT1, INPUT);
  pinMode(INPUT2, INPUT);
  pinMode(INPUT3, INPUT);
  pinMode(INPUT4, INPUT);
  pinMode(INPUT5, INPUT);
  pinMode(INPUT6, INPUT);
  pinMode(INPUT7, INPUT);
  pinMode(INPUT8, INPUT);
  
  Wire.begin(16,17);
  Serial.println("Initializing DIsplay");
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  
  Serial.println("Testing Modem");
  
  timer1 = millis();
  Serial2.println("AT");
  while(millis()<timer1+10000){
    while (Serial2.available()) {
    int inByte = Serial2.read();
    Serial.write(inByte);
    }
  }

  timer1 = millis();
  Serial2.println("AT+CPIN?");
  while(millis()<timer1+10000){
    while (Serial2.available()) {
    int inByte = Serial2.read();
    Serial.write(inByte);
    }
  }
  timer1 = millis();
  Serial2.println("AT+CFUN?");
  while(millis()<timer1+10000){
    while (Serial2.available()) {
    int inByte = Serial2.read();
    Serial.write(inByte);
    }
  }

  Serial.println("Testing Modem Done");
  adcAttachPin(36);

  digitalWrite(RS485_FC, HIGH);   // RS-485 
}

void loop() {  
  // put your main code here, to run repeatedly:
  while (Serial.available()) {
    int inByte = Serial.read();
    Serial2.write(inByte);
  }

  while (Serial2.available()) {
    int inByte = Serial2.read();
    Serial.write(inByte);
  }
 
  Serial.print(digitalRead(INPUT1));
  Serial.print(digitalRead(INPUT2));
  Serial.print(digitalRead(INPUT3));
  Serial.print(digitalRead(INPUT4));
  Serial.print(digitalRead(INPUT5));
  Serial.print(digitalRead(INPUT6));
  Serial.print(digitalRead(INPUT7));
  Serial.print(digitalRead(INPUT8));
  Serial.println(""); 

  Serial.println(""); 
  Serial.print("Push button  ");
  Serial.println(readSwitch());
  Serial.println(""); 
  
  digitalWrite(OUTPUT1, HIGH);
  digitalWrite(OUTPUT2, LOW);
  digitalWrite(OUTPUT3, LOW);
  digitalWrite(OUTPUT4, LOW);
  delay(200);
  digitalWrite(OUTPUT1, LOW);
  digitalWrite(OUTPUT2, HIGH);
  delay(200);
  digitalWrite(OUTPUT2, LOW);
  digitalWrite(OUTPUT3, HIGH);
  delay(200);
  digitalWrite(OUTPUT3, LOW);
  digitalWrite(OUTPUT4, HIGH);
  delay(200);
  digitalWrite(OUTPUT4, LOW);
  digitalWrite(OUTPUT5, HIGH);
  delay(200);
  digitalWrite(OUTPUT5, LOW);
  digitalWrite(OUTPUT6, HIGH);
  delay(200);
  digitalWrite(OUTPUT6, LOW);
  delay(200);
  
  digitalWrite(RS485_FC, HIGH);                    // Make FLOW CONTROL pin HIGH
  delay(500);
  Serial1.println(F("RS485 01 SUCCESS"));          // Send RS485 SUCCESS serially
  delay(500);                                      // Wait for transmission of data
  digitalWrite(RS485_FC, LOW) ;                    // Receiving mode ON                                                   // Serial1.flush() ;
  delay(500);     
  
  while (Serial1.available()) {  // Check if data is available
    char c = Serial1.read();     // Read data from RS485
    Serial.write(c);             // Print data on serial monitor
  }
 //Serial2.println("AT");
 delay(500); 
}
