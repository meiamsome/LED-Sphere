#include <list>
#include "mbed.h"

#ifndef UTILS_H
#define UTILS_H

class Frame{
    public: 
        int width, height, colour_depth;
        char **frame_data;

        void freeData();
};

class RPMCounter{
    private:
        std::list<int> samples;
        Timer t;
        
    public:
        int keepSamples;

        RPMCounter();
        int getRpm();
        void addSample();
};

#endif
