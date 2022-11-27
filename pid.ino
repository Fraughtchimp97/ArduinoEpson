#include <OneWire.h> 
#include <DallasTemperature.h>

const int oneWireBus = 4;    
OneWire oneWire(oneWireBus);
DallasTemperature sensor(&oneWire);

#include "BluetoothSerial.h" 
BluetoothSerial ESP_BT; 

#define RXD2 16
#define TXD2 17
#define resistencia 2 

int t2; 
int incoming;   
float r1=20,t1;            

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  ESP_BT.begin("ESP_SEXO"); 
  sensor.begin();
  pinMode(25, OUTPUT);
}

void loop() {
int decimales;
  if (ESP_BT.available()){
    r1 = ESP_BT.read();
  }
  sensor.requestTemperatures();
  t1=sensor.getTempCByIndex(0);
  t2=int(t1);

  if(r1>t2)
   {
    digitalWrite(25, HIGH);
   }
   else
   {
    digitalWrite(25, LOW);
   }

  decimales=t1*100;
  decimales=decimales%100;
  
  ESP_BT.write(t2); 
  ESP_BT.write(decimales);

  //Serial2.write(t2); 
  //Serial2.write(decimales);

  Serial.println(t1); 
  //Serial.println(decimales);
  
  delay(500);
}
