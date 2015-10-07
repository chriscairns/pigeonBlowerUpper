//
//  Pigeon.cpp
//  MidiIn
//
//  Created by Chris Cairns on 29/09/2015.
//
//

#include "Pigeon.hpp"


//void Pigeon::setup(){
//
//    model.loadModel("pigeonExplosion.dae", true);
//    model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.8 , 0);
//    ofEnableSeparateSpecularLight();
//}

Pigeon::Pigeon(int n, ofVec3f p) {
    number = n;
    pos = p;
    size = 60;
    exploding = false;
    maxSizeReached = false;
    
    objName = "pigeon.obj";
    reset();
}


void Pigeon::explode() {
    exploding = true;
    explodeMesh();
}

void Pigeon::draw() {
    
    ofPushMatrix();
    ofTranslate(pos);
    getVboMesh()->draw();
    ofPopMatrix();
    
}



void Pigeon::reset() {
    
    ofxPhysicalOBJModel::load(objName);


    int d = 3;
    paintPoints.clear();
    for (int i = 0; i < 50; i++) {
        ofVec3f v(ofRandom(-d, d), ofRandom(-d, d), ofRandom(-d, d));
        v+= modelCenter;
        paintPoints.push_back(v);
    }
    paintAlpha = 255;
}


void Pigeon::update() {
    
    if (exploding) {
    
        ofxPhysicalOBJModel::update();
        

        for (auto &point : paintPoints) {
            point+= (point - modelCenter).getNormalized() * 0.5;
        }
        
        paintMesh.clear();
        paintMesh.addVertices(paintPoints);
        if (paintAlpha > 0) paintAlpha-= 5;
        
        if (!inMotion()) {
            exploding = false;
            cout << "exploding = false\n";
        }
    }
}


