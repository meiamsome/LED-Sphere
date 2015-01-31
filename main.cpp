#include "mbed.h"
#include "BAI.h"
#include "ExampleAnimation.cpp"
#include "LEDController.h"
#include "utils.h"

int main() {
    ExampleAnimation anim;
    RPMCounter rpmCounter;
    rpmCounter.keepSamples = 5; //this is default, but we can change it

    LEDController ctrl(&anim, rpmCounter);


    Frame f = ctrl.getDimensions();
    anim.setConfig(f.width, f.height, f.colour_depth);

    ctrl.streamFrames();
}
