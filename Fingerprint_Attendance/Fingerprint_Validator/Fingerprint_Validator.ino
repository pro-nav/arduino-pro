#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <Adafruit_Fingerprint.h>

int led = 13;
int val = 0;
int validID = 0;
int i;

bool limit[10];

const int rs = 12, en = 11, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup()
{
  for (i = 0 ; i <= 10 ; i++)
  {
    limit[i] = true;
  }
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println("\n\nDigital Attendence");

  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) {
      delay(1);
    }
  }
  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
  lcd.print("Place Finger...");
}

void loop()
{
  validID = getFingerprintIDez();

  delay(50);

  for (i = 0; i <= 10; i++)
  {
    if (validID == i)
    {
      if (limit[i] == true)
      {
        val = EEPROM.read(validID);
        val++;
        EEPROM.update(validID, val);
        Serial.print("Student ID #"); Serial.print(validID); Serial.print("\n");
        Serial.print("Your Attendance is "); Serial.print(val); Serial.print("\n\n");
        lcd.clear();
        lcd.print("Student ID #"); lcd.setCursor(12, 0); lcd.print(validID);
        lcd.setCursor(0, 1); lcd.print("Attendance is "); lcd.setCursor(14, 1); lcd.print(val);
        delay(3000);
        lcd.clear();
        val = 0;
        limit[i] = false;
      }
      else
      {
        Serial.print("Student ID #"); Serial.print(validID); Serial.print("\n");
        Serial.print("Your Attendance is Already Marked"); Serial.print("\n\n");
        lcd.clear();
        lcd.print("Student ID #"); lcd.setCursor(12, 0); lcd.print(validID);
        lcd.setCursor(0, 1); lcd.print("Already marked");
        delay(3000);
        lcd.clear();
      }
    }
  }
  lcd.clear();
  lcd.print("Place Finger...");
  delay(50);
}
