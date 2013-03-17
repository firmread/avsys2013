#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetCircleResolution(80);
    ofEnableAlphaBlending();
//	ofBackground(54, 54, 54);
    
	soundStream.listDevices();
	
	int bufferSize = 256;
    historySize = 100;
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(historySize, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

}

//--------------------------------------------------------------
void testApp::update(){
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    volHistory.push_back( scaledVol );
	if( volHistory.size() >= historySize ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
}

//--------------------------------------------------------------

void testApp::drawMountain(){
    
}

void testApp::draw(){
    
    //gradient background
    ofColor bluesky;
    bluesky.setHex(0xa6ccdd);
    ofColor lightblue;
    lightblue.setHex(0xf7fafc);
    ofBackgroundGradient(lightblue, bluesky);
    
    
//	ofNoFill();
//	
//	// draw the left channel:
//	ofPushStyle();
//    ofPushMatrix();
//        ofTranslate(32, 170, 0);
//        
//        ofSetColor(225);
//        ofDrawBitmapString("Left Channel", 4, 18);
//        
//        ofSetLineWidth(1);
//        ofRect(0, 0, 512, 200);
//        
//        ofSetColor(245, 58, 135);
//        ofSetLineWidth(3);
//        
//        ofBeginShape();
//        for (int i = 0; i < left.size(); i++){
//            ofVertex(i*2, 100 -left[i]*180.0f);
//        }
//        ofEndShape(false);
//        
//    ofPopMatrix();
//	ofPopStyle();
//    
//	// draw the right channel:
//	ofPushStyle();
//    ofPushMatrix();
//        ofTranslate(32, 370, 0);
//        
//        ofSetColor(225);
//        ofDrawBitmapString("Right Channel", 4, 18);
//        
//        ofSetLineWidth(1);
//        ofRect(0, 0, 512, 200);
//        
//        ofSetColor(245, 58, 135);
//        ofSetLineWidth(3);
//        
//        ofBeginShape();
//        for (int i = 0; i < right.size(); i++){
//            ofVertex(i*2, 100 -right[i]*180.0f);
//        }
//        ofEndShape(false);
//    
//    ofPopMatrix();
//	ofPopStyle();
//	
//    for (int i = 0; i< volHistory.size(); i++) {
//        volHistory[i] *= 10*ofNoise(ofGetElapsedTimef());
//    }
    
    int mountainNo = 5;
    int mouseLapse = ofMap(mouseY, 0, ofGetHeight(), 100, 50);
    
    //5
    ofSetHexColor(0xb5bec2);
    ofBeginShape();
    int startVector5 = 0;
    int endVector5 = volHistory.size()/mountainNo;
    for (int i = startVector5; i < endVector5; i++){
        int setWidth = ofMap(i, startVector5, endVector5-1, 0, ofGetWidth()+10);
        int baseHeight = mouseLapse*5;
        int heightMul = 200;
        
        if( i == startVector5 ) ofVertex(0, ofGetHeight());
        if( i == startVector5 +1 ) ofVertex(0, ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        
        ofVertex(setWidth, ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        
        if( i == endVector5 -2 ) ofVertex(ofGetWidth(), ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        if( i == endVector5 -1 ) ofVertex(ofGetWidth(), ofGetHeight());
    }
    ofEndShape(false);
    
    //4
    ofSetHexColor(0x94a1a9);
    ofBeginShape();
    int startVector4 = volHistory.size()/mountainNo;
    int endVector4 = volHistory.size()*2/mountainNo;
    for (int i = startVector4; i < endVector4; i++){
        int setWidth = ofMap(i, startVector4, endVector4-1, 0, ofGetWidth()+10);
        int baseHeight = mouseLapse*4;
        int heightMul = 200;
        
        if( i == startVector4 ) ofVertex(0, ofGetHeight());
        if( i == startVector4 +1 ) ofVertex(0, ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        
        ofVertex(setWidth, ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        
        if( i == endVector4 -2 ) ofVertex(ofGetWidth(), ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        if( i == endVector4 -1 ) ofVertex(ofGetWidth(), ofGetHeight());
    }
    ofEndShape(false);
    
    //3
    ofSetHexColor(0x73858f);
    ofBeginShape();
    int startVector3 = volHistory.size()*2/mountainNo;
    int endVector3 = volHistory.size()*3/mountainNo;
    for (int i = startVector3; i < endVector3; i++){
        int setWidth = ofMap(i, startVector3, endVector3-1, 0, ofGetWidth()+10);
        int baseHeight = mouseLapse*3;
        int heightMul = 200;
        
        if( i == startVector3 ) ofVertex(0, ofGetHeight());
        if( i == startVector3 +1 ) ofVertex(0, ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        
        ofVertex(setWidth, ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        
        if( i == endVector3 -2 ) ofVertex(ofGetWidth(), ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        if( i == endVector3 -1 ) ofVertex(ofGetWidth(), ofGetHeight());
    }
    ofEndShape(false);
    
    
    
    
    //2
    ofSetHexColor(0x57666d);
    ofBeginShape();
    int startVector2 = volHistory.size()*3/mountainNo;
    int endVector2 = volHistory.size()*4/mountainNo;
    
    for (int i = startVector2; i < endVector2; i++){
        int setWidth = ofMap(i, startVector2, endVector2-1, 0, ofGetWidth()+10);
        int baseHeight = mouseLapse*2;
        int heightMul = 200;
        
        if( i == startVector2 ) ofVertex(0, ofGetHeight());
        if( i == startVector2 +1 ) ofVertex(0, ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        
        ofVertex(setWidth, ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        
        if( i == endVector2 -2 ) ofVertex(ofGetWidth(), ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        if( i == endVector2 -1 ) ofVertex(ofGetWidth(), ofGetHeight());
    }
    ofEndShape(false);
    
    
    
    //1
    ofSetHexColor(0x3c454a);
    ofBeginShape();
    
    int startVector1 = volHistory.size()*4/mountainNo;
    int endVector1 = volHistory.size()*5/mountainNo;
    for (int i = startVector1; i < endVector1; i++){
        int setWidth = ofMap(i, startVector1, endVector1-1, 0, ofGetWidth()+10);
        int baseHeight = mouseLapse;
        int heightMul = 200;
        
        if( i == startVector1 ) ofVertex(0, ofGetHeight());
        if( i == startVector1 +1 ) ofVertex(0, ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        
        ofVertex(setWidth, ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        
        if( i == endVector1 -2 ) ofVertex(ofGetWidth(), ofGetHeight()- baseHeight - volHistory[i] * heightMul);
        if( i == endVector1 -1 ) ofVertex(ofGetWidth(), ofGetHeight());
    }
    ofEndShape(false);
    
    
    
    ofSetColor(255,100);
    ofCircle(ofGetWidth()-20, ofGetHeight()-20, scaledVol * 10.0f);
    
    
    
	
	drawCounter++;
	
//	ofSetColor(225);
//	string reportString = "buffers received: "+ofToString(bufferCounter)+"\ndraw routines called: "+ofToString(drawCounter)+"\nticks: " + ofToString(soundStream.getTickCount());
//	ofDrawBitmapString(reportString, 32, 589);

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if( key == 's' || key =='S'){
		soundStream.start();
	}
	
	if( key == 'e' || key =='E'){
		soundStream.stop();
	}
    if ( key == 'f' || key =='F') {
        ofToggleFullscreen();
    }
    
}
//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}