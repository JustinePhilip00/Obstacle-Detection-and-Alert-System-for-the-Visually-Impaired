// include the library code:
#include <LiquidCrystal.h> // library code for the LCD display
#include "DHT.h" //library code for temperature sensor
const int trigpin= 7;
const int echopin= 8;
long duration;
float distance;
int motorPin = 13;    // vibration motor digital pin 13
#define DHTPIN 8 // set the DHT Pin

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  dht.begin();
  
  // Print a message to the LCD.
  lcd.print("Temp:  distance:");
}

void loop() {
delay(100);
  // for calculating distance
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  duration=pulseIn(echopin,HIGH);
  distance = duration*0.0340/2;
  Serial.print(distance);
  
 if (distance<16 && distance>=0)
 {
  digitalWrite(motorPin, HIGH);
 }
 else
 {
  digitalWrite(motorPin, LOW);
 }
 
  delay(150);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  //read temperature in Fahrenheit
  float f = dht.readTemperature(true);

  if (isnan(f)|| isnan(distance)) {
    lcd.print("ERROR");
    return;
  }

  lcd.print(f);
  lcd.setCursor(7,1);
  lcd.print(distance);  
}
