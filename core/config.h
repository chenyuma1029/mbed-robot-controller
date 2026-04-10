#ifndef CONFIG_H
#define CONFIG_H

#ifdef __ARM_FP
#undef __ARM_FP
#endif

#include "mbed.h"
#include "../hardware_libs/MotionControl.h"
#include "../hardware_libs/StdMotor.h"
#include "../hardware_libs/Ultrasonic.hpp"

#include <cstring>
#include <cstdio>
#include <cstdint>


const int WIDTH  = 320;
const int HEIGHT = 240;
const int A      = WIDTH * HEIGHT;

const int period     = 50;  // unit: us
const int speedGrade = 7;


const uint32_t BT_READABLE  = (1 << 0);
const uint32_t RPI_READABLE = (1 << 1);


struct CmdInfo {
    char text[32];
    int  len;
    CmdInfo() { memset(text, 0, sizeof(text)); len = 0; }
};


extern StdMotor BR, BL, FR, FL;
extern MotionControl carMotion;

extern BufferedSerial pc;
extern BufferedSerial bt;
extern BufferedSerial rpi;
extern Ultrasonic sonar;

extern bool sonicSwitch;
extern EventFlags flag;
extern Mail<CmdInfo, 16> cmdMail;

#endif 
