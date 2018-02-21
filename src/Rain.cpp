#include "Rain.h"

Rain::Rain(){
};

void Rain::setup(float _x, float _y, int _dim){
    x = _x;
    y = _y;
    dim = _dim;
    
    speedX = ofRandom(-1, 1);
    speedY = ofRandom(1, 2);
    str =  generateString();
    
    color.set(ofRandom(255), ofRandom(255), ofRandom(255));
}

void Rain::update(){
    
    if(x < 0 ){
        x = 0;
        speedX *= -1;
    } else if(x > ofGetWidth()){
        x = ofGetWidth();
        speedX *= 1;
        
    }
    
    if(y < 0 ){
        y = 0;
        speedY *= -1;
    } else if(y > ofGetHeight()){
        y = 0;
        speedY *= 1;
    }
    
    
    x+=speedX;
    y+=speedY;
}

char Rain::generateString(){
    char string[4] = {'R','A','I','N'};
    char currentChar = string[rand() % 5];
    return currentChar;
}


void Rain::draw(){
    ofSetColor(color);
   // ofDrawCircle(x, y, dim);
    ofDrawBitmapString(str,x ,y, dim);
}



