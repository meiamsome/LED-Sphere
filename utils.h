#include <list>
#include "mbed.h"

class Frame{
    public: 
        int width, height, colour_depth;
        char **frame_data;

        void freeData();
}

class RPMCounter{
    private:
        std::List<int> samples;
        Timer t;
        
    public:
        RPMCounter();
        int keepSamples;
        int getRpm();
        void addSample();
}
