#pragma once

#include "ofMain.h"

class Tratto {
    
    public:
        void setup();
        void setup(int findRed, int findGreen, int findBlue, float departX, float departY);
        void update();
        void draw();
        void setPosition(ofPoint a);
        void setPosition(float pointX, float pointY);
        void setControl(int time);
        bool getDecrease();
        float getRadius();
        void setDragged(int variable);
        int getDragged();
    
    private :
        void decrease();
        void stopDecrease();
    
        ofPoint position, prevPosition;
        ofColor color;
        int control, alpha, dragged;
        bool stop;
        vector<float> coordX;
        vector<float> coordY;
        vector<float> radius;
};
