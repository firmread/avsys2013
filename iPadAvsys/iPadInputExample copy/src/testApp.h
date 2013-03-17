#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

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
    
        //audio input
        void audioIn(float * input, int bufferSize, int nChannels);
        int	initialBufferSize;
        int	sampleRate;
        int	drawCounter;
        int bufferCounter;
        float * buffer;
    
        //display log string
        char eventString[255];
        char timeString[255];
    
        //compass
        ofxiPhoneCoreLocation * coreLocation;
        float heading;
        float sinheading;
        bool hasCompass;
        bool hasGPS;
    
        //orientation
        int orientation;
    
    
    

};


