#include "app.h"


//--------------------------------------------------------------
void app::setup() {    

    ofEnableAlphaBlending();

    video.initGrabber(320, 240);
    w = video.getWidth();
    h = video.getHeight();

    rgb.allocate(w, h);
    hsb.allocate(w, h);
    hue.allocate(w, h);
    sat.allocate(w, h);
    bri.allocate(w, h);
    red.allocate(w, h);
    green.allocate(w, h);
    blue.allocate(w, h);
    
    ofSetVerticalSync(false);
    ofSetFrameRate(80);
    
    read = false;
    soundSlowDown = false;
    
    findRed = 0;
    findGreen = 0;
    findBlue = 0;
    
    time = 0;
    control = 0;
    timeTemp = 0;
    controlTemp=0;
    slowDownTime = 0;
    
    //Accelerometer setup
    ofxAccelerometer.setup();
    
    shake = 0;
    x_trig = 0; 
    x_startshake = 0;  
    
    y_trig = 0;  
    y_startshake = 0;  
    
    timeofgesture = 1500;  
    f_threshold = 1.0;  
    
    introVoice.loadSound("intro.wav");
    
    vibration.vibrate();
    introVoice.setVolume(0.5f);
    introVoice.play();    
}

//--------------------------------------------------------------
void app::update(){
    
    time = ofGetElapsedTimeMillis();
    
    if (timeTemp !=0){
        control = time -timeTemp;
        if(controlTemp!=0)
            slowDownTime = time - controlTemp;
    }
    
    video.update();
    
    if (video.isFrameNew()) {
        
        rgb.setFromPixels(video.getPixels(), w, h);
        
        rgb.convertToGrayscalePlanarImages(red, green, blue);
        
        hsb = rgb;
        
        hsb.convertRgbToHsv();
        
        hsb.convertToGrayscalePlanarImages(hue, sat, bri);
    }
    
    a = ofxAccelerometer.getForce();
    
    detectShake();
    
    if (shake>0){
        reset();
        shake = 0;
    }
    
    if (sound.size()>0 and sound.back().getVolume()>0.0f){
        if(soundSlowDown)
            sound.back().setVolume((float)ofMap(slowDownTime, 0, 4000, sound.back().getVolume(), 0));
        else {
            float radius = tratto.back().getRadius();
            sound.back().setVolume((float)ofMap(radius, 10, 65, 0, 1));
        }
        sound.back().update(); 
    }
    
    if(read){
        sound.back().scalingSound(findBri, findSat);
        readColor();
        read = false;
    }
    
    if (tratto.size()>0 and !tratto.back().getDecrease() and tratto.back().getDragged()!=2 and sound.size()>0){
        if (control>=350){
            if (tratto.back().getDragged()==0){
                tratto.back().setPosition(a);
                if(slowDownTime>4000)
                    sound.back().setVolume(0.0f);
            }
            tratto.back().setControl(control);
            tratto.back().update();
        }   
    }
    else if(tratto.size()>0 and tratto.back().getDragged()==2)
        return;
    else {
        timeTemp=0;
        controlTemp = 0;
    }
}


//--------------------------------------------------------------
void app::readColor(){
        
    sound.back().read();
} 

//--------------------------------------------------------------
void app::draw(){
        
    ofPushMatrix();
        
    //ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    
    rgb.draw(0,0);
    
    if(control>=400)
        drawTratto();
    
        
    if ((control < 400 and control > 0))
        drawBackgroundColor();
    else
        cleanScreen();
    
    ofPopMatrix();
            
    /*ofSetHexColor(0xffffff);
	char reportStr[1024];
	sprintf(reportStr, " pan %f\n speed %f\n sat %d\n bri %d\n hue %d\n volume %f\n", pan, speed, findSat, findBri, findHue, volume);
	ofDrawBitmapString(reportStr, 4, 380); */
}

//--------------------------------------------------------------
void app::drawTratto(){
    for(int i=0; i< tratto.size(); i++){
        tratto.at(i).draw();
    } 
} 

//--------------------------------------------------------------
void app::drawBackgroundColor(){
    ofSetColor(findRed, findGreen, findBlue);
    ofNoFill();
    ofRect(0, 0, 1, 1);
}

//--------------------------------------------------------------
void app::cleanScreen(){
    ofSetColor(255, 255, 255);
    ofNoFill();
    ofRect(0, 0, 1, 1); 
}

//--------------------------------------------------------------
void app::exit(){
    
}

//--------------------------------------------------------------
void app::reset(){
    read= false;
    soundSlowDown = false;

    timeTemp = 0;
    controlTemp = 0;
    
    vibration.vibrate();
        
    //clean the canvas
    if (tratto.size()>0)
        tratto.erase(tratto.begin(), tratto.end());
    
    if (sound.size()>0)
        sound.erase(sound.begin(), sound.end());
}

//--------------------------------------------------------------
void app::touchDown(ofTouchEventArgs & touch){
    if (touch.id == 1){
        
        read= false;
        soundSlowDown = false;
        
        timeTemp = 0;
        controlTemp = 0;
        
        vibration.vibrate();
        
        if (tratto.size()>0)
            tratto.erase(tratto.end());
        
        if (sound.size()>0)
            sound.erase(sound.end());
        
        ofxiPhoneAppDelegate * delegate = ofxiPhoneGetAppDelegate();  
        ofxiPhoneScreenGrab(delegate);
    }
    else if (touch.id == 0){
        
        int mx = int(touch.x) % w;
        int my = int(touch.y) % h;
        findRed = red.getPixels()[my*w+mx];
        findGreen = green.getPixels()[my*w+mx];
        findBlue = blue.getPixels()[my*w+mx];
        findHue = hue.getPixels()[my*w+mx];
        findBri = bri.getPixels()[my*w+mx];
        findSat = sat.getPixels()[my*w+mx];
        timeTemp = ofGetElapsedTimeMillis();
        
        soundSlowDown = false;
        read = true;
                
        if(introVoice.getIsPlaying())
            introVoice.stop();
        
        tratto.push_back(Tratto());
        tratto.back().setup(findRed, findGreen, findBlue, touch.x, touch.y);
        
        if (sound.size()>5){ 
            sound.erase(sound.begin(), sound.end()-1);
        }
        
        if (sound.size()>0){ 
            sound.back().setVolume(0.0f);
            sound.back().update();
        }
            
        sound.push_back(Sound());
        sound.back().setup(findHue);

    }

}

//--------------------------------------------------------------
void app::touchMoved(ofTouchEventArgs & touch){
    if (touch.id == 0){
        if(tratto.size()>0 and tratto.back().getDragged()==0)
            tratto.back().setDragged(1);
    
        if(tratto.size()>0 and !tratto.back().getDecrease())
            if (control>=350)
                tratto.back().setPosition(touch.x, touch.y);
    }
}

//--------------------------------------------------------------
void app::touchUp(ofTouchEventArgs & touch){
    if(tratto.size()>0 and tratto.back().getDragged()==1){
       tratto.back().setDragged(2);
       /* if (sound.size()>0 and sound.back().getVolume()>0.0f){
            sound.back().setVolume(0.0f);
            sound.back().update();
        }*/
    }
    
    soundSlowDown = true;
    controlTemp = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void app::detectShake(){       
    
    if(a.x < -f_threshold && x_trig == 0){  
        x_trig = 1;  
        x_startshake = ofGetElapsedTimeMillis();  
    }  
    if(a.x > f_threshold && x_trig == 1)
        x_trig=2;  
    
    if(a.x < -f_threshold && x_trig == 2)  
        x_trig=3;  
    
    if(a.x > f_threshold && x_trig == 3){  
        shake++;  
        x_trig=0;  
    }  
    if ((ofGetElapsedTimeMillis() - x_startshake) > timeofgesture) 
        x_trig=0;  
    
    // detect y shake  
    if(!shake){   
        
        if(a.y < -f_threshold && y_trig == 0){  
            y_trig = 1;  
            y_startshake = ofGetElapsedTimeMillis();  
        }  
        if(a.y > f_threshold && y_trig == 1) 
            y_trig=2;  
        
        if(a.y < -f_threshold && y_trig == 2)
            y_trig=3;  
        
        if(a.y > f_threshold && y_trig == 3){  
            shake++;  
            y_trig=0;  
        }  
        if ((ofGetElapsedTimeMillis() - y_startshake) > timeofgesture)
            y_trig=0;  
    } 
} 

//--------------------------------------------------------------
void app::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void app::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void app::lostFocus(){
    
}

//--------------------------------------------------------------
void app::gotFocus(){
    
}

//--------------------------------------------------------------
void app::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void app::deviceOrientationChanged(int newOrientation){
    
}
