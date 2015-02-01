#include <list>
#include "mbed.h"

#ifndef UTILS_H
#define UTILS_H

class Frame{
    public: 
        int width, height, colourDepth;
        char **frameData;

        Frame(int, int, int);
        ~Frame();
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
