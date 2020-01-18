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
    startPoint.set(ofGetWidth()/2, ofGetHeight()/2);
    currentPoint = startPoint;
    currentLength = 0;
    velocity.set(ofRandom(1), ofRandom(1));
    velocity.scale( 1 ); // scale velocity amplitude
    amplitude = 1;
    acceleration =0;
    angularAcceleration = ofRandom(-1, 1);
    ofSetFrameRate(30);
    numDrinks = 4;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetBackgroundAuto(false);
    ofPoint nextPoint;
    //while (currentLength < length) {
        nextPoint = velocity + currentPoint;
        currentLength += amplitude;
        ofDrawLine(currentPoint, nextPoint);
        currentPoint = nextPoint;
        velocity = velocity.getRotated(angularAcceleration);
        velocity.scale(amplitude+acceleration);
        acceleration += ofRandom(-0.1, 0.1) * numDrinks;
        angularAcceleration += ofRandom(-1, 1);
    //}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
