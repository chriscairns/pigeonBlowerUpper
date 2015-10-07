//
//  Tools.h
//  pigeonBlowerUpper
//
//  Created by Will Gallia on 07/10/2015.
//
//

#pragma once

#include "ofMain.h"

// returns a map of the first vertex of each group in an OBJ file
// useful if you don't want to load  a huge OBJ file, as the magic is done by grep
inline map<string, ofVec3f> positionsFromOBJ(string file) {
    
    string path = ofToDataPath(file);
    
    // find groups and the next line (i.e. the first vertex)
    string command("grep -A 1 'g ' ");
    command+= path;
    command+= " | grep -v '^--$'";
    
    
    map<string, ofVec3f> output;
    
    istringstream stream(ofSystem(command));
    string line, lastKey;
    
    while (getline(stream, line)) {
        if (line.find("g ") == 0) {
            lastKey = line.substr(2);
            
            // remove \n
            lastKey = lastKey.erase(lastKey.length() - 1);
            
        }
        else if (line.find("v ") == 0) {
            ofVec3f p;
            vector<string> elements = ofSplitString(line.substr(2), " ");
            if(elements.size()<2) {
                printf("Error line does not have at least 2 coordinates: \"%s\"\n", line.c_str());
            }
            p.x = atof(elements[0].c_str());
            p.y = atof(elements[1].c_str());
            if(elements.size()>=3) {
                p.z = atof(elements[2].c_str());
            }
            
            output[lastKey] = p;
        }
    }
    
    return output;
}
