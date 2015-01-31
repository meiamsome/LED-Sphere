#ifndef BAI
#define BAI

#include <cstdlib>
#include <exception>
#include "utils.h"

class Animation {
    public:
        Animation();
        ~Animation();
        virtual void beginFrame() = 0;
        virtual void renderFrame() = 0;

        Frame getFrame();
        Frame *getFramePointer();
    protected:
        Frame currFrame; 
        Frame lastFrame;
        bool frameRetrieved;

        void setupFrame(int width, int height, int colour_depth);
        void switchFrames();
};

/*class FrameConfigurationException: public exception {

};*/

#endif
