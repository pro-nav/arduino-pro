# Fingerprint Attendance
Biometric Attendance system using Arduino and R307 fingerprint Scanner

![When Idle](/images/Idle.jpg)

The above System uses an Arduino Uno along with R307 Fingerprint Scanner Module to take Attendance. All the data is Stored in EEPROM of Arduino Uno and can be retrieved later. Similarly all the fingerprints are stored in the Module which can be updated without any harm to stored data.  

The Attendance is recorded and stored in Arduino...

![Attendance Recorded](/images/recorded.jpg)

It is quite Fool Proof and record only once per day (or as set previously)...

![Attendance is already Marked](/images/marked.jpg)

Check out all the Code in **Fingerprint_Validator** folder.

You will need to install the `Adafruit_Fingerprint` library first.
Click [here!](https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library) for Adafruit Fingerprint Sensor Library.

The `enroll` program allows to store fingerprints.

The maximum number of fingerprints is currently set to 10 but can be increased to 127 by changing these lines to required numbers
```c
bool limit[10];
```
```c
void setup()
{
  for (i = 0 ; i <= 10 ; i++)
  {
    limit[i] = true;
  }
  .
  .
  .
```

```c
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
      .
      .
      .
```

This project is Highly Efficient but still it should not be used for any Commercial Propose.  
