// include the library code:
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Setup temp probe
#define ONE_WIRE_BUS 3
#define RELAY_PIN 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define buttonDN 2

void setTemp();
void testButton();
String buttonStat;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // setup temp probe 
  sensors.begin();

  Serial.begin(115200);

  pinMode(buttonDN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  buttonStat = "UP";
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print(buttonStat);

  sensors.requestTemperatures();
  lcd.setCursor(0,1);
  lcd.print(String(sensors.getTempCByIndex(0)) + "  ");

  setTemp();
}

void setTemp() {
  if(digitalRead(buttonDN)==LOW) {
    buttonStat = "DOWN";
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    buttonStat = "UP  ";
    digitalWrite(RELAY_PIN, LOW);
  }
}
