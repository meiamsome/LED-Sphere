#ifndef BAI_H
#define BAI_H

#include <cstdlib>
#include <exception>
#include "utils.h"

class Animation {
    public:
        Animation();
        ~Animation();
        virtual void beginFrame() = 0;
        virtual void renderFrame() = 0;

        Frame *getFrame();
        void switchFrames();
    protected:
        Frame *currFrame; 
        Frame *lastFrame;
        bool frameRetrieved;

        void setupFrame(int width, int height, int colourDepth);
};

/*class FrameConfigurationException: public exception {

};*/

#endif
