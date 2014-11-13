#include <sound.h>


//--------------------------------------------------------------
void Sound::setup(int findHue) {
    
    speed = 1.0f;
    pan= 0.0f;
    volume = 1.0f;
    
    if (findHue >= 0 and findHue< 15)
        note.loadSound("note/do.wav"); 
    else if (findHue >= 15 and findHue< 30)
        note.loadSound("note/doA.wav");
    else if (findHue >= 30 and findHue< 45)
        note.loadSound("note/re.wav");
    else if (findHue >= 45 and findHue< 60)
        note.loadSound("note/reA.wav");
    else if (findHue >= 60 and findHue< 75)
        note.loadSound("note/mi.wav");
    else if (findHue >= 75 and findHue< 90)
        note.loadSound("note/fa.wav"); 
    else if (findHue >= 90 and findHue< 105)
        note.loadSound("note/faA.wav");
    else if (findHue >= 105 and findHue< 120)
        note.loadSound("note/sol.wav");
    else if (findHue >= 120 and findHue< 150)
        note.loadSound("note/solA.wav");
    else if (findHue >= 150 and findHue< 180)
        note.loadSound("note/la.wav");    
    else if (findHue >= 180 and findHue< 210)
        note.loadSound("note/laA.wav");
    else if (findHue >= 210 and findHue< 240)
        note.loadSound("note/si.wav");
    else
        note.loadSound("note/dodie.wav");
}

//--------------------------------------------------------------
void Sound::update() {
    
    note.setVolume(volume);
}

//--------------------------------------------------------------
void Sound::read() {
    
    note.setSpeed(speed);
    note.setPan(pan);
    note.play();
}

//--------------------------------------------------------------
void Sound::scalingSound(int findBri, int findSat){
    
    speed = ofMap((float)findBri, 0, 255, 0.8, 1.8);
    
    pan = ofMap((float)findSat, 0, 255, -1, 1);
} 

//--------------------------------------------------------------
float Sound::getVolume(){
    return volume;
}

//--------------------------------------------------------------
void Sound::setVolume(float value){
    volume = value;
}