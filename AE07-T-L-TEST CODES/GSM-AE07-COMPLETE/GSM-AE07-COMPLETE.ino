/*
 * Test Program for NORVI IIOT V2.0
 * Use appropriate libraries supplied.
 * All Outputs should be on when turned on Supplying power to inputs should turn on Relays.
 * Display shows ADC values from Buit-in buttons. Pressing Built-in buttons should change Value displayed on Display 
 */

#include <Adafruit_ADS1X15.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_ADS1115 ads1;
Adafruit_ADS1115 ads2;

#define ANALOG_PIN_0 36

#define INPUT1 34
#define INPUT2 35
#define INPUT3 14
#define INPUT4 13
#define INPUT5 5
#define INPUT6 15
#define INPUT7 19

#define OUTPUT1 12
#define OUTPUT2 2
#define OUTPUT3 27
#define OUTPUT4 4
#define OUTPUT5 23
#define OUTPUT6 18

#define RS485_RX 25
#define RS485_TX 26
#define RS485_FC 22

#define GSM_RX 32
#define GSM_TX 33
#define GSM_RESET 21

unsigned long int timer1 = 0;
int analog_value = 0;
int reading[8]={0};
String adcString[8];
  
int readSwitch(){
  analog_value = analogRead(ANALOG_PIN_0);
  return analog_value; //Read analog
}
// ================================================ SETUP ================================================
void setup() {  
  Serial.begin(115200);
  Serial.println("Hello");
  
  pinMode(RS485_FC, OUTPUT);
  digitalWrite(RS485_FC, HIGH);   // RS-485 
  
  Serial1.begin(9600, SERIAL_8N1, RS485_RX, RS485_TX); 
  Serial2.begin(115200, SERIAL_8N1, GSM_RX, GSM_TX); 

  pinMode(GSM_RESET, OUTPUT);
  digitalWrite(GSM_RESET, HIGH);    

  Wire.begin(16,17);
  delay(100);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
  }

  display.display();
  
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
    
  adcAttachPin(36);
  timer1 = millis();
  Serial2.println("AT");
  while(millis()<(timer1+10000)){
    while (Serial2.available()) {
    int inByte = Serial2.read();
    Serial.write(inByte);
    }
  }

  timer1 = millis();
  Serial2.println("AT+CPIN?");
  while(millis()<(timer1+10000)){
    while (Serial2.available()) {
    int inByte = Serial2.read();
    Serial.write(inByte);
    }
  }
}

void loop() {
  // read from port 0, send to port 1:
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
  Serial.println(""); 

  Serial.println(""); 
  Serial.print("Push button  ");
  Serial.println(readSwitch());
  Serial.println(""); 
    
  digitalWrite(OUTPUT1, HIGH);
  digitalWrite(OUTPUT2, LOW);
  digitalWrite(OUTPUT3, LOW);
  digitalWrite(OUTPUT4, LOW);
  digitalWrite(OUTPUT5, LOW);
  digitalWrite(OUTPUT6, LOW);
  delay(500);
  digitalWrite(OUTPUT1, LOW);
  digitalWrite(OUTPUT2, HIGH);
  digitalWrite(OUTPUT3, LOW);
  digitalWrite(OUTPUT4, LOW);
  digitalWrite(OUTPUT5, LOW);
  digitalWrite(OUTPUT6, LOW);
  delay(500);
  digitalWrite(OUTPUT1, LOW);
  digitalWrite(OUTPUT2, LOW);
  digitalWrite(OUTPUT3, HIGH);
  digitalWrite(OUTPUT4, LOW);
  digitalWrite(OUTPUT5, LOW);
  digitalWrite(OUTPUT6, LOW);
  delay(500);
  digitalWrite(OUTPUT1, LOW);
  digitalWrite(OUTPUT2, LOW);
  digitalWrite(OUTPUT3, LOW);
  digitalWrite(OUTPUT4, HIGH);
  digitalWrite(OUTPUT5, LOW);
  digitalWrite(OUTPUT6, LOW);
  delay(500);
  digitalWrite(OUTPUT1, LOW);
  digitalWrite(OUTPUT2, LOW);
  digitalWrite(OUTPUT3, LOW);
  digitalWrite(OUTPUT4, LOW);
  digitalWrite(OUTPUT5, HIGH);
  digitalWrite(OUTPUT6, LOW);
  delay(500);
  digitalWrite(OUTPUT1, LOW);
  digitalWrite(OUTPUT2, LOW);
  digitalWrite(OUTPUT3, LOW);
  digitalWrite(OUTPUT4, LOW);
  digitalWrite(OUTPUT5, LOW);
  digitalWrite(OUTPUT6, HIGH);
  delay(500);
  digitalWrite(OUTPUT1, LOW);
  digitalWrite(OUTPUT2, LOW);
  digitalWrite(OUTPUT3, LOW);
  digitalWrite(OUTPUT4, LOW);
  digitalWrite(OUTPUT5, LOW);
  digitalWrite(OUTPUT6, LOW);

  Serial1.println("Hello RS-485");
  delay(1000);
}
