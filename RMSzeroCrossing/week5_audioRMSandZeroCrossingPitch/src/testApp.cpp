#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    soundStream.setup(this, 0, 1, 44100, 256, 4);
    
    sampleSmooth = 0;
    bSignOflastValue = false;
    
    volume = 0;
    pitch = 0;
    
    volumeSmoothSlow = 0;
    pitchSmoothSlow = 0;
    
    ofSetVerticalSync(true);
    ofBackground(0);
    ofEnableAlphaBlending();
//    ofSetBackgroundAuto(false);
    black = 0;
    white = 255;
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    ofDrawBitmapStringHighlight(ofToString(volumeSmoothSlow), ofPoint(50,ofGetHeight()-50));
    ofDrawBitmapStringHighlight(ofToString(pitchSmoothSlow), ofPoint(ofGetWidth()-150,ofGetHeight()-50));
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofColor color;
    
    
    float sat = 0;
    float bri = 255;
    float hue = 0;
    
//    if (ofGetElapsedTimeMillis() <= 5000) {}
    
    if (ofGetElapsedTimeMillis() > 3000) {
        
        sat = 180;
        bri = ofMap(volume, 0, 0.2, 255, 0, true);
        hue = ofMap(pitch, 0, 3000, 0, 254, true);
    }
    
        color.setHsb(hue, sat, bri);
        ofSetColor(color);
        ofFill();
        ofRect(ofGetWidth()/2, ofGetHeight()/2-25, 100, 50);
        
    
    if (ofGetElapsedTimeMillis() > 3000) {
        sat = 180;
        bri = ofMap(volumeSmoothSlow, 0, 0.2, 255, 0, true);
        hue = ofMap(pitchSmoothSlow, 0, 3000, 0, 254, true);
    }
    
        color.setHsb(hue, sat, bri);
        ofSetColor(color);
        ofFill();
        ofRect(ofGetWidth()/2,ofGetHeight()/2+25,100,50);  


    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key =='f' ||key =='F') {
        ofToggleFullscreen();
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
    
    // compute RMS
    // see: http://en.wikipedia.org/wiki/Root_mean_square
    
    float rms = 0;
    for (int i = 0; i < bufferSize; i++){
        rms += input[i] * input[i];
    }
    rms /= (float)bufferSize;
    rms = sqrt(rms);
    
    volume = 0.9f * volume + 0.1 * rms;
    volumeSmoothSlow = 0.99f * volumeSmoothSlow + 0.01 * rms;
    
    
    
    // compute pitch
    
    
    
    int zeroCrossingCount = 0;
    
    for (int i = 0; i < bufferSize; i++){
        
        // this is how to do "low pass filtering"
        
        sampleSmooth = 0.9f * sampleSmooth + 0.1 * input[i];
        bool curSign = sampleSmooth > 0 ? true : false;   // if this line looks confusing, see "ternary operator"
                                                      // http://www.cplusplus.com/forum/articles/14631/
        
        // w/ out low pass filtering
        
//        bool curSign = input[i] > 0 ? true : false;
        
        if (curSign != bSignOflastValue){
            zeroCrossingCount++;
        }
        bSignOflastValue = curSign;
    }
    
    float pitchVal = zeroCrossingCount * (44100.0 / (float)bufferSize) * (0.5);
    pitch = 0.9f * pitch + 0.1 * pitchVal;
    pitchSmoothSlow = 0.99f * pitchSmoothSlow + 0.01f * pitchVal;
    
    
}

