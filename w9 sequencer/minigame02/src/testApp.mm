//#include "testApp.h"

#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	// initialize the accelerometer
	ofxAccelerometer.setup();
    ofxAccelerometer.setForceSmoothing(0.55f);
    
    start.set(ofGetWidth()/2, ofGetHeight()/2);
    cursorIn = start;
    
    ofSetCircleResolution(8);
    ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofEnableSmoothing();
    
    indicator = 0;
    circleSize = CIRCLE_SIZE;
    goal = 350;
    holdSize = 120;
    
    cursorIn.set(0,0);
    accelXeno.set(0,0);
    
    
    ofSetColor(ofColor::blanchedAlmond);
    if(bFingerPressed) ofSetColor(ofColor::cadetBlue);
    
    
    corner[0].set(0,0);
    corner[1].set(ofGetWidth(),0);
    corner[2].set(0, ofGetHeight());
    corner[3].set(ofGetWidth(), ofGetHeight());
    
    for (int i = 0; i<4; i++) {
        bCorner[i] = false;
    }
    
    //particles drawings
	bFingerPressed = false;
    gestures.push_back(pointRecorder());
    
	ofSoundStreamSetup(2,0,this, 44100, 512, 4);
}

//--------------------------------------------------------------
void testApp::update(){
	
    
    if(bCorner[0] && bCorner[1] && bCorner[2] && bCorner[3]) bFingerPressed =true;
    else bFingerPressed = false;
    
    if (!bFingerPressed) particles.clear();
    if (gestures.size()) {
        if (!bFingerPressed && gestures[gestures.size()-1].pts.size()>0) {
            gestures[gestures.size()-1].lineComplete = true;
            gestures.push_back(pointRecorder());
        }

    }
    
    //accel input
    ofPoint accelIn = ofxAccelerometer.getForce();
    ofClamp(accelIn.x, -.6, .6);
    ofClamp(accelIn.y, -.6, .6);
    
    float xenoSpeed = 0.2f;
    accelXeno = (xenoSpeed)* accelIn + (1-xenoSpeed)* accelXeno;
    cursorIn.x = ofMap(accelXeno.x, -.6, .6, 0, ofGetWidth(),true);
    cursorIn.y = ofMap(accelXeno.y, .6, -.6, 0, ofGetHeight(),true);
    
    
    
    
    //drawing
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
		particles[i].addDampingForce();
		particles[i].update();
	}
    
	// use xeno to catch the mouse:
    smoothedTouch.x = 0.9f * smoothedTouch.x + 0.1f * cursorIn.x;
    smoothedTouch.y = 0.9f * smoothedTouch.y + 0.1f * cursorIn.y;
    
	if (bFingerPressed){
        
		float dx = smoothedTouch.x - prevTouch.x;
		float dy = smoothedTouch.y - prevTouch.y;
		particle myParticle;
		myParticle.setInitialCondition(cursorIn.x,cursorIn.y, dx,dy);
		particles.push_back(myParticle);
        
        
        gestures[gestures.size()-1].addPoint(cursorIn);
	}
	
	prevTouch = smoothedTouch;
    if (particles.size()>PARTICLE_NUM) particles.clear();
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    //bg
    ofColor dark(40);
    ofBackgroundGradient(dark, ofColor::black);
    
    
    
    //circle bar
    ofSetColor(ofColor::cadetBlue,30);
    ofSetRectMode(OF_RECTMODE_CORNER);
    float bar = ofMap(particles.size(), 0, PARTICLE_NUM, 0, ofGetHeight()/2);
    ofCircle(start, bar);
    
    
    //color-touch detect
    ofSetColor(ofColor::blanchedAlmond,100);
    if(bFingerPressed) {
        if (gestures.size()) {
            int yVal = (float)gestures[gestures.size()-1].startY/ofGetHeight() * 255;
            ofSetColor(yVal, (255-yVal)-yVal, 255-yVal, 150);
        }
        else ofSetColor(ofColor::cadetBlue,100);
    }
    
    for(int i=0;i<gestures.size();i++){
		gestures[i].draw();
		
		if(gestures[i].lineComplete){
			float waitTime = 0;
			if(gestures[i].newStartTime + gestures[i].totalDuration + waitTime < ofGetElapsedTimef())
				gestures[i].newStartTime = ofGetElapsedTimef();
		}
		
	}
    
    //drawings
	ofNoFill();
    ofSetLineWidth(3);
	ofBeginShape();
	for (int i = 0; i < particles.size(); i++){
		ofCurveVertex(particles[i].pos.x, particles[i].pos.y);
	}
	ofEndShape();
    ofFill();
	
    //cursorIn
    ofCircle(cursorIn, circleSize/3);
    ofCircle(cursorIn, circleSize*2/3);
    ofCircle(cursorIn, circleSize);
    
    
    
    //hold buttons
    for (int i = 0; i<4; i++) {
        ofSetColor((bCorner[i])? ofColor::seaGreen: ofColor::salmon);
        ofCircle(corner[i], holdSize);
    }
    
    for(int i=0;i<gestures.size();i++){
		string report = "gesture "+ofToString(i)+": nPts = " + ofToString(gestures[i].pts.size(), 0) + "\t total time = " + ofToString(gestures[i].totalDuration, 3);
		ofDrawBitmapString(report, 10, 14+i*14);
    }
    
}
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    
    //extract touch.id cases, varies on where finger lands on
    if      (touch.y<ofGetHeight()/2) {
        if      (touch.x<ofGetWidth()/2) touch.id = 1;
        else if (touch.x>=ofGetWidth()/2) touch.id = 2;
    }
    else if (touch.y>=ofGetHeight()/2){
        if      (touch.x<ofGetWidth()/2) touch.id = 3;
        else if (touch.x>=ofGetWidth()/2) touch.id = 4;
    }
    
    for (int i=0; i<4; i++) {
        if (touch.id == i+1) {
            ofPoint holdDiff;
            holdDiff.x = corner[i].x-touch.x;
            holdDiff.y = corner[i].y-touch.y;
            if(holdDiff.length()<holdSize) bCorner[i] = true;
        }
    }
}
//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    if      (touch.y<ofGetHeight()/2) {
        if      (touch.x<ofGetWidth()/2) touch.id = 1;
        else if (touch.x>=ofGetWidth()/2) touch.id = 2;
    }
    else if (touch.y>=ofGetHeight()/2){
        if      (touch.x<ofGetWidth()/2) touch.id = 3;
        else if (touch.x>=ofGetWidth()/2) touch.id = 4;
    }
    
    for (int i=0; i<4; i++) {
        if (touch.id == i+1) {
            ofPoint holdDiff;
            holdDiff.x = corner[i].x-touch.x;
            holdDiff.y = corner[i].y-touch.y;
            
            if(holdDiff.length()>holdSize) bCorner[i] = false;
            else if(holdDiff.length()<holdSize) bCorner[i] = true;
        }
    }}
//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
    if      (touch.y<ofGetHeight()/2) {
        if      (touch.x<ofGetWidth()/2) touch.id = 1;
        else if (touch.x>=ofGetWidth()/2) touch.id = 2;
    }
    else if (touch.y>=ofGetHeight()/2){
        if      (touch.x<ofGetWidth()/2) touch.id = 3;
        else if (touch.x>=ofGetWidth()/2) touch.id = 4;
    }
    
    for (int i=0; i<4; i++) {
        if (touch.id == i+1) {
            ofPoint holdDiff;
            holdDiff.x = corner[i].x-touch.x;
            holdDiff.y = corner[i].y-touch.y;
            
            if(holdDiff.length()<                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                holdSize) bCorner[i] = false;
        }
    }
}
//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    if (newOrientation == 6) {
        gestures.clear();
    }
}
//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){}
//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){}
//--------------------------------------------------------------
void testApp::lostFocus(){}
//--------------------------------------------------------------
void testApp::gotFocus(){}
//--------------------------------------------------------------
void testApp::gotMemoryWarning(){}
//--------------------------------------------------------------
void testApp::exit(){}

void testApp::audioRequested(float * output, int bufferSize, int nChannels){
	
	for (int i = 0; i < bufferSize; i++){
		output[i*nChannels    ] = 0;
		output[i*nChannels + 1] = 0;
	}
	
	if(gestures.size()>0){
		for(int i=0;i<gestures.size();i++)
			gestures[i].addToSoundBuffer(output, bufferSize);
		
		for (int i = 0; i < bufferSize; i++){ // avgerage all the inputs so the sound never goes over 1.0
			output[i*nChannels    ] /= gestures.size();
			output[i*nChannels + 1] /= gestures.size();
		}
	}
}
