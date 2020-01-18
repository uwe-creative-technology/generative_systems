/*
 Project Title: Drunken Ant path
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 adapted from example by Carl Lostrito in 'Computational Drawing'
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    resetAnt();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundAuto(false);
    ofPoint nextPoint;
    nextPoint = velocity + currentPoint;
    currentLength += amplitude;
    ofDrawLine(currentPoint, nextPoint);
    currentPoint = nextPoint;
    velocity = velocity.getRotated(angularAcceleration);
    velocity.scale(amplitude+acceleration);
    acceleration += ofRandom(-0.1, 0.1) * numDrinks;
    angularAcceleration += ofRandom(-1, 1);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 'r':
            resetAnt();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::resetAnt(){
    startPoint.set(ofGetWidth()/2, ofGetHeight()/2);
    currentPoint = startPoint;
    currentLength = 0;
    velocity.set(ofRandom(1), ofRandom(1));
    velocity.scale( 1 ); // scale velocity amplitude
    amplitude = 1;
    acceleration =0;
    angularAcceleration = ofRandom(-1, 1);
    ofSetFrameRate(60);
    numDrinks = 4;
    
    ofBackground(255);
    ofSetColor(0);
}
