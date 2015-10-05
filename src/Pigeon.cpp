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
    exploded = false;
    maxSizeReached = false;
}


void Pigeon::explode() {
    exploded = true;
    
//    cout << "exploding pigeon number " << number << endl;
}

void Pigeon::draw() {
    
    if (exploded && !maxSizeReached && size < 250) {
        size*= 5;
//        size+= 10;
    }
    
    if (size >= 250) {
        maxSizeReached = true;
    }
    
    if (maxSizeReached && size > 60){
        size/= 1.5;
        
        if (size <= 60) {
            size = 60;
            exploded = false;
            maxSizeReached = false;
        }
        
        
        
//        size-= 20;
    }
    
//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//    
//    ofEnableDepthTest();
//    
//    glShadeModel(GL_SMOOTH); //some model / light stuff
//    light.enable();
//    ofEnableSeparateSpecularLight();
//    
//    model.drawFaces();
//    
//    
//    if(ofGetGLProgrammableRenderer()){
//        glPushAttrib(GL_ALL_ATTRIB_BITS);
//        glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
//    }
//    glEnable(GL_NORMALIZE);
//    
//    ofxAssimpMeshHelper & meshHelper = model.getMeshHelper(0);
//    
//    ofMultMatrix(model.getModelMatrix());
//    ofMultMatrix(meshHelper.matrix);
//    
//    ofMaterial & material = meshHelper.material;
//    if(meshHelper.hasTexture()){
//        meshHelper.getTextureRef().bind();
//    }
//    material.begin();
//    //  mesh.drawWireframe();
//    material.end();
//    if(meshHelper.hasTexture()){
//        meshHelper.getTextureRef().unbind();
//    }
//    ofPopMatrix();
//    
//    if(ofGetGLProgrammableRenderer()){
//        glPopAttrib();
//    }
//    
//    ofDisableDepthTest();
//    light.disable();
//    ofDisableLighting();
//    ofDisableSeparateSpecularLight();
//    
//    ofSetColor(255, 255, 255 );
//    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);
//    ofDrawBitmapString("keys 1-5 load models, spacebar to trigger animation", 10, 30);
//    ofDrawBitmapString("drag to control animation with mouseY", 10, 45);
//    ofDrawBitmapString("num animations for this model: " + ofToString(model.getAnimationCount()), 10, 60);
//}
//    ofNoFill();
//    ofSetColor(120, 180, 100);
    ofRect(pos.x, pos.y, size, size);
//    ofSetColor(255, 10, 10);
//    ofRect(pos.x, pos.y, size, size);
}