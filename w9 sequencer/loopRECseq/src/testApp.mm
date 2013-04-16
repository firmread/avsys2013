//#include "testApp.h"

#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSoundStreamSetup(2,0,this, 44100, 512, 4);
	ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
	for(int i=0;i<gestures.size();i++){
		gestures[i].draw();
		string report = "gesture "+ofToString(i)+": nPts = " + ofToString(gestures[i].pts.size(), 0) + "\t total time = " + ofToString(gestures[i].totalDuration, 3);
		ofDrawBitmapString(report, 10, 14+i*14);
		
		if(gestures[i].lineComplete){
			float waitTime = 0;
			if(gestures[i].newStartTime + gestures[i].totalDuration + waitTime < ofGetElapsedTimef())
				gestures[i].newStartTime = ofGetElapsedTimef();
		}
		
	}
    
}
//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
	gestures.push_back(pointRecorder());
}
//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
	gestures[gestures.size()-1].addPoint(ofPoint(touch.x,touch.y));
}
//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
	gestures[gestures.size()-1].addPoint(ofPoint(touch.x,touch.y));
    //add one last point so that we can hold down at the end of the line and have that recorded
	gestures[gestures.size()-1].lineComplete = true; // set the line to finished
}
//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
	gestures.clear();
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
