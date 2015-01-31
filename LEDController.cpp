#include "LEDController.h"

LEDController::LEDController(Animation anim)
{
    this.leds = BusOut(p17, p18, p19, p20, p21, p22, p23, p24);
    this.clock = DigitalOut(p14);
    this.outputEnable = DigitalOut(p13);
    this.anim = anim;
    w = 64;
    h = 64;
    colourDepth = 1;
    linesDrawn = 0;
}

Frame LEDController::getDimensions(){
    Frame f;
    f.width = w;
    f.height = h;
    f.colourDepth = colourDepth;
    return f;
}

void LEDController::streamFrames(){
    Frame *f;
    Ticker lineTicker;
    Timer t;

    t.start();
    streaming = true;
    while(streaming){
        int drawLinePeriod = rpmCounter.getMs() / w * 1000;
        lineTicker.attach_us(this, & LEDController::drawLine, drawLinePeriod)

        anim.beginFrame();
        anim.renderFrame();
        currFrame = anim.getFramePointer();

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
void LEDController::interruptVideo(){
    streaming = false;
}

void LEDController:drawLine(){
    int val, y;
    int x = linesDrawn;
    int cycle = linesDrawn/colourDepth;
    char **pic = currFrame->frame_data;

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
            clock = 1; 
            outputEnable = 1;
            wait_us(1); //wait a microsec to make sure it registers
            clock = 0; //clock up down
            outputEnable = 0;
        }
    }
    linesDrawn = (linesDrawn + 1) % w*colourDepth;
}
