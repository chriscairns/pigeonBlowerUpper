//
//  ModelCache.cpp
//  pigeonBlowerUpper
//
//  Created by Will Gallia on 08/10/2015.
//
//

#include "ModelCache.h"

#include "ofMain.h"
#include "ofxPhysicalOBJModel.h"

map<string, shared_ptr<ofxPhysicalOBJModel> > models;

ofxPhysicalOBJModel* ModelCache::getModel(string name) {
    
    if (!models.count(name)) {
        models[name] = shared_ptr<ofxPhysicalOBJModel>(new ofxPhysicalOBJModel);
        models[name]->load(name);
        
        ofLogNotice("ModelCache") << "loaded model " << name;
    }
    
    return models[name].get();
}
