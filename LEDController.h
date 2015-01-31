#include "mbed.h"
#include "BAI.h"
#include "utils.h"

class LEDController {
    private:
        //LED controls
        BusOut leds;
        DigitalOut clock;
        DigitalOut outputEnable;

        // Frame related stuff
        Animation anim;
        Frame *currFrame;
        bool streaming;

        // frame related stuff
        int linesDrawn;
        RPMCounter rpmCounter;
        
    public:
        LEDController;
        int w;
        int h;
        int colourDepth;
}


