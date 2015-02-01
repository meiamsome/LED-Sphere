#include "mbed.h"
#include "BAI.h"
#include "utils.h"

class LEDController {
    private:
        //LED controls
        BusOut *leds;
        DigitalOut *clock;
        DigitalOut *outputEnable;

        // Frame related stuff
        Animation *anim;
        Frame *currFrame;
        bool streaming;

        // frame related stuff
        int linesDrawn;
        RPMCounter *rpmCounter;
        
        void drawLine();
        void getFrame();
    public:
        int w;
        int h;
        int colourDepth;

        LEDController(Animation *, RPMCounter *);
        ~LEDController();
        void streamFrames();
        void interruptStream();
        Frame getDimensions();
};

