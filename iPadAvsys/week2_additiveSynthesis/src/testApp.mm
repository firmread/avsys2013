#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
        
	ofBackground(50);
    
    stream.setup(this, 2, 0, 44100, 512, 4);
    
    totalSoundBuffer = new float[512];
    
    for (int i = 0; i < 3; i++){
        sinWaves[i].setup(44100);
        sinWaves[i].setFrequency( ofRandom(400,1000));
        sinWaves[i].setVolume(0.1);
        
        soundBuffers[i] = new float[512];
    }
    
    sineMod1 = ofRandom(400,1000);
    sineMod2 = ofRandom(400,1000);
    sineMod3 = ofRandom(400,1000);
}

//--------------------------------------------------------------
void testApp::update(){
    sinWaves[0].setFrequency( max(1,sineMod1) );  // don't want to give a negative frequency...
    sinWaves[1].setFrequency( max(1,sineMod2) );
    sinWaves[2].setFrequency( max(1,sineMod3) );

}

//--------------------------------------------------------------
void testApp::draw(){
    
    for (int i = 0; i < 3; i++){
        ofFill();
        ofSetColor(0);
        ofRect(20,20 + i * 220,512, 200);
        
        ofNoFill();
        ofSetColor(200);
        ofBeginShape();
        for (int j = 0; j < 512; j++){
            ofVertex(20 + j, 20 + i * 220 + 100 + 100 * soundBuffers[i][j]);
        }
        ofEndShape();
    }
    
    
    
    ofFill();
    ofSetColor(0);
    ofRect(20,ofGetHeight()-220,512, 200);
    
    ofNoFill();
    ofSetColor(255);
    ofBeginShape();
    for (int i = 0; i < 512; i++){
        ofVertex(20 + i, ofGetHeight()-120 + 100 * totalSoundBuffer[i]);
    }
    ofEndShape();
}


//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
    if (touch.id ==0) {
        sineMod1 = ofRandom(400,1000);
        sineMod2 = ofRandom(400,1000);
        sineMod3 = ofRandom(400,1000);
    }
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
    if (touch.id ==1) {
        sineMod1 = touch.x + touch.y;
    }
    else if (touch.id ==2) {
        sineMod2 = abs (touch.x - touch.y);
    }
    else if (touch.id ==3) {
        sineMod3 = touch.x*2+ touch.y;
    }
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){}

//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){
    
	for (int i = 0; i < bufferSize; i++){
        
        
        float sample = 0;
        
        for (int j = 0; j < 3; j++){
            float val = sinWaves[j].getSample();
            soundBuffers[j][i] = val;
            sample += val;
        }
        
        output[i*nChannels    ] = sample;
        output[i*nChannels + 1] = sample;
        
        totalSoundBuffer[i] = sample;
	}
    
    
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){}
void testApp::touchDoubleTap(ofTouchEventArgs & touch){}
void testApp::touchCancelled(ofTouchEventArgs & touch){}
void testApp::lostFocus(){}
void testApp::gotFocus(){}
void testApp::gotMemoryWarning(){}
void testApp::exit(){}
