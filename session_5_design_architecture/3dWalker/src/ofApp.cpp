/*
Project Title: 3d walker plotting paths in higher dimensional stochastic space
Description:
©Daniel Buzzo 2020
dan@buzzo.com
http://buzzo.com
https://github.com/danbz
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    numOfWalkers = 1;
    b_drawGui = true; // boolean variable to indicate whether or not to show the gui display
    ofSetBackgroundColor(0, 0, 0);
    b_autoRotate = b_addstagger =  false;
    rotAngle = 0.0;
    ofSetFrameRate(120);
    
    for (int i=0; i<numOfWalkers;i++){
        walker newWalker; // create a walker and push into our vector of walkers
        walkers.push_back(newWalker);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if (b_addstagger){
        for (int i=0; i < walkers.size(); i++){
            walkers[i].addStagger();
        }
    }
    if (b_autoRotate){
        rotAngle +=0.1 ;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofVec3f curStep, prevStep(0.0,0.0,0.0);
    ofEnableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofColor wfColor(50,50,50,150);
    glPointSize(5);
    
    // light.enable();

    cam.begin(); // begin using our easyCam objectfor 3D viewing
    ofPushMatrix();
    ofRotateYDeg(rotAngle);
    for (int i=0; i<walkers.size();i++){ // iterate though all the values in our vector of steps/points
        ofSetColor(walkers[i].color);
        if (b_renderMesh) {
            walkers[i].mesh.draw();
            
            ofSetColor(walkers[i].color + wfColor);
            walkers[i].mesh.drawWireframe();
        } else {
            //  ofSetColor(walkers[i].color + wfColor);
            walkers[i].mesh.drawWireframe();
            walkers[i].mesh.drawVertices();
        }
    }
    ofPopMatrix();
    cam.end(); // end using our easyCam object
    
    //  light.disable();
    
    ofSetColor(150, 150, 150);
    if (b_drawGui){ // check if we should show the onscreen gui/text
        ofDrawBitmapString(" 'w' to toggle walks, 'r' to autoRotate, 'f' fullscreen, 'g' hide text, 'm' toggle mesh/pointcloud render\nfps: " + ofToString(ofGetFrameRate())  + "\niteration number "+ ofToString(walkers[0].steps.size()), 10, 10);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
            
        case 'r':
            b_autoRotate=!b_autoRotate;
            break;
            
        case 'w':
            b_addstagger=!b_addstagger;
            break;
            
        case 'f':
            ofToggleFullscreen(); // toggle full screen display
            break;
            
        case 'g':
            b_drawGui = !b_drawGui; //toggle the guid overlay on and off
            break;
            
        case 'm':
            b_renderMesh = !b_renderMesh;
            break;
            
    }
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
walker::walker(){ // constructor
    staggerSize =40; // set how far to stagger when we add staggers to the walk of points
    ofVec3f new3dpoint(ofRandom(-staggerSize, staggerSize),ofRandom(-staggerSize, staggerSize),ofRandom(-staggerSize, staggerSize));
    steps.push_back(new3dpoint);
    verticalMotion = 0.0f;
    maxLineWidth =40;
    lineWidth.push_back(5);
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 150);
    //mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    randomKey = ofRandom( 1000 );
    twistiness = 1; // scale for step through perlin noise space - 0.1-5.0 is good, more = more twisty
    
    // for building rings
    pie = 3.14159;
    tubeMeshRes = 36;
    radius = 40.0;
    tubeHeight = 0;
    tubeHeightStep = (1.0 * pie * radius) / tubeMeshRes ;
    
}

//--------------------------------------------------------------
walker::~walker(){
    // destructor
}

//--------------------------------------------------------------
void walker::addStagger(){
    // generate a new small step/stagger that is within +/- our staggerSize distance of the last step
    ofVec3f lastStep = steps[steps.size()-1];
    ofVec3f newStep;
    
    // time noise walk - generate a noisy 3d position over time
    float t = randomKey + ( ofGetElapsedTimef()) * twistiness;
    newStep.x = ofSignedNoise(t, 0, 0);
    newStep.y = ofSignedNoise(0, t, 0);
    newStep.z = ofSignedNoise(0, 0, t);
    newStep *= ofRandom(staggerSize); // scale from -1,+1 range to -400,+400
    newStep += lastStep;
    
    steps.push_back(newStep); // add a new step to the end of our vector of steps
    lineWidth.push_back( ofNoise(randomKey +  ofGetElapsedTimef() ) * maxLineWidth);
    
    // mesh based line draw - elements from mouse draw oF example
    // get the direction from one to the next. the ribbon should fan out from this direction
    ofVec3f direction = (newStep - lastStep);
    
    // get the distance from one point to the next
    float distance = direction.length();
    
    // get the normalized direction. normalized vectors always have a length of one
    // and are really useful for representing directions as opposed to something with length
    ofVec3f unitDirection = direction.getNormalized();
    
    // find both directions to the left and to the right
    ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
    ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
    
    // find both directions to the left and to the right
    ofVec3f toTheTop = unitDirection.getRotated(0, ofVec3f(0,0,1));
    ofVec3f toTheBtm = unitDirection.getRotated(180, ofVec3f(0,0,1));
    
    float thickness = ofNoise(randomKey +  ofGetElapsedTimef() * twistiness) * maxLineWidth;
    thickness = 50;
    // calculate the points to the left and to the right
    // by extending the current point in the direction of left/right by the length
    ofVec3f leftPoint = lastStep+toTheLeft*thickness;
    ofVec3f rightPoint = lastStep+toTheRight*thickness;
    
    ofVec3f topPoint = lastStep+toTheTop*thickness;
    ofVec3f btmPoint = lastStep+toTheBtm*thickness;
    // addRing();
    // add these points to the triangle strip
    // fix the winding in the vertex list !
    
    mesh.addVertex(ofVec3f(topPoint));
    mesh.addVertex(ofVec3f(rightPoint));
    mesh.addVertex(ofVec3f(btmPoint));
    mesh.addVertex(ofVec3f(leftPoint));
    // triangulate mesh
    int indexAmnt = mesh.getNumVertices();
    if (indexAmnt >4) {
        // top
        mesh.addIndex(indexAmnt -7);
        mesh.addIndex(indexAmnt -6) ;
        mesh.addIndex(indexAmnt-2);
        
        mesh.addIndex(indexAmnt -7);
        mesh.addIndex( indexAmnt -2);
        mesh.addIndex( indexAmnt -3);
        
        //        // right
                mesh.addIndex(indexAmnt -6);
                mesh.addIndex( indexAmnt -5);
                mesh.addIndex(indexAmnt-1);
        
                mesh.addIndex(indexAmnt -6);
                mesh.addIndex( indexAmnt -1);
                mesh.addIndex( indexAmnt -2);
        // btm
        mesh.addIndex(indexAmnt -5);
        mesh.addIndex( indexAmnt -4);
        mesh.addIndex(  indexAmnt);
        
        mesh.addIndex(indexAmnt -5);
        mesh.addIndex( indexAmnt );
        mesh.addIndex( indexAmnt -1);
        // left
                mesh.addIndex(indexAmnt -4);
                mesh.addIndex( indexAmnt -7);
                mesh.addIndex(  indexAmnt-3);
        
                mesh.addIndex(indexAmnt -4);
                mesh.addIndex( indexAmnt -3);
                mesh.addIndex(indexAmnt );
    }
}

void walker::addRing() {
    // add a ring of vertices to our mesh
    int i,x,y,z, w, h, left, right;
    float angle =0.0;
    float p;
    
    ofVec3f radPoint;
    ofColor col;
    z = 0;
    left = w / 4 * 1;
    right = w / 4 * 3;
    
    radPoint.set(ofVec3f( 10,0,tubeHeight ));
    x=100; // guess a value here for now.... is a magic number so really bad practice!
    int stepAngle = 360 / tubeMeshRes ;
    for (p =0; p < 2 * pie; p+= 2 * pie / tubeMeshRes) {
        int input = ofMap(p, 0, 2 * pie, 0, 50);
        // radius = fftSmoothed[input] *  200;
        
        angle = stepAngle * p;
        radPoint = ofVec3f(  radius * cos( angle ), radius * sin( angle ), 0 - tubeHeight * tubeHeightStep);
        //radPoint = ofVec3f(  p, angle, tubeHeight * 10 ); // make a straight sheet of points
        mesh.addVertex(radPoint);
        
        
        if (z < tubeMeshRes/2) {         // extract appropriate color from video
            x = left; //left hand side pixels
            y = h / tubeMeshRes * (z * 2);
        } else {
            x = right; //right hand side pixels
            y = h * 2 - (h / tubeMeshRes * (z * 2) ) ;
        }
        z++;
        mesh.addColor(color);
    }
    tubeHeight ++;
}

void walker::triangulateMesh(  ){
    int meshW = tubeMeshRes ;
    int meshH = tubeHeight;
    int step =1;
    int width = meshW;
    int height = meshH;
    int index =0;
    ofVec3f v3, v3b;
    
    for (int y = 0; y<height-step-1; y+= step){ // triangulate mesh
        for (int x=0; x<width-step-1; x+= step){
            v3.set(0,0,0);

            v3 = mesh.getVertex(index);
            v3b = mesh.getVertex(index+1);
            index ++;

            mesh.addIndex(x+y*meshW);               // 0
            mesh.addIndex((x+1)+y*meshW);           // 1
            mesh.addIndex(x+(y+1)*meshW);           // 10
 
            mesh.addIndex((x+1)+y*meshW);           // 1
            mesh.addIndex((x+1)+(y+1)*meshW);       // 11
            mesh.addIndex(x+(y+1)*meshW);           // 10
        }
    }
}
