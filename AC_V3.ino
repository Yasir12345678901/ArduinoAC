#include <Adeept_DHT11.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
Adeept_DHT11 Adeept_dht11;
#define DHT11PIN 2  //Set the digital 2 to the S pin

int whiteButton = 11;   //Button to control the system more
bool mode = true;
int fanA = 3;
int fanB = 4;
int heaterLED = 10;
int redbutton=12;
int bluebutton=13;
int temperature1=30;
int potentio = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(whiteButton, INPUT);
  pinMode(potentio, INPUT);
  pinMode(fanA, OUTPUT);
  pinMode(fanA, OUTPUT);
  pinMode(heaterLED, OUTPUT);
  pinMode(bluebutton,INPUT);
  pinMode(redbutton,INPUT);
  Adeept_dht11.read(DHT11PIN);
  lcd.init();
  lcd.backlight();
}

void loop() {
  if(digitalRead(bluebutton)==LOW){
    temperature1=temperature1-1;
  }
  if(digitalRead(redbutton)==LOW){
    temperature1=temperature1+1;
  }
  if(digitalRead(whiteButton)==LOW){
    mode=!mode;
  }

  if (mode == true){
    Serial.println("Mode: HOT ");
    if (Adeept_dht11.temperature >= 25){
      analogWrite(fanA, analogRead(potentio)/4);
      digitalWrite(heaterLED, LOW);
    }
    else{
      digitalWrite(fanA, LOW);
      digitalWrite(heaterLED, LOW);
    }
  }
  else{
    Serial.println("Mode: COLD");
    if (Adeept_dht11.temperature <= 25){
      digitalWrite(fanA, LOW);
      digitalWrite(heaterLED, HIGH);
    }
    else{
      digitalWrite(fanA, LOW);
      digitalWrite(heaterLED, LOW);
    }
  }
  delay(250);
  lcd.setCursor(0,0);
  lcd.print("C: ");
  lcd.print(Adeept_dht11.temperature);
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(temperature1);
  lcd.setCursor(10,1);
  lcd.print("Mode:");
  lcd.print(mode);
}
