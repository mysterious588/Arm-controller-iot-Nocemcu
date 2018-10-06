#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h>
#define WIFI_SSID "elmatar"
#define WIFI_PASSWORD "rt600600r"
//initialize servos
Servo servoX;
Servo servoY;
Servo grapper;
Servo z;
//Android app info
String FIREBASE_HOST = "arm-controller-11c79.firebaseio.com";
String FIREBASE_AUTH = "ua89iusoIZdwK5E2MfMpZBWNTzb92rhrbJXv0gtU";
//integers to store the values from the android app
int val1, val2, val3,val4, Mode;
//wifi info


void setup()
{ //servo pins
servoX.attach(D1);
servoY.attach(D2);
z.attach(D3);
grapper.attach(D4);
servoX.write(50);
servoY.write(50);
grapper.write(85);
z.write(50);

  Serial.begin(115200);
  //connect to wifi
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
  Serial.print(".");
  delay(500);
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());
//connect to the android app
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  delay(2000);
}
void firebasereconnect()
{
  WiFi.disconnect();
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status()!=WL_CONNECTED){
  Serial.print(".");
  delay(500);}
  
  Serial.println("WiFi reconnected");
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    delay(2000);   
}
void loop()
{


      //firebase read
      val1=Firebase.getInt("servo1");  
              Serial.println(val1);

      val2=Firebase.getInt("servo2");
              Serial.println(val2);
              // grapper and z swapped .. mb 
      val3=Firebase.getInt("z");
              Serial.println(val3);
              
      val4=Firebase.getInt("grapper");
              Serial.println(val4);
  if(Firebase.failed())
  {
   firebasereconnect();  
  }
constrain(val1,10,180);
constrain(val2,10,180);
constrain(val3,10,180);
constrain(val4,80,120);

   if (val1 == 0 || val2 == 0 || val3 == 0 || val4 == 0)
   {
        servoX.write(50);
        servoY.write(50);
        grapper.write(120);
        z.write(50);
   }

     else{   //manual mode
        servoX.write(val1);
        servoY.write(val2);
        grapper.write(val3);
        z.write(val4);
      
     }
}
