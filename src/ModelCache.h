//
//  ModelCache.h
//  pigeonBlowerUpper
//
//  Created by Will Gallia on 08/10/2015.
//
//

#pragma once

#include <string>

class ofxPhysicalOBJModel;

class ModelCache {
public:
    static ofxPhysicalOBJModel* getModel(std::string name);
    
};