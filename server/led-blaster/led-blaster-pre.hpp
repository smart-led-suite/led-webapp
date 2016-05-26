#ifndef _led_blaster_pre_hpp
#define _led_blaster_pre_hpp

//THE TWO READ/WRITE FUNCTIONS DO NOTHING RIGHT NOW
//theres a rewrite necessary but currently we dont use them anyway

#include <vector>
#include <cstdlib>
//#include <pigpio.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <pthread.h>
#include <stdint.h> //libary which includes uint8_t etc.
#include "led.hpp"

using namespace std;
//******************* VARIABLES ****************************
//extern std::vector<LED> leds;
struct ledInformationStruct {
  std::vector<LED> leds;
  int fadeTime;
  int pwmSteps;
};
struct configInformationStruct {
  uint16_t waitCounter;
  uint16_t mode;
  string serverPath;
};

//**************** FUNCTIONS ********************************
int initialize();
void ledBlasterTerminate(int dummy); //function which terminates the program safely. needs the dummy variable to be called by the sigHandler!
void ledBlasterTerminateFast(int dummy); //same but FASTER
#endif
