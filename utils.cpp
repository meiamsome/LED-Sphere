#include <cstdlib>
#include <numeric>
#include "utils.h"

void Frame::freeData(){
    if(frame_data != NULL) {
        for(int i = 0; i < width; i++)
            free(frame_data[i]);
        free(frame_data);
    }
}

RPMCounter::RPMCounter(){
    keepSamples = 5;
    t.start();
}

int RPMCounter::getRpm(){
    int sum = std::accumulate(samples.begin(), samples.end(), 0);
    return (double) (sum / samples.size()) * 1000*60;
}

int addSample(){
    t.stop();
    samples.push_front(t.read_ms());
    t.reset(); t.start();
    if(samples.size() > keepSamples){
        samples.pop_back();
    }
}
