#include "BAI.h"

// Constructor
Animation::Animation() {
    myFrame.frame_data = NULL;
}
// Deconstructor
Animation::~Animation() {
    eraseFrame();
}

// Erase the current frame
void Animation::eraseFrame() {
    if(myFrame.frame_data != NULL) {
        for(int i = 0; i < myFrame.width; i++)
            free(myFrame.frame_data[i]);
        free(myFrame.frame_data);
    }
}

// Set up a new frame
void Animation::setupFrame(int width, int height, int colour_depth) {
    if(myFrame.frame_data != NULL &&
        myFrame.width == width &&
        myFrame.height == height &&
        myFrame.colour_depth == colour_depth) return;
    if(myFrame.width < 1 || myFrame.height < 1 ||
        myFrame.colour_depth < 1 || myFrame.colour_depth > 8) {
        width = width;//throw new FrameConfigurationException();
    }
    eraseFrame();
    myFrame.frame_data = (char**) malloc(width * sizeof(char*));
    for(int i = 0; i < width; i++) {
        myFrame.frame_data[i] = (char*) malloc(height * sizeof(char));
    }
    myFrame.width = width;
    myFrame.height = height;
    myFrame.colour_depth = colour_depth;
}

// Return the current Frame
Frame Animation::getFrame() {
    return myFrame;
}

// Return the current Frame as a pointer for whatever reason.
Frame *Animation::getFramePointer() {
    return &myFrame;
}