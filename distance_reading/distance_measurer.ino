#include <LiquidCrystal.h>
#include <NewPing.h>
int V0=6,RS=8,E=9,D4=5,D5=4,D6=3,D7=2;
int trig=12,echo=11,MAX=400,distance;
LiquidCrystal lcd(RS,E,D4,D5,D6,D7);
NewPing sonar(trig,echo,MAX);
void setup() {
  lcd.begin(16,2);
  analogWrite(V0,103);
  Serial.begin(9600);
}

void loop() {
  distance=sonar.ping_cm();
  Serial.println(distance);
  lcd.setCursor(0,0);
  lcd.print("The object is");
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.setCursor(3,1);
  lcd.print("cm away");
  delay(10000);
}
