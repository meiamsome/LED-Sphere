#include "BAI.h"

// Constructor
Animation::Animation() {
    lastFrame.frame_data = NULL;
    currFrame.frame_data = NULL;
}
// Deconstructor
Animation::~Animation() {
    eraseFrame();
}

// Set up a new frame
void Animation::setupFrame(int width, int height, int colour_depth) {
    if(width < 1 || height < 1 ||
        colour_depth < 1 || colour_depth > 8) {
        width = width;
        // we might want to throw this, but idk
        //throw new FrameConfigurationException();
    }

    currFrame.frame_data = (char**) malloc(width * sizeof(char*));
    for(int i = 0; i < width; i++) {
        currFrame.frame_data[i] = (char*) malloc(height * sizeof(char));
    }
    currFrame.width = width;
    currFrame.height = height;
    currFrame.colour_depth = colour_depth;
}

// Return the current Frame
Frame Animation::getFrame() {
    frameRetrieved = true;
    return lastFrame;
}

// Return the current Frame as a pointer for whatever reason.
Frame *Animation::getFramePointer() {
    frameRetrieved = true;
    return &lastFrame;
}

void Animation::switchFrames(){
    // if whoever needs the frame has not retrieved, we free it here
    // to prevent memory leaking. if they have retrieved the frame,
    // we assume it is being used and thus freed by somebody else
    if(! frameRetrieved){
        lastFrame.freeData();
    }
    frameRetrieved = false;   
    lastFrame = &currFrame;
}
