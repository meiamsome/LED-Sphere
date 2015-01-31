#include <list>
#include "mbed.h"

#ifndef UTILS_H
#define UTILS_H

class Frame{
    public: 
        int width, height, colourDepth;
        char **frameData;

        void freeData();
};

class RPMCounter{
    private:
        std::list<int> samples;
        Timer t;
        
    public:
        unsigned int keepSamples;

        RPMCounter();
        int getRpm();
        int getMs();
        void addSample();
};

#endif
