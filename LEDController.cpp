#include "LEDController.h"

LEDController::LEDController(Animation *anim, RPMCounter *r)
{
    this->anim = anim;
    this->rpmCounter = r;

    this->leds = new BusOut(p17, p18, p19, p20, p21, p22, p23, p24);
//    this->leds = new BusOut(LED1, LED2, LED3, LED4, LED1, LED2, LED3, LED4);
    this->clock = new DigitalOut(p14);
    this->outputEnable = new DigitalOut(p13);
    w = 64;
    h = 64;
    colourDepth = 1;
    linesDrawn = 0;
    currFrame = NULL;
}

LEDController::~LEDController(){
    free(leds);
    free(clock);
    free(outputEnable);
}

Frame LEDController::getDimensions(){
    Frame f(w, h, colourDepth);
    return f;
}

void LEDController::streamFrames(){
    Ticker lineTicker;
    Timer t;

    //make sure we have a frame to draw
    getFrame();

    t.start();
    streaming = true;
    while(streaming){
        int drawLinePeriod = rpmCounter->getMs() / w * 1000;
        lineTicker.attach_us(this, & LEDController::drawLine, 1000000/60);

        getFrame();

        if(currFrame == NULL){
            streaming = false;
        }

        // busy wait to have this going at 30fps
        while((t.read_ms() < 1000 / 30 / colourDepth) && streaming) {;};
        t.reset();
        lineTicker.detach();
    }
}

// this might be useful
void LEDController::interruptStream(){
    streaming = false;
}

void LEDController::drawLine(){
    int val, y;
    int x = linesDrawn;
    int cycle = linesDrawn/colourDepth;
    char **pic = currFrame->frameData;

    for(int i = 0; i < 3; i++){ //red, green, blue
        for(int j = 0; j < 8; j++){ //8 rows
            val = 0;
            for(int k = 0; k < 8; k++){ // 8 LEDs
                y = j*k;
                val |= (
                        ((pic[y][x] &   //take (x,y) pixel
                        2 << i*2)       //2 bits per colour
                        >> i*2)         //shift them back
                        > cycle         //if > than curr cycle - flash it on
                       ) << k;
            }
            *leds = ~val; //set outputs
            *clock = 1; //clock it
            *outputEnable = 1; //write outputs
            wait_us(1); //wait a microsec to make sure it registers
            *outputEnable = 0; //stop writing
            *clock = 0; //clock down
        }
    }
    linesDrawn = (linesDrawn + 1) % w*colourDepth;
}

void LEDController::getFrame(){
    anim->beginFrame();
    anim->renderFrame();
    anim->switchFrames(); //have to switch the frame ourselves
    Frame *temp = currFrame; //temporary store so we don't get NULL derefs
    currFrame = anim->getFrame(); //this might get interrupted
    delete temp; //delete the old frame. don't leak that memory
}
