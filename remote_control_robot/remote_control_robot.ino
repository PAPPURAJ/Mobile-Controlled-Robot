#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;
#define echoPin D5
#define trigPin D6


String command;
int out1 = D3, out2 = D4, out3 = D7, out4 = D8;
void handleRoot() {

}

float distance = 0, minDis = 300;
int rpm = 0;

String APSSID = "Power (7PTA²)";
String APPSK = "12345678";

String line1 = "Car started!", line2 = "RMP: ";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  digitalWrite(out1, 0);
  digitalWrite(out2, 0);
  digitalWrite(out3, 0);
  digitalWrite(out4, 0);

  lcd.init();
  lcd.backlight();
  lcd.home();
  myservo.attach(D0);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  EEPROM.begin(500);

  WiFi.softAP(APSSID, APPSK);

  IPAddress myIP = WiFi.softAPIP();
  server.on("/monitor", handleRoot);
  server.begin();
  server.onNotFound([]() {
    command = server.uri();
    server.send(200, "text/plain", command);
  });

  server.begin();
  dis("Hello world!", "Robot Start");

}

int count = 0, tRpm = 0;

void loop() {
  
    myservo.write(180);
calDis();
  if (line1 == "Turn Forward" && distance < minDis) {
    digitalWrite(out1, 0);
    digitalWrite(out2, 0);
    digitalWrite(out3, 0);
    digitalWrite(out4, 0);
    myservo.write(1);
    delay(1000);
    calDis();
    delay(1000);
    dis("Looking path!","Distance:"+String(distance));
      delay(2000);
     
    if (distance < minDis)
    {
      myservo.write(170);
      delay(2000);
      dis("Cannot be run!","Obstacle detect!");
      delay(5000);
      return;
    } else {
      digitalWrite(out1, 1);
      digitalWrite(out2, 0);
      digitalWrite(out3, 0);
      digitalWrite(out4, 0);
      delay(1000);

      digitalWrite(out1, 0);
      digitalWrite(out2, 0);
      digitalWrite(out3, 0);
      digitalWrite(out4, 0);
      
    }return;

  }


  if (analogRead(A0) > 130)rpm++;

  Serial.println(String(distance));
  delay(100);
  if (analogRead(A0) > 100)rpm++;
  delay(100);
  if (analogRead(A0) > 100)rpm++;
  delay(100);
  if (analogRead(A0) > 100)rpm++;
  delay(100);
  if (analogRead(A0) > 100)rpm++;








  server.handleClient();
  //Serial.println("          " + command);

  if (command.equals("/11")) { //Front
    digitalWrite(out1, 1);
    digitalWrite(out2, 0);
    digitalWrite(out3, 1);
    digitalWrite(out4, 0);
    Serial.println("Front");
    line1 = "Turn Forward";
  }

  else if (command.equals("/12")) { //Back
    digitalWrite(out1, 0);
    digitalWrite(out2, 1);
    digitalWrite(out3, 0);
    digitalWrite(out4, 1);
    Serial.println("Back");
    line1 = "Turn Backward";
  }

  else if (command.equals("/13")) { //Left
    digitalWrite(out1, 0);
    digitalWrite(out2, 0);
    digitalWrite(out3, 1);
    digitalWrite(out4, 0);
    Serial.println("Left");
    line1 = "Left Turn";
  }

  else if (command.equals("/14")) { //Right
    digitalWrite(out1, 1);
    digitalWrite(out2, 0);
    digitalWrite(out3, 0);
    digitalWrite(out4, 0);
    Serial.println("Right");
    line1 = "Right Turn";
  }

  else if (command.equals("/15")) { //All Stop
    digitalWrite(out1, 0);
    digitalWrite(out2, 0);
    digitalWrite(out3, 0);
    digitalWrite(out4, 0);
    Serial.println("All off");
    line1 = "Car off";
  }
  delay(100);
  if (analogRead(A0) > 100)tRpm++;
  delay(100);
  if (analogRead(A0) > 100)tRpm++;
  delay(100);
  if (analogRead(A0) > 100)tRpm++;
  delay(100);
  if (analogRead(A0) > 100)tRpm++;
  delay(100);
  if (analogRead(A0) > 100)tRpm++;
  delay(100);
  if (analogRead(A0) > 100)tRpm++;
  //Serial.print("VAL: "+String(rpm)+"  |  ");

  if (count++ >= 5) {
    tRpm = tRpm * 12;
    rpm = tRpm;
    tRpm = 0;
    count = 0;
  }


  line2 = "RPM:" + String(rpm) + " Dis:" + String(distance);

  dis(line1, line2);
  // delay(300);
  Serial.println("RPM: " + String(rpm));

}




void calDis(){
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  distance =  pulseIn(echoPin, HIGH) * (0.034 / 2) * 10;
}

void dis(String a, String b) {
  lcd.setCursor(0, 0);
  lcd.print(a + "                 ");
  lcd.setCursor(0, 1);
  lcd.print(b + "                 ");

}












String readStringFromEEPROM(int addrOffset)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
    Serial.println(data[i]);
  }
  data[newStrLen] = '\0';

  return String(data);
}



String subS(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
