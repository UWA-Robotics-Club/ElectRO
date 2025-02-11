#include "rc.h"
#include <Arduino.h>

void initializeControllerPins() {
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
}

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

RcChannelValues readChannels(){
  RcChannelValues channels;
  channels.ch1 = readChannel(CH1, RC_MIN_LIMIT, RC_MAX_LIMIT, RC_DEFAULT_VAL);
  channels.ch2 = readChannel(CH2, RC_MIN_LIMIT, RC_MAX_LIMIT, RC_DEFAULT_VAL);
  channels.ch3 = readChannel(CH3, RC_MIN_LIMIT, RC_MAX_LIMIT, RC_DEFAULT_VAL);
  channels.ch4 = readChannel(CH4, RC_MIN_LIMIT, RC_MAX_LIMIT, RC_DEFAULT_VAL);

  return channels;
}