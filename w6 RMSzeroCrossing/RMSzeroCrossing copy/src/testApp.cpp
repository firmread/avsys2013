#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
    ofEnableAlphaBlending();
    soundStream.setup(this, 0, 1, 44100, 256, 4);
//	ofSetBackgroundAuto(false);
	
	ofSetColor(255);
	ofBackground(0);

	crossingSum = 0;
	
    startSecond = ofGetSeconds();
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if (ofGetSeconds() == startSecond) {
        ofSetColor(255);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(ofGetWidth()/2, ofGetHeight()/2, 100, 100);
    }
    
	float timeMultiplier = 50;
//	float xPos = fmod(ofGetElapsedTimef()*timeMultiplier, ofGetWidth());
    float xPos = int(ofGetElapsedTimef()*timeMultiplier)% ofGetWidth();
    
    ofSetColor(0,5);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
	
	if (xPos < 1) {
//		ofBackground(0);
	}
	
    
    
	//cout << xPos << endl;
	ofSetRectMode(OF_RECTMODE_CORNER);
    
    for (int i = 0; i< rmsRect.size(); i++){
        ofSetColor(255,100);
        ofRectangle rect;
        rect.set(xPos, 100, 2, rms*300);
        //    ofLine(xPos, 100, xPos, 100+rms*300);
//        ofRect(xPos, 100, 2, rms * 300);
        rmsRect.push_back(rect);
    }
    
    
    
    
//	ofLine(xPos, 300, xPos, 300+pitch);
	ofRect(xPos, 300, 1, pitch);
    
	
	//ofDrawBitmapString("Pitch: " + ofToString(lastHz), 10, 10);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'f' || key == 'F') {
        ofToggleFullscreen();
        
        ofSetColor(255);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(ofGetWidth()/2, ofGetHeight()/2, 100, 100);
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
	
}

void testApp::audioIn(float * input, int bufferSize, int nChannels){
    
	float samplesSummed = 0;
	
	bool lastSampleWasPositive = false;
	int numCrossings = 0;
	
	float xenoSample = 0;
	
    for (int i = 0; i < bufferSize; i++){
		// RMS
		float sampleSquared = input[i] * input[i];
		samplesSummed += sampleSquared;
		
        float xenoSpeed = 0.19f;
		if (i != 0) {
			xenoSample = input[i] * xenoSpeed + input[i-1] * (1 - xenoSpeed);
		}
//		pos.x = target.x * speed + pos.x * (1 - speed);
		
		
		// Zero crossings
		//if (lastSampleWasPositive && (input[i] < 0)) {
		if (lastSampleWasPositive && (xenoSample < 0)) {
			// crossing
			numCrossings++;
		}
//		if (!lastSampleWasPositive && (input[i] > 0)) {
		if (!lastSampleWasPositive && (xenoSample > 0)) {
			// crossing
			numCrossings++;
		}
		
		if (xenoSample > 0)
			lastSampleWasPositive = true;
		else
			lastSampleWasPositive = false;
		
    }
	
	float samplesDividedByTotal = samplesSummed / bufferSize;
	rms = sqrt(samplesDividedByTotal);
	
	//cout << rms << endl;
	
	//cout << numCrossings << endl;
	//pitch = numCrossings;
	
	float xenoPitch = numCrossings * 0.19f + lastPitch * (1 - 0.19f);
	pitch = xenoPitch;
	
	lastPitch = pitch;
	
	float bufferMultiplier = 44100 / bufferSize;
	float mattHz = xenoPitch * bufferMultiplier / 2;
	
	lastHz = mattHz;
	
	
	crossingSum += xenoPitch;
	
	//float sumForPrint = crossingSum / 2;
	
	cout << "Pitch: " << mattHz /* << " Firm pitch: " << sumForPrint */ << endl;
	
	if (lastTime != ofGetSeconds()) {
		
		crossingSum = 0;
	}
	
	lastTime = ofGetSeconds();
    
}

