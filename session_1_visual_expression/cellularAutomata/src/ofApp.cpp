/*
 Project Title: Cellular Automata
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // uncomment different rule sets to see different CA patterns
    rules= {0,0,0,1,1,1,1,0}; // pyramid CA
    //    rules= {0,0,1,1,0,1,1,0}; // pyramid grid CA
    //    rules= {0,1,0,1,1,0,1,0}; // pyramid dark CA
    //    rules= {1,0,1,1,0,1,1,0}; // pyramid light CA
    //    rules= {1,0,1,0,0,1,0,1}; // pyramid light CA
    
    generation = 1;
    onCol = ofColor(255);
    offCol = ofColor(0);
    ofSetFrameRate(8); // slow down the framerate
    ofSetColor(onCol);
    ofSetBackgroundColor(0);
    screenImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    screenImage.setColor(ofGetWidth()/2, 0, onCol ); // set an initial pixel to be on
    if (generation < ofGetHeight()-1){
        for(int i = 0; i<ofGetWidth()-1; i++){
            ofColor left = screenImage.getColor(i-1,generation-1) ; // get color of pixel
            ofColor me = screenImage.getColor(i,generation-1) ;
            ofColor right = screenImage.getColor(i+1,generation-1) ;
            if (applyRules(left, me, right)==1){
                screenImage.setColor(i, generation, onCol);
            }
        }
        generation++;
    }
    ofImage image;
    image.setFromPixels(screenImage);
    image.draw(0,0, ofGetWidth(),ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    screenImage.setColor(mouseX, mouseY, onCol);
}

//--------------------------------------------------------------
int ofApp::applyRules( ofColor a, ofColor b, ofColor c){
    if ((a==onCol) && (b== onCol) && c==onCol){ return rules[0];}
    if ((a==onCol) && (b== onCol) && c==offCol){ return rules[1];}
    if ((a==onCol) && (b== offCol) && c==onCol){ return rules[2];}
    if ((a==onCol) && (b== offCol) && c==offCol){ return rules[3];}
    if ((a==offCol) && (b== onCol) && c==onCol){ return rules[4];}
    if ((a==offCol) && (b== onCol) && c==offCol){ return rules[5];}
    if ((a==offCol) && (b== offCol) && c==onCol){ return rules[6];}
    if ((a==offCol) && (b== offCol) && c==offCol){ return rules[7];}
    return 0;
}
