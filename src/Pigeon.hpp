//
//  Pigeon.hpp
//  MidiIn
//
//  Created by Chris Cairns on 29/09/2015.
//
//

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"

class Pigeon {
    
public:
    void setup();
    int number;
    ofVec3f pos;
    
    float size;
    bool exploded;
    bool maxSizeReached;
    
    Pigeon(int n, ofVec3f p);
    
    void explode();
    
    void draw();
    
    ofxAssimpModelLoader model;
    
    //    bool bAnimate;
    //    bool bAnimateMouse;
    //    float animationPosition;
    
    ofMesh mesh;
    ofLight	light;
};