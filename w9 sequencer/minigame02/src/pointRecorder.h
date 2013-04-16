//
//  pointRecorder.h
//  minigame02
//
//  Created by Firm Read on 4/16/13.
//
//

#ifndef __minigame02__pointRecorder__
#define __minigame02__pointRecorder__

#include <iostream>
#include "fmOscillator.h"
#include "particle.h"

typedef struct {
	ofPoint		pos;
	float		time; // from the start, what time does this pt occur at
} timePt;


class pointRecorder {
    
public:
	
    pointRecorder();
	
    void addPoint(ofPoint pt);
    void clear();
    void draw();
	
	//sound stuff - - --
    void addToSoundBuffer(float * buffer, int bufferSize);
    fmOscillator		tone;
    
    float				startTime;
    int					maxNumPts;
    vector <timePt>		pts;
    
	
    float				newStartTime; //for playback
    float				totalDuration; // the total life of the line
    bool				lineComplete; // for knowing that a line has finished drawing
    ofPoint				mostRecentPoint; // the most recent point drawn during playback
	
    float				oldPointDist; //the distance to the previous y point, used for modulator strength
	
    int					mostRecentPointIndex; // the index of the most recent Point in pts (useful for fading the volume at the beginning and end of a gesture)
    
    int					startY, startX; // the starting point of the rect, used to calculate the modulator frequency
    
    
    ofPoint smoothedTouch,prevTouch;
    
};
#endif /* defined(__minigame02__pointRecorder__) */
