#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);//rx,tx

#include <LiquidCrystal.h>
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int redLed = 13;
int greenLed = 12;
int buzzer = 11;
int smokeA0 = A5;

// Your threshold value
int sensorThres = 400;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  mySerial.begin(9600);
}
void loop() 
{
  int analogSensor = analogRead(smokeA0);
  mySerial.print("Alcohollevel: ");
  mySerial.println(analogSensor);

  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
   
    mySerial.println("Person is Drunk");
    mySerial.println("");
    lcd.begin(16, 2);
    lcd.print("Alcohollevel:");
    lcd.setCursor(13, 0); // top right
    lcd.println(analogSensor);
    lcd.setCursor(0, 2);
    lcd.print("Person is Drunk");
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
    SendMessage1();
  }
  else
  { 
    mySerial.println("Person not Drunk");
     mySerial.println("");
    lcd.begin(16, 2);
    lcd.print("Alcohollevel:");
    lcd.setCursor(13, 0); // top right
    lcd.println(analogSensor);
    lcd.setCursor(0, 2);
    lcd.print("Person not Drunk");
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
    SendMessage2();
    delay(1000);
  }
  delay(1000);
  lcd.clear();
}

void SendMessage2()
{
  mySerial.begin(9600);
  delay(1000);
  Serial.println("AT");
  delay(1000);
  Serial.println("OK");
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("OK");
  Serial.println("AT+CMGS=\"+xxxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println("I am SMS from drink and drive departemnt.");
  Serial.println("Person is not drunked ");// The SMS text you want to send
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(5000);
  delay(5000);
  //delay(5000);
}
void SendMessage1()
{
  mySerial.begin(9600);
  delay(1000);
  Serial.println("AT");
  delay(1000);
  Serial.println("OK");
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("OK");
  Serial.println("AT+CMGS=\"+xxxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  Serial.println("I am SMS from drink and drive departemnt.");
  Serial.println("Person is drunked ");// The SMS text you want to send
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
  delay(5000);
  delay(5000);
 // delay(5000);
}
