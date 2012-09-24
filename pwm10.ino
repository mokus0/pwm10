#include <Arduino.h>
#include <inttypes.h>

#include "pwm.h"

struct pwm_mode pwm10 = {2, 3, 3};

static const struct pwm_chan d2  = {OCR3B, 1, 2,  pwm10, TCCR3A, TCCR3B};
static const struct pwm_chan d3  = {OCR3C, 2, 3,  pwm10, TCCR3A, TCCR3B};
static const struct pwm_chan d5  = {OCR3A, 0, 5,  pwm10, TCCR3A, TCCR3B};
static const struct pwm_chan d6  = {OCR4A, 0, 6,  pwm10, TCCR4A, TCCR4B};
static const struct pwm_chan d7  = {OCR4B, 1, 7,  pwm10, TCCR4A, TCCR4B};
static const struct pwm_chan d8  = {OCR4C, 2, 8,  pwm10, TCCR4A, TCCR4B};
static const struct pwm_chan d11 = {OCR1A, 0, 11, pwm10, TCCR1A, TCCR1B};
static const struct pwm_chan d12 = {OCR1B, 1, 12, pwm10, TCCR1A, TCCR1B};
static const struct pwm_chan d13 = {OCR1C, 2, 13, pwm10, TCCR1A, TCCR1B};
static const struct pwm_chan d44 = {OCR5C, 2, 44, pwm10, TCCR5A, TCCR5B};
static const struct pwm_chan d45 = {OCR5B, 1, 45, pwm10, TCCR5A, TCCR5B};
static const struct pwm_chan d46 = {OCR5A, 0, 46, pwm10, TCCR5A, TCCR5B};

static const struct pwm_chan *allPWMs[] = 
  { &d2, &d3, &d5, &d6, &d7, &d8, &d11, &d12, &d13, &d44, &d45, &d46};

static const int numPWMs = sizeof allPWMs / sizeof (struct pwm_chan *);

void setAll(int level) {
  for (int i = 0; i < numPWMs; i++) {
    setPWM(*allPWMs[i], level);
  }
}

void setup() {
  for (int i = 0; i < numPWMs; i++) {
    setupPWM(*allPWMs[i]);
  }
}

void loop() {
  // ramp up once
  for (int i = 0; i < 0x0400; i++) {
    delay(5);
    setAll(i);
  }

  // blink a few times
  for (int i = 0; i < 10; i++) {
    delay(50);
    setAll(0x0100);
    delay(50);
    setAll(0x03ff);
  }
}
