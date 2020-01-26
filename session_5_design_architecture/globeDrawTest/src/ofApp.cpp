
/*
 Project Title: Globe Draw
 Description: generate points on the surface of a sphere using cartesian co-ordinates, then generate  curve path between each point and draw in 3D
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    globeRadius = 400;
    globe.set(globeRadius, 10);
    int maxPoints =20;
    for (int i = 0; i<maxPoints; i++){
        ofPoint newPoint = sphericalToCartesian(ofRandom(-180, 180.0), ofRandom(360.0), globeRadius);
        geoPositions.push_back(newPoint);
    }
    ofBackground(0, 0, 0);
    
    geoPath.setStrokeWidth(6);
    geoPath.setFilled(false);
    ofColor red(255,0,0);
    geoPath.setColor(red);
    light.setPosition(1000, 2000, 2000);
    cam.setPosition(0, 0, 1000);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    cam.begin();
    light.enable();
    ofSetColor(100, 255, 100); // draw wire frame sphere in green
    globe.drawWireframe();
    
    ofSetColor(200, 200, 200); //draw blobs at curve points in grey
    geoPath.clear();
    for (int i =0; i<geoPositions.size();i++){
        ofDrawSphere(geoPositions[i],  10.0);
        geoPath.curveTo(geoPositions[i]);
    }
    
    geoPath.draw();
    light.disable();
    cam.end();
    ofDisableDepthTest();
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

ofVec3f ofApp::sphericalToCartesian( float lat, float lon, float radius ){
    ofVec3f result;
    // new quaternion example
    // three rotations, two to represent the latitude and lontitude of the city
    // a third so that it spins along with the spinning sphere
    ofQuaternion latRot, longRot, spinQuat;
    lat *= -1;        // inverse latitude.
    lon += 180;        // longitude offset to match geometry of the sphere.
    latRot.makeRotate(lat, 1, 0, 0);
    longRot.makeRotate(lon, 0, 1, 0);
    spinQuat.makeRotate(0, 0, 1, 0);
    
    //our starting point is 0,0, on the surface of our sphere, this is where the meridian and equator meet
    ofVec3f center = ofVec3f(0,0,radius); // add distance above globe surface to draw to
    //multiplying a quat with another quat combines their rotations into one quat
    //multiplying a quat to a vector applies the quat's rotation to that vector
    //so to to generate our point on the sphere, multiply all of our quaternions together then multiple the centery by the combined rotation
    ofVec3f worldPoint = latRot * longRot * spinQuat * center;
    return worldPoint;
}
