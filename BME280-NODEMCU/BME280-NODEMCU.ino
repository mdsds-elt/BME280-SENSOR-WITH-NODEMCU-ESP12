/***************************
  Autora : Márcia de Sá 
  BME280 | OLED | ESP8266
****************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*******************
#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5
********************/

int buzzer = 0;/*buzzer!!*/
int pin_led_verm = 14;/* D5 | Led vermelho*/
int pin_led_verde = 12;/* D6 | Led verde*/

Adafruit_BME280 bme; //comunicação I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
unsigned long delayTime;

void setup() {
  
  pinMode(buzzer, OUTPUT);
  pinMode(pin_led_verm, OUTPUT);
  pinMode(pin_led_verde, OUTPUT);
  
  Serial.begin(115200);
  Serial.println(F("BME280 test"));
   
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C 
   // init done
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1.5);// era 1.2
  display.setTextColor(WHITE);
  
  bool status;
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("ERRO AO ENCONTRAR O SENSOR!");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}


void loop() { 
   
  /*Diplay*/
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1.9);
  
  /*Temperatura*/
  Serial.print("Temperature = "); 
  Serial.print(bme.readTemperature()); 
  Serial.println(" C");
  display.print("TEMPERATURA: "); 
  display.print(bme.readTemperature()); 
  //display.write(3);
  display.println(" C");

  /*Umidade*/
  Serial.print("Humidity = "); 
  Serial.print(bme.readHumidity()); 
  Serial.println(" %");
  display.print("UMIDADE: "); 
  display.print(bme.readHumidity()); 
  display.println(" %");
    

  if (bme.readTemperature() > 32)
  {
   //tone(buzzer, 1000, 200);
   digitalWrite(pin_led_verm, HIGH);
   digitalWrite(pin_led_verde, LOW);
   tone(buzzer, 1000, 200);
   }
   else
   {
    digitalWrite(pin_led_verm, LOW);/*Desliga O led Vermelho*/
    digitalWrite(pin_led_verde, HIGH);/*Liga O led Verde*/
    noTone(buzzer);
    }
    delay(100);


    Serial.println();
    display.display();
    delay(1000);
  }

  
