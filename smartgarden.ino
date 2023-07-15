#include <dht.h>
dht DHT;
#include <LiquidCrystal.h>
int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);
int temp , humidity, light, raindrop;
int dht = 8, buzz = 9, led = 10,in1=11,in2=12 ,en1 =13;
int ldr = A2;
int moist = A0;
int rain = A1;
int done = 1;
void water_on ()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(en1, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("Water is ON");
}
void water_off()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(en1, LOW);
  lcd.setCursor(0, 1);
  lcd.print("Water is OFF");
}
void Light()
{
  if (light < 55)
  {    
    digitalWrite(led, HIGH);
    lcd.setCursor(3, 1);
    lcd.print("It is Night");

  }
  else {
    digitalWrite(led, LOW);
    lcd.setCursor(3, 1);
    lcd.print("It is Day");
  }
}

void setup() {
  lcd.begin(16, 2);
  pinMode(led, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en1, OUTPUT);
}

void loop() {
  DHT.read11(dht);
  int moisture;
  int value = analogRead(moist);
  moisture = map(value, 0, 1023, 100, 0);


  //temperature
  temp = DHT.temperature;
  lcd.setCursor(0, 0);
  lcd.print("the temp:");
  lcd.print(temp);
  lcd.print(" C");

  //humidity
  humidity = DHT.humidity;
  lcd.setCursor(0, 1);
  lcd.print("humidity: ");
  lcd.print(humidity);
  delay(2000);
  lcd.clear();

  //ldr
  int value2 = analogRead(ldr);
  light = map(value2, 0, 1023, 100, 0) - 10;
  lcd.setCursor(0, 0);
  lcd.print("Brightness:");
  lcd.print(light);
  lcd.print("%");
  Light();
  delay(2000);
  lcd.clear();

  //moisture
  value = analogRead(moist);
  moisture = map(value, 0, 1023, 100, 0);
  lcd.setCursor(0, 0);
  lcd.print("the moisture:");
  lcd.print(moisture);
  lcd.print("%");
  if (temp <= 20)
  {
    if (moisture < 10 && done==1) {
      water_on();
    }
    else if ( light >= 50 && light <= 60 && done==1)
    {
      if ( moisture >= 18 && moisture <= 20) {
        water_on();
      }
      else {
        water_off();
      }
    }
    else {
      water_off();
    }
  }
  else {
    if (moisture < 10 && done==1) {
      water_on();
    }
    else if (light >= 50 && light <= 60 && done==1)
    {
      if (moisture >= 18 && moisture <= 20) {
        water_on();
      }
      else {
        water_off();
      }
    }
    else if (85 <= light && light <= 90 && done==1)
    {
      if (18 <= moisture && moisture <= 20) {
        water_on();
      }
      else {
        water_off();
      }
    }
    else {
      water_off();
    }
  }
  delay(2000);
  lcd.clear();

  //rain
  int value3 = analogRead(rain);
  raindrop = map(value3, 0, 1023, 100, 0);
  lcd.setCursor(0, 0);
  lcd.print("the rain: ");
  lcd.print(raindrop);
  lcd.print("%");
  if (raindrop > 30)
  {
    if (done == 1) {
      tone(buzz, 1000, 500);
      done = 0;
    }
  }
  else
  {
    noTone(buzz);
    done = 1;
  }
  delay(2000);
}
