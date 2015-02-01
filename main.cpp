#include "mbed.h"
#include "BAI.h"
#include "ExampleAnimation.cpp"
#include "LEDController.h"
#include "utils.h"

DigitalOut led1(LED1);

int main() {
    led1 = 1;
    ExampleAnimation anim;
    RPMCounter rpmCounter;
    rpmCounter.keepSamples = 5; //this is default, but we can change it

    LEDController ctrl(&anim, &rpmCounter);

    InterruptIn hullInterupt(p12);
    hullInterupt.rise(&rpmCounter, &RPMCounter::addSample);
    ctrl.streamFrames();
}
