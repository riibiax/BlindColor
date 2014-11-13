#include <tratto.h>


//--------------------------------------------------------------
void Tratto::setup() {
    position.set(ofGetWidth()/2, ofGetHeight()/2);
    prevPosition.set(ofGetWidth()/2, ofGetHeight()/2);
    coordX.push_back(ofGetWidth()/2);
    coordY.push_back(ofGetHeight()/2);
    
    radius.push_back(40);
    
    alpha = 120;
    color.set(ofRandom(255), ofRandom(255), ofRandom(255), alpha);
    dragged = 0;
    stop = false;
    control = 0;
}

//--------------------------------------------------------------
void Tratto::setup(int findRed, int findGreen, int findBlue, float departX, float departY) {
    
    position.set(departX, departY);
    prevPosition.set(departX, departY);
    coordX.push_back(departX);
    coordY.push_back(departY);
    
    float radiusAvg = (findRed + findGreen + findBlue) / 3;
    int radiusMap = (int)ofMap(radiusAvg, 0, 255, 40, 65);
    radius.push_back(radiusMap);
    
    alpha = 120;
    color = ofColor(findRed, findGreen, findBlue, alpha);
    dragged = 0;
    stop = false;
    control = 0;
}

//--------------------------------------------------------------
void Tratto::update() {
    
    if((position.y>prevPosition.y+7) or (position.y<prevPosition.y-7) or (position.x>prevPosition.x+3) or (position.x<prevPosition.x-3) or dragged==1){
        decrease();
        
        if (!stop){
            /* if (dragged and ((position.y>prevPosition.y+7) or (position.y<prevPosition.y-7) or (position.x>prevPosition.x+3) or (position.x<prevPosition.x-3))){
                 ofPoint subCoord;
                 subCoord.x= sqrt(double((prevPosition.x - position.x)*(prevPosition.x - position.x)));
                 subCoord.y= sqrt(double((prevPosition.y - position.y)*(prevPosition.y - position.y)));
                 decrease();
                 if (!stop){
                     if(prevPosition.x>position.x and prevPosition.y>position.y){
                         coordX.push_back(prevPosition.x-subCoord.x/2);
                         coordY.push_back(prevPosition.y-subCoord.y/2);
                     }
                     else if(prevPosition.x>position.x and prevPosition.y<position.y){
                         coordX.push_back(prevPosition.x-subCoord.x/2);
                         coordY.push_back(prevPosition.y+subCoord.y/2);
                     }
                     else if(prevPosition.x<position.x and prevPosition.y<position.y){
                         coordX.push_back(prevPosition.x+subCoord.x/2);
                         coordY.push_back(prevPosition.y-subCoord.y/2);
                     }
                     else {
                         coordX.push_back(prevPosition.x+subCoord.x/2);
                         coordY.push_back(prevPosition.y+subCoord.y/2);
                     }
                 } 
            }*/
            coordX.push_back(position.x);
            coordY.push_back(position.y);
            prevPosition.set(position.x, position.y);
        }
    }
}

//--------------------------------------------------------------
void Tratto::draw(){
    for(int i=0; i< coordX.size(); i++){
        ofSetColor(color);
        ofFill();
        ofRect(coordX[i] - radius[i]/2, coordY[i] - radius[i]/2, radius[i], radius[i]);        
    }
   /* for(int i=0; i< coordX.size(); i++){
        ofSetColor(color);
        ofFill();
        ofEllipse(coordX[i]+9, coordY[i]+7, radius[i]+3, radius[i]-2);        
    }
    for(int i=0; i< coordX.size(); i++){
        ofSetColor(color);
        ofFill();
        ofEllipse(coordX[i]+12, coordY[i]-7, radius[i]-3, radius[i]+3);        
    }
    for(int i=0; i< coordX.size(); i++){
        ofSetColor(color);
        ofFill();
        ofEllipse(coordX[i], coordY[i]-11, radius[i], radius[i]);        
    }
    for(int i=0; i< coordX.size(); i++){
        ofSetColor(color);
        ofFill();
        ofEllipse(coordX[i]-11, coordY[i]-3, radius[i]-4, radius[i]);
    }
    for(int i=0; i< coordX.size(); i++){
        ofSetColor(color);
        ofFill();
        ofEllipse(coordX[i]-8, coordY[i]+8, radius[i]-4, radius[i]+2);
    } */
}

//--------------------------------------------------------------
void Tratto::decrease(){
    if (radius.back()>9 and (radius.front()-control/130>9))
        radius.push_back(radius.front()-control/130);
    else
        stopDecrease();
}

//--------------------------------------------------------------
void Tratto::stopDecrease(){
    stop = true;
}

//--------------------------------------------------------------
bool Tratto::getDecrease(){
    return stop;
}

//--------------------------------------------------------------
float Tratto::getRadius(){
    return radius.back();
}

//--------------------------------------------------------------
void Tratto::setPosition(ofPoint a){
    a*=4;
    position.set(position.x+a.x,position.y-a.y);
}

//--------------------------------------------------------------
void Tratto::setPosition(float pointX, float pointY){
    position.set(pointX, pointY);
}

//--------------------------------------------------------------
void Tratto::setDragged(int variable){
    dragged = variable;
}

//--------------------------------------------------------------
int Tratto::getDragged(){
    return dragged;
}

//--------------------------------------------------------------
void Tratto::setControl(int time){
    control=time;
}