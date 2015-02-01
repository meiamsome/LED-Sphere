#include <cstdlib>
#include <numeric>
#include "utils.h"

Frame::Frame(int width, int height, int colourDepth){
    this->width = width;
    this->height = height;
    this->colourDepth = colourDepth;

    frameData = (char**) malloc(width * sizeof(char*));
    for(int i = 0; i < width; i++) {
        frameData[i] = (char*) malloc(height * sizeof(char));
    }
}

Frame::~Frame(){
    if(frameData != NULL) {
        for(int i = 0; i < width; i++)
            free(frameData[i]);
        free(frameData);
    }
}

RPMCounter::RPMCounter(){
    keepSamples = 5;
    t.start();
}

int RPMCounter::getRpm(){
    return (1 / getMs()) * 1000 * 60;
}

int RPMCounter::getMs(){
    if(!ms){
        int sum = std::accumulate(samples.begin(), samples.end(), 0);
        ms = sum / samples.size();
    }
    return ms;
}

void RPMCounter::addSample(){
    t.stop();
    samples.push_front(t.read_ms());
    t.reset(); t.start();
    if(samples.size() > keepSamples){
        samples.pop_back();
    }
    ms = 0;
}
