#pragma once

// Define Input Connections
#define CH1 1
#define CH2 2
#define CH3 3
#define CH4 10

#define RC_MIN_LIMIT -100
#define RC_MAX_LIMIT 100
#define RC_DEFAULT_VAL 0

struct RcChannelValues {
    int ch1;
    int ch2;
    int ch3;
    int ch4;
};

// Function to initialize the pins
void initializeControllerPins();

// Function to read a channel value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue);

RcChannelValues readChannels();