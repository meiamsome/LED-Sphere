#include "mbed.h"
#include "BAI.h"
#include "ExampleAnimation.cpp"
#include "LEDController.cpp"

int main() {
    Animation anim = (Animation) new ExampleAnimation();
    LEDController ctrl = new LEDController(anim)
    ctrl.streamFrames();
}
