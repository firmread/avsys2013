#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void drawGravity(ofPoint p, ofPoint gravity);
    
    ofxBox2d                 box2dA;
    ofxBox2d                 box2dB;
    
    vector <ofxBox2dCircle>  circlesA;
    vector <ofxBox2dCircle>  circlesB;
    vector <ofxBox2dRect>    sharedRects;
    
    ofRectangle boundsA;
    ofRectangle boundsB;
    
    
    //sound
    void audioReceived 	(float * input, int bufferSize, int nChannels);
	
    float * left;
    float * right;
	
    float * autoCorrelation;
	
    bool bNormalize;
	
    void doAutoCorrelation();
	
	
    int 	bufferCounter;
    int 	drawCounter;
    
    //what i really do
    vector<ofxBox2dPolygon> corr;
    
    
};