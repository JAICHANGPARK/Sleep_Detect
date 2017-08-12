#include <LowPower.h>

int POWERPIN = 3;

void sleepForMinutes(int interval)
{
  int i = 0;
  int seconds = interval * 60;
  int iterations = seconds / 8;
  for (i = 0; i <= A5; i++) {
    pinMode (i, OUTPUT);    // changed as per below
    digitalWrite (i, LOW);  //     ditto
  }
  digitalWrite(POWERPIN, LOW);
  for (i = 0; i < iterations; i++) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}
