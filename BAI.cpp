#include "BAI.h"

// Constructor
Animation::Animation() {
    change = false;
    w = h = 64;
    colourDepth = 1;
    fps = 30;
    lastFrame = new Frame(64, 64, 1);
    currFrame = new Frame(64, 64, 1);
}
// Deconstructor
Animation::~Animation() {
    delete lastFrame;
    delete currFrame;
}

// Set up a new frame
void Animation::setupFrame(int width, int height, int colourDepth) {
    if(width < 1 || height < 1 ||
        colourDepth < 1 || colourDepth > 8) {
        width = width;
        // we might want to throw this, but idk
        //throw new FrameConfigurationException();
    }
    currFrame = new Frame(width, height, colourDepth);
}

// Return the current Frame
Frame *Animation::getFrame() {
    frameRetrieved = true;
    return lastFrame;
}

void Animation::switchFrames(){
    // if whoever needs the frame has not retrieved, we free it here
    // to prevent memory leaking. if they have retrieved the frame,
    // we assume it is being used and thus deleted by somebody else
    if(! frameRetrieved){
        delete lastFrame;
    }
    frameRetrieved = false;   

    lastFrame = currFrame;
}
