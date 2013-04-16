#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxOpticalFlowLK.h"


class testApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	ofVideoGrabber 		vidGrabber;


	ofxCvColorImage			colorImg;
	ofxCvGrayscaleImage 	grayImage,prevGrayImage;
	ofxOpticalFlowLK		flow;
    ofxCvGrayscaleImage     diff;
	
    float aspectRatio;
    
    int threshold;
	
    
    
    void audioIn(float * input, int bufferSize, int nChannels);
	
    vector <float> left;
    vector <float> right;
    
    float smoothedVol;
    float scaledVol;
    
    ofSoundStream soundStream;
    
    
    ofSoundPlayer twomoons;
    int songnum;
    float speed;
};

#endif
