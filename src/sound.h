#pragma once

#include "ofMain.h"

class Sound {
    
    public:
        void setup(int findHue);
        void update();
        void read();
        void scalingSound(int findBri, int findSat);
        void setVolume(float value);
        float getVolume();
    
    private :
        float speed, volume, pan;
        ofSoundPlayer note;

    
};
