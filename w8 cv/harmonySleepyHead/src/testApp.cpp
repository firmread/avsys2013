#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
	int w = 640 , h = 480;

	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(w, h);

	colorImg.allocate(w, h);
	grayImage.allocate(w, h);
	prevGrayImage.allocate(w, h);
    diff.allocate(w, h);
	
	flow.setup(w, h);
    
    
    
    
    
    
    int bufferSize = 256;
	
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
    twomoons.loadSound("twomoons.mp3");
	twomoons.setLoop(true);
	twomoons.play();
	twomoons.setSpeed(0.5);
    songnum = 1;

}

//--------------------------------------------------------------
void testApp::update(){
    
    
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    
    

	bool bNewFrame = false;
	vidGrabber.update();
	bNewFrame = vidGrabber.isFrameNew();

	if (bNewFrame){
		colorImg.setFromPixels(vidGrabber.getPixels(), vidGrabber.getWidth(), vidGrabber.getHeight());
		grayImage = colorImg;
		grayImage.mirror(false, true);
        
        diff.absDiff(grayImage,prevGrayImage);
        diff.threshold(threshold);
        prevGrayImage = grayImage;
        
		flow.update(grayImage);
	}
    
    if (songnum == 1) speed = ofMap(diff.countNonZeroInRegion(0, 0, diff.getWidth(), diff.getHeight()), 0, 300000, .1, 2,true);
    if (songnum == 2) speed = ofMap(diff.countNonZeroInRegion(0, 0, diff.getWidth(), diff.getHeight()), 0, 300000, .05, 1,true);
    
    
    twomoons.setSpeed(speed);
    aspectRatio = vidGrabber.getWidth()/vidGrabber.getHeight();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    
    ofSetColor(70,200);
	grayImage.draw(0,0, ofGetWidth(), ofGetWidth()/aspectRatio);
    
    ofColor opaque(0,0);
    ofBackgroundGradient(opaque, ofColor::black);
    
    ofSetColor(255);
	flow.draw(ofGetWidth(), ofGetWidth()/aspectRatio, 2+ (scaledVol*100),7);
    
    ofDrawBitmapStringHighlight(" press '1' for harmony mode\n press '2' for sleepy mode",0, ofGetHeight()-20);
    
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    if(key=='f') ofToggleFullscreen();
    if (key == '1') {
        twomoons.loadSound("twomoons.mp3");
        twomoons.setLoop(true);
        twomoons.play();
        twomoons.setSpeed(0.5);
        songnum = 1;
    }
    if (key == '2') {
        twomoons.loadSound("sleepyhead.mp3");
        twomoons.setLoop(true);
        twomoons.play();
        twomoons.setSpeed(0.5);
        songnum = 2;
    }
}
//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
	int numCounted = 0;
    
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	//rms
	curVol /= (float)numCounted;
	curVol = sqrt( curVol );
	//xeno
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
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

