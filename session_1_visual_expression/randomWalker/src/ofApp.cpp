/*
 Project Title: randomWalker
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
    walker.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    walker.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
walker::walker(){
    xyPoint = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    walk.push_back(xyPoint);
    color = (255);
    radius = 1;
}

//--------------------------------------------------------------
walker::~walker(){
    
}

//--------------------------------------------------------------
void walker::update(){
    int random = ofRandom(4);
    switch (random) {
        case 0: // up
            xyPoint += ofVec2f(0, 1);
            break;
        case 1: // down
            xyPoint += ofVec2f(0, -1);
            break;
        case 2: // right
            xyPoint += ofVec2f(1, 0);
            break;
        case 3: // left
            xyPoint += ofVec2f(-1, 0);
            break;
            
        default:
            break;
    }
    walk.push_back(xyPoint);
}

//--------------------------------------------------------------
void walker::draw(){
    ofSetColor( color);

    for (int i=0; i<walk.size(); i++){
        ofDrawCircle(walk[i], radius);
    }
}
