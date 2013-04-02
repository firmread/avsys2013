#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
    soundStream.setup(this, 0, 1, 44100, 256, 4);
	ofSetBackgroundAuto(false);
	
	ofSetColor(255);
	ofBackground(127);

	crossingSum = 0;
	
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){

	
	float timeMultiplier = 50;
	float xPos = fmod(ofGetElapsedTimef()*timeMultiplier, ofGetWidth());
	
	if (xPos < 1) {
		ofBackground(127);
	}
	
	//cout << xPos << endl;
	
	ofRect(xPos, 100, 1, rms * 300);
	//printf("x: %f, y: %i, w: %i, h: %f\n",fmod(ofGetElapsedTimef()*20, ofGetScreenWidth()), 100, 1, rms * 300 );
	
	ofRect(xPos, 300, 1, pitch * 3);
	
	//ofDrawBitmapString("Pitch: " + ofToString(lastHz), 10, 10);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
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
		
		if (i != 0) {
			xenoSample = input[i] * 0.19f + input[i-1] * (1 - 0.19f);
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

