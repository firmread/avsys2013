#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	
	squirrel.loadImage("camp.jpg");
	squirrel.setImageType(OF_IMAGE_COLOR);
    copy = squirrel;
    copy.setImageType(OF_IMAGE_GRAYSCALE);
	
	ofBackground(0,0,0);
    
    ofSetCircleResolution(3);
    
    mode = 2;
    
    
    
    
    int bufferSize = 256;
	
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

    
}

//--------------------------------------------------------------
void testApp::update(){
    
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
}

//--------------------------------------------------------------
void testApp::draw(){
	
    
	ofSetColor(0,0,0);
	squirrel.draw(0,0);

    
	unsigned char * pixels = squirrel.getPixels();
    
	
	for (int i = 0; i < squirrel.width; i+=MAX(1,constraint)){
		for (int j = 0; j < squirrel.height; j+=MAX(1,constraint)){
			
			int red = pixels[ (j * squirrel.width + i) * 3];
			int green = pixels[ (j * squirrel.width + i) * 3 + 1];
			int blue = pixels[ (j * squirrel.width + i) * 3 + 2];
			
            int value = pixels[j * copy.width + i];
			float pct = ofMap(value, 0,255, 3,10);
            
			ofSetColor(red,green,blue);
            ofSetCircleResolution(pct);
			ofCircle( i, j, constraint);
		}
	}
    ofDrawBitmapStringHighlight("press 1, 2, or 3 to choose mode", 20,670);
    if (mode ==1) {
        constraint = ofMap(mouseX, 0, ofGetWidth(), 3, 30);
        ofDrawBitmapStringHighlight("mode 1 : mouseX : constraint = " + ofToString(constraint), 320, 670);
    }
    if (mode ==2) {
        constraint = 3+abs(30*sin(ofGetElapsedTimef()*scaledVol));
        ofDrawBitmapStringHighlight("mode 2 : sin * inputVolume : constraint = " + ofToString(constraint), 320, 670);
    }
    if (mode ==3) {
        constraint = 50*ofNoise(ofGetElapsedTimef()*scaledVol);
        ofDrawBitmapStringHighlight("mode 3 : noise * inputVolume : constraint = " + ofToString(constraint), 320, 670);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key =='1') {
        mode = 1;
    }
    if (key =='2') {
        mode = 2;
    }
    if (key =='3') {
        mode = 3;
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

