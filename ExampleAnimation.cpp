#include "BAI.h"

// Change ExampleAnimation to be a name for your animation. GlobeAnimation, for example
class ExampleAnimation: public Animation {
    private:
        // Set up your 'global' variables here, these keep state between function calls
        int x, y, mode;
    public:
        // Constructor must be used if you want to set initial values to your 'global's
        ExampleAnimation() {
            mode = 0;
        }

        // This frame is called when a new frame should be rendered.
        void beginFrame() {
            // Always call setupFrame in here,
            // arguments are width, height, colour_depth:
            // width         This is 
            // height        Should really always be 64, if not <= 64. If < 64 then the
            //               frame will have black borders added automatically.
            // colour_depth  specify how much colour depth you want, in bits:
            //               A value of 1 means each colour of every pixel can be either
            //                   on or off
            //               A value of 2 means each colour of every pixel can be any
            //                   number 0-3, where 0 is off, 3 is on and 1 and 2 are in
            //                   between.
            //               Numbers greater than 8 are not allowed.
            setupFrame(w, h, colourDepth);
            // Configure your variables to the new frame.
            // For this case, we have the current pixel being rendered stored as x, y
            // and the current mode (Basically inverts the output every other render)
            x = y = 0;
            mode = ! mode;
        }

        // This is called at least once per frame but can be multiple times. Your program
        // should expect to be rudely interrupted in the middle of any operation and recover.
        void renderFrame() {
            // In this example, we start at the current frame always. As we can expect to
            // be interrupted WE CANNOT ASSUME THAT WE ARE STARTING AT THE START OF THE FRAME
            for(; x < 64; x++) for(; y < 64; y ++) {
                // For the example, we make a lattice, where every other LED is on, and they
                // switch every frame. We simply set the frame data's value on the x, y. The
                // value to set it at is anywhere from 0 to (2^colour_depth)-1.
                currFrame->frameData[x][y] = (x + y + mode) % 2;
            }
        }
};
