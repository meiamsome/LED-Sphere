#ifndef BAI
#define BAI

#include <cstdlib>
#include <exception>


typedef struct {
    int width, height, colour_depth;
    char **frame_data;
} Frame;

class Animation {
    public:
        Animation();
        ~Animation();
        virtual void beginFrame() = 0;
        virtual Frame animateFrame() = 0;
    protected:
        Frame myFrame; 
        void eraseFrame();
        void setupFrame(int width, int height, int colour_depth);
        Frame getFrame();
        Frame *getFramePointer();
};

/*class FrameConfigurationException: public exception {

};*/

#endif