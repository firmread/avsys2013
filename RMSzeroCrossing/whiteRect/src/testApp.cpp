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
    
//    ofEnableSmoothing();
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    ofEnableAlphaBlending();
    ofSetCircleResolution(100);
//    ofSetBackgroundAuto(false);
    
    
    rmsHistory.assign(200, 0.0);
    zeroCrossHistory.assign(200, 0.0);
    
    delayMillis = 2000;
    ofToggleFullscreen();
    
    rotateMode = true;
    showInput = false;
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (ofGetElapsedTimeMillis()>delayMillis) {
        zeroCrossHistory.push_back(pitch);
        if (zeroCrossHistory.size() > 200)  zeroCrossHistory.erase(zeroCrossHistory.begin());
        rmsHistory.push_back(volume);
        if (rmsHistory.size() > 200)        rmsHistory.erase(rmsHistory.begin());
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    ofColor dark;
    
    if ( ofGetElapsedTimeMillis()< delayMillis*3){
        int runToDark = 0;
        runToDark = ofMap(ofGetElapsedTimeMillis(), 0, delayMillis*3, 0, 40);
        dark.set(runToDark);
    }
    else if ( ofGetElapsedTimeMillis()> delayMillis*3){
        dark.set(40);
    }
    
    ofBackgroundGradient(ofColor::black,dark);
    
    float hue = 0;
    float sat = 0;
    float bri = 255;
    
    int zeroCdown = 100;
    int rmsUp = 150;

    // show input stuffs
    if (ofGetElapsedTimeMillis()>delayMillis && showInput) {
        ofSetColor(255,200);
    
        ofCircle(50,ofGetHeight()-50, volume*rmsUp);
        ofCircle(50,ofGetHeight()-50, volumeSmoothSlow*rmsUp);
        
        ofCircle(ofGetWidth()-150,ofGetHeight()-50, pitch/zeroCdown);
        ofCircle(ofGetWidth()-150,ofGetHeight()-50, pitchSmoothSlow/zeroCdown);
        
        ofDrawBitmapStringHighlight(ofToString(volume), ofPoint(50,ofGetHeight()-70));
        ofDrawBitmapStringHighlight(ofToString(volumeSmoothSlow), ofPoint(50,ofGetHeight()-50));
        
        ofDrawBitmapStringHighlight(ofToString(pitch), ofPoint(ofGetWidth()-150,ofGetHeight()-70));
        ofDrawBitmapStringHighlight(ofToString(pitchSmoothSlow), ofPoint(ofGetWidth()-150,ofGetHeight()-50));
    }
    
    
    ofColor color;
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    // dance with scale and rotate
    if (ofGetElapsedTimeMillis()>delayMillis) {
        ofScale(1+volumeSmoothSlow*3, 1+volumeSmoothSlow*3);
        if (rotateMode) {
            ofRotateZ((ofGetElapsedTimeMillis()-4000)*pitchSmoothSlow/10000);
        }
    }
    
    // Zero Crossing/pitch half of the square
    hue = ofMap(pitch, 0, 3000, 180, 254, true);
    sat = 180;
    bri = ofMap(pitch, 0, 3000, 100, 255, true);
    
    color.setHsb(hue, sat, bri);
    ofSetColor(color);
    
    ofBeginShape();
    ofVertex(-50, -50);
    for (int i=0; i< zeroCrossHistory.size()/2; i++) {
        ofVertex(-50-zeroCrossHistory[i]/zeroCdown, -50+i);
    }
    for (int i=zeroCrossHistory.size()/2; i< zeroCrossHistory.size(); i++) {
        ofVertex(-150+i, 50+zeroCrossHistory[i]/zeroCdown);
    }
    ofVertex(50, 50);
    ofEndShape();
    
    
    // Root Mean Square/volume half of the square
    hue = ofMap(volume, 0, 0.2, 0, 180, true);
    sat = 180;
    bri = ofMap(volume, 0, 0.2, 100, 255, true);
    
    color.setHsb(hue, sat, bri);
    ofSetColor(color);
    
    ofBeginShape();
    ofVertex(-50, -50);
    for (int i=0; i< rmsHistory.size()/2; i++) {
        ofVertex(-50+i, -50-rmsHistory[i]*rmsUp);
    }
    for (int i=rmsHistory.size()/2; i< rmsHistory.size(); i++) {
        ofVertex(50+rmsHistory[i]*rmsUp, -150+i);
    }
    ofVertex(50, 50);
    ofEndShape();

    
    // start whiteRect
    int stillMillis = 1000;
    if (ofGetElapsedTimeMillis()<stillMillis) {
        ofSetColor(255, 255);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(0, 0, 100, 100);
        ofSetRectMode(OF_RECTMODE_CORNER);
    }
    
    // fade after mill 1000 > 2000
    if (ofGetElapsedTimeMillis()>stillMillis && ofGetElapsedTimeMillis()<delayMillis) {
        float alpha = ofMap(ofGetElapsedTimeMillis(), stillMillis, delayMillis, 255, 0,true);
        ofSetColor(255, alpha);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(0, 0, 100, 100);
        ofSetRectMode(OF_RECTMODE_CORNER);
    }
    
    // kick in input visualization
    if (ofGetElapsedTimeMillis()> 4000 && ofGetElapsedTimeMillis()< 5000) {
        showInput = true;
    }

    

    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'f' || key == 'F') {
        ofToggleFullscreen();
    }
    if (key == 'r' || key == 'R')  {
        rotateMode = !rotateMode;
    }
    if (key == 'i' || key == 'I') {
        showInput = !showInput;
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
    pitchSmoothSlow = 0.995f * pitchSmoothSlow + 0.005f * pitchVal;
    
    
}

