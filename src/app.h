#pragma once


#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"


//ON IPHONE NOTE INCLUDE THIS BEFORE ANYTHING ELSE
#include "ofxOpenCv.h"
#include "tratto.h"
#include "sound.h"



class app : public ofxiPhoneApp{
	
    public:
    
        void setup();
        void update();
        void draw();
        void exit();
    
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);
	
        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
        
        void reset();
        void detectShake();
        void drawTratto();
        void drawBackgroundColor();

        void readColor();
        void cleanScreen();
    
        ofVideoGrabber video;
    
        ofxCvColorImage rgb, hsb;
        ofxCvGrayscaleImage hue, sat, bri, red, green, blue;    
    
        int w, h;
        int findRed, findGreen, findBlue, findHue, findSat, findBri;
        int time, timeTemp, control, slowDownTime, controlTemp, timeofgesture;
        int shake, x_trig, x_startshake, y_trig, y_startshake;  
        
        bool read, soundSlowDown;
        float f_threshold;
    
        ofPoint a;
        ofxOpenALSoundPlayer vibration;
        ofSoundPlayer introVoice;
    
        vector<Tratto> tratto;
        vector<Sound> sound;
    };
