#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxControlPanel.h"
#include "granularManager.h"


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
		
		// create a variable of the type ofImage
		ofxControlPanel			panel;
	
		int						width, height;
		ofVideoGrabber			video;
		ofxCvColorImage			colorCvImage;
		ofxCvColorImage			colorHSVCvImage;
	
		ofxCvGrayscaleImage		grayscaleHueImage;
		ofxCvGrayscaleImage		grayscaleSatImage;
		ofxCvGrayscaleImage		grayscaleBriImage;
		
		unsigned char *			grayPixels;
		ofxCvGrayscaleImage		grayscaleCvImage;

	
    ofxCvContourFinder contour;
		// for tracking...
		int hue, sat, val;

		int hueRange;
		int satRange;
		int valRange;
    
    float aspectRatio;
	
    
    
    
    void audioOut(float * input, int bufferSize, int nChannels);
	
    granularManager	GM;
	
    float * audioData;
	
	
};

#endif
