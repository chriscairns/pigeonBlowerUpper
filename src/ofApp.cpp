/*
 * Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxMidi for documentation
 *
 */
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofBackground(255, 255, 255);
	//ofSetLogLevel(OF_LOG_VERBOSE);
	
	// print input ports to console
	midiIn.listPorts(); // via instance
	//ofxMidiIn::listPorts(); // via static as well
	
	// open port by number (you may need to change this)
	midiIn.openPort(1);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add ofApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(true);
    
    drums.push_back(Drum("kick", 0));
    drums.push_back(Drum("snare", 1));
    drums.push_back(Drum("hihat", 2));
    
    // add a key for each of the drums to numberOfHits
    
    int counter = 0;
    for (Drum drum : drums) {
        numberOfHits[drum.name] = 0;
        
        for (int i = 0; i < NUM_PIGEONS_PER_DRUM; i++) {
            pigeons[drum.name].push_back(new Pigeon(i, ofVec3f((i+1)*120, (counter+1)*120, 0)));
        }
        counter++;

    }
    
    numberOfNoteOns = 0;
//    numberOfKicks = 0;
//    numberOfSnares = 0;
    
//   drums.push_back("snare");
//   drums.push_back("kick");
//   drums.push_back("tom");
    
//    for (string drum : drums) {
    
//    vector<Pigeon> snarePigeons;
//    for (int i = 0; i < 11; i++) {
//           snarePigeons.push_back(i);
//      }
//  }
  
    
    
//    for (int i = 0; i < NUM_PIGEONS_PER_DRUM; i++) {
//        kickPigeons.push_back(Pigeon(i, ofVec3f((i+1)*120, 120, 0)));
//    }
//    
//    for (int i = 0; i < NUM_PIGEONS_PER_DRUM; i++) {
//        snarePigeons.push_back(Pigeon(i, ofVec3f((i+1)*120, 240, 0)));
//    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::update() {
    ofSetWindowTitle( ofToString( ofGetFrameRate(),1 ) );
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(150,10,10);
	
    
//    for (int i = 0; i < kickPigeons.size(); i++) {
//        kickPigeons[i].draw();
//    }
//    
//    ofSetColor(10,150,10);
//    for (int i = 0; i < snarePigeons.size(); i++) {
//        snarePigeons[i].draw();
//    }
    
    for (auto &pigeonElement : pigeons) {
        auto pigeonList = pigeonElement.second;
        for (auto &pigeon : pigeonList) {
            pigeon->draw();
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::exit() {
	
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
    
    // delete all the pigeons
    
    for (auto &pigeonElement : pigeons) { // loop through each of the drums with pigeons
        auto pigeonList = pigeonElement.second;
        for (auto &pigeon : pigeonList) { // loop through all the pigeons for this drum
            delete pigeon;
        }
    }
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {

	// make a copy of the latest message
	midiMessage = msg;
    
//    cout << "pitch: " << msg.pitch << endl;
//    cout << "velocity: " << msg.velocity << endl;
    
    printf("status: %d, pitch: %d, velocity: %d\n", msg.status, msg.pitch, msg.velocity);
    
    if (msg.status == MIDI_NOTE_ON && msg.velocity != 0) {
        
        for (Drum &drum : drums) {
            if (drum.midiNote == msg.pitch) {
                
                // if we get here we're on the right drum for the current note that's been played
                int hitsSoFar = numberOfHits[drum.name];
                
                if (hitsSoFar < pigeons[drum.name].size()) {
                    pigeons[drum.name][hitsSoFar]->explode();
                    numberOfHits[drum.name]++;
                }
            }
        }
        
        
        
        
//        numberOfNoteOns ++;
//        
//        printf("number of midi messages received so far: %d\n", numberOfNoteOns);
//        
//        if (msg.pitch == 0) {
//            if(numberOfHits["kick"] < kickPigeons.size()){
////            cout << "we see pigeon number " << numberOfKicks << " explode" << endl;
////                printf("we see kickPigeon number %d explode\n", numberOfKicks);
//                kickPigeons[numberOfHits["kick"]].explode();
//                numberOfHits["kick"] ++;
//                printf("number of kicks received so far: %d\n", numberOfHits["kick"] );
//            }
//        }
//
//        else if (msg.pitch == 2) {
//            if(numberOfHits["snare"] < snarePigeons.size()){
////                printf("we see snarePigeon number %d explode\n", numberOfSnares);
//                snarePigeons[numberOfHits["snare"]].explode();
//                numberOfHits["snare"] ++;
//                printf("number of snares received so far: %d\n", numberOfHits["snare"] );
//
//            }
//        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	switch(key) {
		case 'l':
			midiIn.listPorts();
			break;
	}
    
    if(key == 'r'){
        numberOfKicks = 0;
        numberOfSnares = 0;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased() {
}
