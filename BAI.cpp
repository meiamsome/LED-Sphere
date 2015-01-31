#include "BAI.h"

// Constructor
Animation::Animation() {
    lastFrame->frameData = NULL;
    currFrame->frameData = NULL;
}
// Deconstructor
Animation::~Animation() {
    lastFrame->freeData();
    currFrame->freeData();
}

// Set up a new frame
void Animation::setupFrame(int width, int height, int colourDepth) {
    if(width < 1 || height < 1 ||
        colourDepth < 1 || colourDepth > 8) {
        width = width;
        // we might want to throw this, but idk
        //throw new FrameConfigurationException();
    }

    currFrame->frameData = (char**) malloc(width * sizeof(char*));
    for(int i = 0; i < width; i++) {
        currFrame->frameData[i] = (char*) malloc(height * sizeof(char));
    }
    currFrame->width = width;
    currFrame->height = height;
    currFrame->colourDepth = colourDepth;
}

// Return the current Frame
Frame *Animation::getFrame() {
    frameRetrieved = true;
    return lastFrame;
}

void Animation::switchFrames(){
    // if whoever needs the frame has not retrieved, we free it here
    // to prevent memory leaking. if they have retrieved the frame,
    // we assume it is being used and thus freed by somebody else
    if(! frameRetrieved){
        lastFrame->freeData();
    }
    frameRetrieved = false;   
    lastFrame = currFrame;
}
