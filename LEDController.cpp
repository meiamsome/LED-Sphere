#include "LEDController.h"

LEDController::LEDController(Animation anim)
{
    this.leds = BusOut(p17, p18, p19, p20, p21, p22, p23, p24);
    this.clock = DigitalOut(p14);
    this.outputEnable = DigitalOut(p13);
    this.hallSensor = DigitalOut(p12);
    this.anim = anim;
}

void LEDController::setRpm(int rpm){
    this.rpm = rpm;
}

Frame LEDController::getDimensions(){
    Frame f;
    f.width = 64;
    f.height = 64;
    f.colourDepth = 1;
    return f;
}

void LEDController::streamVideo(){
    streaming = true;
    while(streaming){
    // get video from anim, put on leds
    }
}

// this might be useful
void LEDController::interruptVideo(){
    streaming = false;
}
