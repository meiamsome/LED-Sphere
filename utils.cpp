#include <cstdlib>
#include <numeric>
#include "utils.h"

void Frame::freeData(){
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
    int sum = std::accumulate(samples.begin(), samples.end(), 0);
    return (double) (1 / (sum / samples.size())) * 1000 * 60;
}

int RPMCounter::getMs(){
    int sum = std::accumulate(samples.begin(), samples.end(), 0);
    return (double) (sum / samples.size());
}

void RPMCounter::addSample(){
    t.stop();
    samples.push_front(t.read_ms());
    t.reset(); t.start();
    if(samples.size() > keepSamples){
        samples.pop_back();
    }
}
