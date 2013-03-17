#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "oscillator.h"


class testApp : public ofxiPhoneApp{
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);
    
    
        //audio out
    
        void audioOut(float * input, int bufferSize, int nChannels);
        
        ofSoundStream stream;
        
        float * soundBuffers[3];
        float * totalSoundBuffer;
        
        oscillator sinWaves[3];

        int sineMod1, sineMod2, sineMod3;
    
    
    

};


