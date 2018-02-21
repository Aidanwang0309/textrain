#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    vidGrabber.setup(320,240);
    
    myColorImg.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myGrayImage.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myBackground.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());
	myGrayDiff.allocate(vidGrabber.getWidth(),vidGrabber.getHeight());

	bLearnBackground = true;

	ofSetBackgroundAuto(false);
    
    
    
    //set up text rain
    for(int i=0; i<NRAIN; i++){
        letters[i] = generateString();
    };

}

//--------------------------------------------------------------
void ofApp::update(){

    bool bNewFrame = false;

	vidGrabber.update();
	bNewFrame = vidGrabber.isFrameNew();

	if (bNewFrame){

		myColorImg.setFromPixels(vidGrabber.getPixels());
        myGrayImage = myColorImg;
            if (bLearnBackground == true){
                myBackground = myGrayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
                bLearnBackground = false;
            }

		// take the abs value of the difference between background and incoming and then threshold:
		myGrayDiff.absDiff(myBackground, myGrayImage);
		myGrayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(myGrayDiff, 20, (340*240)/3, 1, false);
    }

    
    //update some rain
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255);

	// draw the incoming video image
	ofSetHexColor(0xffffff);
    
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2 - myColorImg.getWidth()/2,ofGetHeight()/2 - myColorImg.getHeight()/2);
	if(bShowVideo){
		myColorImg.draw(0,0);
	}
    
    for(auto &blob : contourFinder.blobs){
        ofSetColor(ofColor::violet);
        ofFill();
        ofDrawEllipse(blob.centroid, 20,20);
    }
    
    fallingLetters();
	ofPopMatrix();
    
	
	ofDrawBitmapString("Press 'v' to toggle video and path drawing", ofGetWidth()/2.0, ofGetHeight()-100.0);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key){
		case 'v':
			ofBackground(ofColor::white);
			bShowVideo = !bShowVideo;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::fallingLetters(){
    
    pix = myGrayDiff.getPixels();
    letterXSpace = ofGetWidth()/NRAIN;

    for(int i=0; i<NRAIN; i++){
        
        float locX = letterPosX + ( i * letterXSpace);
        float locY = letterPosY[i];
        
        ofDrawBitmapString(letters[i], letterPosX,letterPosY[i]);
        
        letterPosX += letterXSpace;
        
        float pixBrightness = pix.getColor(locX,locY).getBrightness();
        
        
        if(letterPosY[i] >= ofGetHeight() - 1)
        {
            letterPosY[i] = 0;
        } else if(pixBrightness < threshold)
        {
            if(letterPosY[i] > 10)
            {
                letterPosY[i]-=letterSpeed;
            }
        }
        else
        {
            letterPosY[i]+=letterSpeed;
        }
    }
    
}
//--------------------------------------------------------------

char ofApp::generateString(){
    char string[4] = {'R','A','I','N'};
    char currentChar = string[rand() % 5];
    return currentChar;
}
