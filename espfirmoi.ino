#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
//#define FIREBASE_HOST "newprg-54653.firebaseio.com"
//#define FIREBASE_AUTH "jcQWWIvOURcTcD0PmxgwxvpVWjG0Ab5QmEJtUSb8"
#define FIREBASE_HOST "smartgarden-153f0.firebaseio.com"
#define FIREBASE_AUTH "JAdIGqeEFgpkWa2cOHemF8cAL3QMANN6P8ybTyWp"
#define WIFI_SSID "amit"
#define WIFI_PASSWORD "amit1234"

/////moisture sensor pins
int sensor_pin = A0;

int output_value ;
int ph=D2;

/////temperaturre sensor pins

#define ONE_WIRE_BUS D1
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
 Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  sensors.begin(); 
  pinMode(ph,HIGH);
//Firebase.setString("status1","4");
 // Firebase.setInt("motor",1);
}
void firebasereconnect(){
  Serial.println("Trying to reconnect");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 
  }

void loop() {

  if (Firebase.failed()) {// Check for errors 
  {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    firebasereconnect();
    delay(1000);
    return;
  }
 
delay(1000);
}

////reading moisture sensor value

output_value= analogRead(sensor_pin);

   output_value = map(output_value,550,0,0,100);

   Serial.print("Mositure : ");

   Serial.print(output_value);

   Serial.println("%");
   //Firebase.setString("moisture","output_value");
   String myString = String(output_value);
    Firebase.setString("Moisture",myString);

   delay(1000);



////reading tempertaure sensor value

 sensors.requestTemperatures();
 Serial.print("Temperature is: "); 
 Serial.print(sensors.getTempCByIndex(0));
// 
// Firebase.setInt("temperature",sensors.getTempCByIndex(0));
String temp=String(sensors.getTempCByIndex(0));
Firebase.setString("temp",temp);

  delay(1000); 

/////////////////reading ph value

 int sensor_val=analogRead(ph);
 float voltage=sensor_val*(5.0/1023.0);
 float val=sensor_val/1000;
 float res=val+6.5;
  delay(1000);
 Serial.println("ph");
  Serial.print(res);
   String result = String(res);
   Firebase.setString("ph",result);

 /* // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
     Serial.println(Firebase.error()); 
      return;
  }
    delay(1000);


   // set bool value
  Firebase.setBool("truth", false);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /truth failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  // append a new value to /logs
 // String name = Firebase.pushInt("logs", 3.0);
  // handle error
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  Serial.print("pushed: /logs/");
  Serial.println(name);
  delay(1000);*/

}

