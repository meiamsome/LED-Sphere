#include "mbed.h"
#include "BAI.h"
#include "ExampleAnimation.cpp"
#include "LEDController.cpp"

BusOut myBus(LED1, LED2, LED3, LED4);
DigitalIn enable(p19);
Animation *myAnimation = NULL;

int main() {
    ExampleAnimation anim;
    myAnimation = &anim;
    myBus = 1;
    while(1) {
        myBus = 2;
        myAnimation -> beginFrame();
        myBus = 3;
        Frame the_frame = myAnimation -> animateFrame();
        myBus = 4;
        int fval = 0;
        for(int i = 0; i < 4; i++) {
            fval <<= 1;
            if(!the_frame.frame_data[0][i]) fval += 1;
        }
        myBus = fval;
        wait(0.1);
    }
}
