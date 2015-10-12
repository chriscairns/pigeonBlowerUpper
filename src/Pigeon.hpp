//
//  Pigeon.hpp
//  MidiIn
//
//  Created by Chris Cairns on 29/09/2015.
//
//

#pragma once

#include "ofMain.h"
#include "ofVboMesh.h"

#include "ofxPhysicalOBJModel.h"

class Pigeon {
public:
    Pigeon(int n, ofVec3f p);

    void setup();
    void reset();
    void update();
    void explode();
    void draw();
    
    int number;
    ofVec3f pos;
    
    float size;
    bool exploding;
    bool maxSizeReached;
    
    string objName;
    
    ofMesh mesh;
    ofLight	light;
    
    ofxPhysicalOBJModel model;
    
protected:
    vector<ofVec3f> paintPoints;
    ofVboMesh paintMesh;
    int paintAlpha;
    
  
    
};