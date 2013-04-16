#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofEnableAlphaBlending();
	// setup video grabber:
	video.initGrabber(320, 240);
	
	// get the width and height, and allocate color and grayscale images: 
	width = video.width; 
	height = video.height;
	
	colorCvImage.allocate(width, height);
	colorHSVCvImage.allocate(width, height);
	
	grayscaleHueImage.allocate(width, height);
	grayscaleSatImage.allocate(width, height);
	grayscaleBriImage.allocate(width, height);
	
	grayscaleCvImage.allocate(width, height);
	
	grayPixels = new unsigned char [width * height];
	
	// set background color to be white: 
	ofBackground(0);
	
	
	panel.setup("cv settings", ofGetWidth()-250, 0, 250, 500);
	panel.addPanel("control", 1, false);
	
	panel.setWhichPanel("control");
	panel.setWhichColumn(0);
	
//	panel.addToggle("video settings", "VIDEO_SETTINGS", false);
	
	panel.addSlider("hue range ", "HUERANGE", 20, 0, 255, true);
	panel.addSlider("sat range ", "SATRANGE", 30, 0, 255, true);
	panel.addSlider("val range ", "VALRANGE", 25, 0, 255, true);
    
    
	panel.addSlider("min blob size ", "MIN_BLOB_SIZE", 100, 0, width*height, true);
	panel.addSlider("max blob size ", "MAX_BLOB_SIZE", 10000, 0, width*height, true);
	panel.addSlider("max num blobs to find ", "N_BLOBS_CONSIDERED", 3, 0, 20, true);
	
	panel.loadSettings("cvSettings.xml");
	
	
	hueRange = 20;
	satRange = 30;
	valRange = 25;
	
	hue = 0;
	sat = 0;
	val = 0;
    
    aspectRatio = 240/320;
	
    
    
    
    ofSoundStreamSetup(2,0,this, 44100, 1024, 4);
    
	//sinOsc.setup();
	
	audioData = new float[1024];
}

//--------------------------------------------------------------
void testApp::update(){
		
    GM.idle();
	panel.update();
	
	
	hueRange			= panel.getValueI("HUERANGE");
	satRange			= panel.getValueI("SATRANGE");
	valRange			= panel.getValueI("VALRANGE");
	int minBlobSize			= panel.getValueI("MIN_BLOB_SIZE");
	int maxBlobSize			= panel.getValueI("MAX_BLOB_SIZE");
	int nBlobsConsidered	= panel.getValueI("N_BLOBS_CONSIDERED");
	
	
//	if (panel.getValueB("VIDEO_SETTINGS") == true){
//		video.videoSettings();
//		panel.setValueB("VIDEO_SETTINGS", false);
//	}
	
	
	video.update();
	
	if (video.isFrameNew()){
		
		colorCvImage.setFromPixels(video.getPixels(), width, height);
		colorHSVCvImage = colorCvImage;
		colorHSVCvImage.convertRgbToHsv();
		
		colorHSVCvImage.convertToGrayscalePlanarImages(grayscaleHueImage, grayscaleSatImage, grayscaleBriImage);
		
		grayscaleHueImage.flagImageChanged();		// this is fixing a bug in OF 0.06
		grayscaleSatImage.flagImageChanged();
		grayscaleBriImage.flagImageChanged();
		
		
		unsigned char * colorHsvPixels = colorHSVCvImage.getPixels();
		
		for (int i = 0; i < width*height; i++){
			
				// since hue is cyclical:
				int hueDiff = colorHsvPixels[i*3] - hue;
				if (hueDiff < -127) hueDiff += 255;
				if (hueDiff > 127) hueDiff -= 255;
			
			
				if ( (fabs(hueDiff) < hueRange) &&
					(colorHsvPixels[i*3+1] > (sat - satRange) && colorHsvPixels[i*3+1] < (sat + satRange)) &&
					(colorHsvPixels[i*3+2] > (val - valRange) && colorHsvPixels[i*3+2] < (val + valRange))){
	
					grayPixels[i] = 255;
		
				} else {
					
					grayPixels[i] = 0;
				}
				
			}
			
			grayscaleCvImage.setFromPixels(grayPixels, width, height);
            contour.findContours(grayscaleCvImage, minBlobSize, maxBlobSize, nBlobsConsidered, false, true);
		
							
								
	}
    
    // call blobs
//    for(int i = 0; i < contour.nBlobs; i++) {
//        ofxCvBlob blob = contour.blobs.at(i);
//        // do something fun with blob
//    }
    
    // blob properties
//    float               area;
//    float               length;
//    ofRectangle         boundingRect;
//    ofPoint             centroid;
//    bool                hole;
//    
//    vector <ofPoint>    pts;    // the contour of the blob
//    int                 nPts;

    if (contour.nBlobs>0) {
        cout<< contour.blobs.at(0).length<< endl;
        GM.avgFrequency         = ofMap(contour.blobs.at(0).area, 0, 20000, 30, 1000);
        GM.avgFrequencySpread   = contour.blobs.at(0).boundingRect.width;
        GM.avgGrainLength       = contour.blobs.at(0).length;
        GM.avgGrainLengthSpread = contour.blobs.at(0).nPts;
        GM.avgVolume            = ofMap(contour.blobs.at(0).boundingRect.height, 0, ofGetHeight(), 0.01, 0.8);
        GM.avgVolumeSpread      = ofMap(contour.blobs.at(0).centroid.x, 0, ofGetWidth(), 0.001, 0.3);
//        GM.grainsPerSecond    = ofMap(contour.blobs.at(0).centroid.y, 0, ofGetHeight(), 1.0, 5.0);
    }
    
    
    //granular variables
//        GM.avgFrequency         += min 30 play 10;
//        GM.avgFrequencySpread   += min 0  play 10;
//        GM.avgGrainLength       += min 0  play 1;
//        GM.avgGrainLengthSpread += min 0  play 1;
//        GM.avgVolume            += min 0  play 0.01f;
//        GM.avgVolumeSpread      += min 0  play 0.001f;
//        GM.grainsPerSecond      += min 0  play 1;
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofSetColor(255, 255, 255);
//	videoColorHSVCvImage.draw(320+20, 0, 320, 240);
//	videoGrayscaleHueImage.draw(0,240+20);
//	videoGrayscaleSatImage.draw(320,240+20);
//	videoGrayscaleBriImage.draw(640,240+20);
	
	grayscaleCvImage.draw(0,0,1280,960);
    
    ofColor selectedColor;
    selectedColor.setHsb(hue, sat, val);
    contour.c2 = selectedColor;
    contour.c1 = ofColor::gray;
    
    contour.draw(0,0,1280,960);
    ofSetColor(255,100);
	colorCvImage.draw(0,0, 160,120);
//	videoGrayscaleCvImage.draw(0,0,ofGetWidth(),ofGetWidth()/aspectRatio);
	
	panel.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key=='f') {
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
	panel.mouseDragged(x,y,button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	panel.mousePressed(x,y,button);
	
	if (x >= 0 && x < 160 && y >= 0 && y < 120){
		int pixel = y*2 * 320 + x*2;
		hue = grayscaleHueImage.getPixels()[pixel];
		sat = grayscaleSatImage.getPixels()[pixel];
		val = grayscaleBriImage.getPixels()[pixel];
		
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	panel.mouseReleased();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){
	
	for (int i = 0; i < bufferSize; i++){
		output[i*nChannels    ] = 0;
		output[i*nChannels + 1] = 0;
	}
	
	GM.addToSoundBuffer(output, bufferSize);
	
	for (int i = 0; i < bufferSize; i++){
		audioData[i] = output[i*2]*0.8f;
	}
	
}



