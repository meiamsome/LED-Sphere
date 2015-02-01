#ifndef BAI_H
#define BAI_H

#include <cstdlib>
#include <exception>
#include "utils.h"

class Animation {
    public:
        bool change;
        int w, h, colourDepth, fps;

        Animation();
        ~Animation();
        Frame *getFrame();
        void switchFrames();

        virtual void beginFrame() = 0;
        virtual void renderFrame() = 0;

    protected:
        Frame *currFrame; 
        Frame *lastFrame;
        bool frameRetrieved;

        void setupFrame(int, int, int);
};

/*class FrameConfigurationException: public exception {

};*/

#endif
