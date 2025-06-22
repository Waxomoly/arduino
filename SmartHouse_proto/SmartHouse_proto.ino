//Video link: https://youtu.be/fpGKZVPLaGQ
#define BLYNK_PRINT Serial
#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>

#include<DHT.h>

char auth[]="PyHzGrHf-F3IQn5m7yB5x2vo_m2iD1rZ";
char ssid[]="wstj-Nusa";
char pass[]="demak437";


BlynkTimer timer;

DHT dht(D2, DHT11);

int FAN = D1;
int gasDigital = D5;
int GREEN_LED = D4;
int YELLOW_LED = D7;
int RED_LED = D6;
int BUZZER = D8;
int gasAnalog = A0;


void setup() {
  pinMode(FAN, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT); 
  pinMode(gasDigital, INPUT);
  pinMode(gasAnalog, INPUT);
  
  Serial.begin(115200);
  
  Blynk.begin(auth, ssid, pass);
  dht.begin();

  timer.setInterval(1000, GAS_LEAK);
  
}



void loop() {
  Blynk.run();
  timer.run();
}

void GAS_LEAK(){
  int conc = analogRead(gasAnalog);
  int stat = digitalRead(gasDigital);

  if(stat==0){
    Serial.println("Sensor MQ2 tidak berfungsi!");
    return;
  }
   
  Blynk.virtualWrite(V2, conc);
  if(conc > 780){
    tone(BUZZER, 431);
    digitalWrite(RED_LED, HIGH);
  }else{
    tone(BUZZER, 0);
    digitalWrite(RED_LED, LOW);
  }
}


BLYNK_WRITE(V0){
  int state = param.asInt();

  if(state==1) digitalWrite(YELLOW_LED, HIGH);
  else digitalWrite(YELLOW_LED, LOW);
}

BLYNK_WRITE(V1){
  int TEMP = param.asInt();
  int cur_TEMP = dht.readTemperature();

  if(isnan(cur_TEMP)){
    Serial.println("Sensor DHT tidak berfungsi!");
    digitalWrite(GREEN_LED, LOW);
    return;
  }

  Blynk.virtualWrite(V4, cur_TEMP);
  digitalWrite(GREEN_LED, HIGH);

  if(cur_TEMP <= TEMP)digitalWrite(FAN, HIGH); 
  else digitalWrite(FAN, LOW);
}
