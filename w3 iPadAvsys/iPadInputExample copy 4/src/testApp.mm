#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
    //default rotation
	//ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	
    
    
    //setup sound input
    initialBufferSize = 512;
	sampleRate = 44100;
	drawCounter = 0;
	bufferCounter = 0;
	buffer = new float[initialBufferSize];
	memset(buffer, 0, initialBufferSize * sizeof(float));
	/*  0 output channels,
        1 input channels
        44100 samples per second
        512 samples per buffer
        4 num buffers (latency)     */
	ofSoundStreamSetup(0, 1, this, sampleRate, initialBufferSize, 4);
    
    
    
    // initialize the compass
	coreLocation = new ofxiPhoneCoreLocation();
	hasCompass = coreLocation->startHeading();
	hasGPS = coreLocation->startLocation();
	
	heading = 0.0;
    
    
	ofBackground(77);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    //update compass
    heading     = ofLerpDegrees(heading, -coreLocation->getTrueHeading(), 0.7);
    
    //Accellerometer input
//    float angle = 180 - RAD_TO_DEG * atan2( ofxAccelerometer.getForce().y, ofxAccelerometer.getForce().x );

}

//--------------------------------------------------------------
void testApp::draw(){
    
    //log messages
    ofSetColor(255);
    ofDrawBitmapString("time:   " +
                       ofToString(ofGetHours()) +
                       ":" +
                       ofToString(ofGetMinutes()) +
                       ":" +
                       ofToString(ofGetSeconds()) , 20, 20);
    ofDrawBitmapString("elapsed time:   "+ ofToString(ofGetElapsedTimeMillis()), 20, 35);
    ofDrawBitmapString(ofToString(eventString) , 20, 50);
    ofDrawBitmapString("orientation no:   "+ ofToString(orientation) , 20, 65);
    ofDrawBitmapString("Accellerometer x:   "+ ofToString(ofxAccelerometer.getForce().x) , 20, 80);
    ofDrawBitmapString("Accellerometer y:   "+ ofToString(ofxAccelerometer.getForce().y) , 20, 95);
    
    
    
    // compass triangle
    ofPushMatrix();
    ofTranslate (ofGetWidth()/2, ofGetHeight()/8, 0);
    ofRotateZ   (heading);
	float size  = 20;
	ofPoint ptA = ofPoint( cos(TWO_PI/3)    * size, sin(TWO_PI/3)   * size);
	ofPoint ptB = ofPoint( cos(2*TWO_PI/3)  * size, sin(2*TWO_PI/3) * size);
	ofPoint ptC = ofPoint( cos(3*TWO_PI/3)  * size, sin(3*TWO_PI/3) * size);
	ofTriangle  (ptA, ptB, ptC);
    ofPopMatrix();
    
    
    //soundwave
	ofSetColor(200);
	ofRect(20, 100, 512, 200);
	ofSetColor(255);
	for(int i = 0; i < initialBufferSize; i++){
		ofLine(20 + i, 200, 20 + i, 200 + buffer[i] * 100.0f);
	}
	ofSetColor(200);
	drawCounter++;
	char reportString[255];
	sprintf(reportString, "buffers received: %i\ndraw routines called: %i\n", bufferCounter, drawCounter);
	ofDrawBitmapString(reportString, 20, 308);

}


//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
	sprintf(eventString, "touchDown = (%2.0f, %2.0f - id %i)", touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
	sprintf(eventString, "touchMoved = (%2.0f, %2.0f - id %i)", touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
	sprintf(eventString, "touchUp = (%2.0f, %2.0f - id %i)",touch.x, touch.y, touch.id);
}


//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
    
	if(initialBufferSize != bufferSize){
		ofLog(OF_LOG_ERROR,
              "your buffer size was set to %i - but the stream needs a buffer size of %i",
              initialBufferSize, bufferSize);
		return;
	}
	
	// samples are "interleaved"
	for(int i = 0; i < bufferSize; i++){
		buffer[i] = input[i];
	}
	bufferCounter++;
    
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    orientation = newOrientation;
    /*  homebutton down     = 1,
     homebutton up       = 2,
     homebutton right    = 3,
     homebutton left     = 4,
     face up             = 5,
     face down           = 6     */
}


//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
	sprintf(eventString, "doubleTap at (%2.0f, %2.0f)",touch.x, touch.y);
}
//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){}

//--------------------------------------------------------------
void testApp::lostFocus(){
	sprintf(eventString, "alert - lost focus");
}

//--------------------------------------------------------------
void testApp::gotFocus(){
	sprintf(eventString, "alert - got focus");
}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){
	sprintf(eventString, "alert - memory warning");
}


//--------------------------------------------------------------
void testApp::exit(){}
