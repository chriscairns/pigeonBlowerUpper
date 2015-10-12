//
//  Pigeon.cpp
//  MidiIn
//
//  Created by Chris Cairns on 29/09/2015.
//
//

#include "Pigeon.hpp"

#include "ModelCache.h"

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
    model.explodeMesh();
}

void Pigeon::draw() {
    
    ofPushMatrix();
    ofTranslate(pos);
    model.getVboMesh()->draw();
    ofPopMatrix();
    
}



void Pigeon::reset() {
    
//    ofxPhysicalOBJModel::load(objName);
    
    model = ofxPhysicalOBJModel(*ModelCache::getModel(objName));
    
//    auto m = ModelCache::getModel(objName);
//    
//    model.clear();
//    for (auto group : m->groups) {
//        model.addGroup(group);
//    }
//
//    
//    model.vertices.resize(m->vertices.size());
//    copy(m->vertices.begin(), m->vertices.end(), model.vertices.begin());
//    
//    model.normals.resize(m->normals.size());
//    copy(m->normals.begin(), m->normals.end(), model.normals.begin());
//    
//    model.texCoords.resize(m->texCoords.size());
//    copy(m->texCoords.begin(), m->texCoords.end(), model.texCoords.begin());
    
    
    
    int d = 3;
    paintPoints.clear();
    for (int i = 0; i < 50; i++) {
        ofVec3f v(ofRandom(-d, d), ofRandom(-d, d), ofRandom(-d, d));
        v+= model.modelCenter;
        paintPoints.push_back(v);
    }
    paintAlpha = 255;
}


void Pigeon::update() {
    
    if (exploding) {
    
        model.update();
        

        for (auto &point : paintPoints) {
            point+= (point - model.modelCenter).getNormalized() * 0.5;
        }
        
        paintMesh.clear();
        paintMesh.addVertices(paintPoints);
        if (paintAlpha > 0) paintAlpha-= 5;
        
        if (!model.inMotion()) {
            exploding = false;
            cout << "exploding = false\n";
        }
    }
}


