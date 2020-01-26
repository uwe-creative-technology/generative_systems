
/*
 Project Title: Globe Draw
 Description: generate points on the surface of a sphere using cartesian co-ordinates, then generate  curve path between each point and draw in 3D
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#pragma once

#include "ofMain.h"
#include "ofxVectorGraphics.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);

		
    ofVec3f sphericalToCartesian( float lat, float lon, float radius );
    ofSpherePrimitive globe;
    int globeRadius;
    ofEasyCam   cam;
    vector<ofPoint> points, geoPositions;
    ofxVectorGraphics vectorGraphics;
    ofPath geoPath;
    ofLight light;
    
};
