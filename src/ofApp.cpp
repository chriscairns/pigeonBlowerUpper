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
    
    Drum kickDrum = { .name = "kick", .midiNote = 0, .numberOfPigeons = 3 };
    drums.push_back(kickDrum);
    
    Drum snareDrum = { .name = "snare", .midiNote = 1, .numberOfPigeons = 2 };
    drums.push_back(snareDrum);
    
    Drum hihatDrum = { .name = "hihat", .midiNote = 2, .numberOfPigeons = 4 };
    drums.push_back(hihatDrum);
    

    ofImage img;
    // add a key for each of the drums to numberOfHits
    
    int counter = 0;
    for (Drum drum : drums) {
        numberOfHits[drum.name] = 0;
        
        for (int i = 0; i < drum.numberOfPigeons; i++) {
            pigeons[drum.name].push_back(new Pigeon(i, ofVec3f((i+1)*120, (counter+1)*120, 0)));
        }
        counter++;

    }
    
    cam.setPosition(124.101639, 431.887573, 924.459777);
    
}

//--------------------------------------------------------------
void ofApp::update() {
    ofSetWindowTitle( ofToString( ofGetFrameRate(),1 ) );
    
    for (auto &pigeonElement : pigeons) {
        auto pigeonList = pigeonElement.second;
        for (auto &pigeon : pigeonList) {
            pigeon->update();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(150,10,10);
	
    cam.begin();

    
    for (auto &pigeonElement : pigeons) {
        auto pigeonList = pigeonElement.second;
        for (auto &pigeon : pigeonList) {
            pigeon->draw();
        }
    }
    
    cam.end();
    
//    this is a new line
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
        for (auto &hitElement : numberOfHits) {
            hitElement.second = 0;
        }
        
        for (auto &pigeonElement : pigeons) { // loop through each of the drums with pigeons
            auto pigeonList = pigeonElement.second;
            for (auto &pigeon : pigeonList) { // loop through all the pigeons for this drum
                pigeon->reset();
            }
        }
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
