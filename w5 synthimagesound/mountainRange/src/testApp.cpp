#include "testApp.h"

void testApp::setup(){

    //setup audio in
    ofSoundStreamSetup(0, 2, this, 44100, BUFFER_SIZE, 4);
    left = new float [BUFFER_SIZE];
    right= new float [BUFFER_SIZE];
    
    //setup FFT
    FFTanalyzer.setup(44100, BUFFER_SIZE/2, 2);
    FFTanalyzer.peakHoldTime    = 30;
    FFTanalyzer.peakDecayRate   = 0.095f;
    FFTanalyzer.linearEQIntercept = 0.9f;
    FFTanalyzer.linearEQSlope   = 0.01f;
    
    //
    ofEnableAlphaBlending();
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
}

void testApp::update(){
    
    float avg_power = 0.0f;
    myfft.powerSpectrum(0, (int) BUFFER_SIZE/2, left, BUFFER_SIZE, &magnitude[0], &phase[0], &power[0], &avg_power);
    
    for(int i = 0; i<BUFFER_SIZE/2; i++){
        freq[i] = magnitude[i];
    }
    FFTanalyzer.calculate(freq);
}

void testApp::draw(){
    
    //gradient background
    ofColor bluesky;
    bluesky.setHex(0xa6ccdd);
    ofColor lightblue;
    lightblue.setHex(0xf7fafc);
    ofBackgroundGradient(lightblue, bluesky);
    
    
    
    ofFill();
    ofPushMatrix();
    ofTranslate(0, ofGetHeight()-20);
    ofBeginShape();
    ofVertex(0, ofGetHeight());
    ofSetColor(40, 80, 20,150);
    
    for (int i = 0;i < FFTanalyzer.nAverages; i++){
        ofPoint posIn(i*70-1, -FFTanalyzer.averages[i]*15);
        ofPoint posOut;
        float catchspeed = 0.9f;
        posOut.x = catchspeed * posIn.x + (1-catchspeed) * posOut.x;
        posOut.y = catchspeed * posIn.y + (1-catchspeed) * posOut.y;
        
        
//        ofCurveVertex(i*70, -FFTanalyzer.averages[i]*15);
        ofCurveVertex(posOut);
        
    }
    ofVertex(ofGetWidth(), ofGetHeight());
    ofEndShape();
    ofPopMatrix();
    
    
    
}

void testApp::audioIn (float * input, int bufferSize, int nChannels){
    for (int i = 0; i < bufferSize; i++){
        left [i]    =   input [i*2  ];
        right[i]    =   input [i*2+1];
    }
}

void testApp::keyPressed(int key){
    if(key=='f'||key=='F'){
        ofToggleFullscreen();
    }
}


void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}