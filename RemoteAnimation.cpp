#include "BAI.h"

class RemoteAnimation: public Animation {
    private:
        Serial *remote;
        RPMCounter *r;
        int frameCount;

        void sendByte(char byte){
            while(! remote->writeable()) ;
            remote->putc(byte);
        }

        char getByte(){
            while(! remote->readable()) ;
            return remote->getc();
        }

        void sendInt(int n){
            for(char i = 0; i < 4; i++){
                while(! remote->readable()) ;
                remote->putc(n >> i*8);
            }
        }

        int getInt(){
            int n = 0;
            for(char i = 0; i < 4; i++){
                while(! remote->readable()) ;
                n |= ((int)remote->getc()) << i*8;
            }
            return n;
        }

        void getConfig(){
            w = getByte();
            h = getByte();
            colourDepth = getByte();
            fps = getByte();
            change = true;
        }

    public:
        RemoteAnimation(RPMCounter *r) {
            this->r = r;
             
            remote = new Serial(p9, p10);
            remote->baud(38400);
            // 8 bits per data, parity even, 1 stop bit
            remote->format(8, SerialBase::Even, 1);
        }

        void beginFrame() {
            // send rpm info 5 times a second
            if(frameCount % (fps/5)){
                sendInt(r->getRpm());
            }

            // there is change, we need to change the config
            if(getByte()){
                getConfig();
            }
            setupFrame(w, h, colourDepth);
        }

        void renderFrame() {
            for(int y = 0; y < currFrame->height; y++) 
                for(int x = 0; x < currFrame->width; x ++) {
                    currFrame->frameData[y][x] = getByte();
            }
            frameCount++;
        }
};
