#include "mbed.h"
#include "BAI.h"
#include "utils.h"

class LEDController {
    private:
        //LED controls
        BusOut leds;
        DigitalOut clock;
        DigitalOut outputEnable;
        DigitalIn hallSensor;

        //Get frames from here
        Animation anim;
        bool streaming;

        int rpm;
        
    public:
        LEDController;
}


