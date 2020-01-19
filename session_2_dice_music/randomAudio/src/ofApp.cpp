#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    totalVoices = 7;
//    for (int i = 0; i< totalVoices; i++){
//        ofSoundPlayer voice;
//        string path ="choir/Eno-Choir-0" + ofToString( i+1 ) + ".wav";
//        cout << "loading " << path << endl;
//        voice.load(path);
//        voice.setMultiPlay(true);
//        voices.push_back(voice);
//    }
    
    totalVoices = 8;
    for (int i = 0; i< totalVoices; i++){
        ofSoundPlayer voice;
        string path ="piano/Eno-Piano-0" + ofToString( i+1 ) + ".wav";
        cout << "loading " << path << endl;
        voice.load(path);
        voice.setMultiPlay(true);
        voices.push_back(voice);
    }
    
    tempo = 5000; // five seconds tempo
    b_autoPlay = false;
    currTime = ofGetSystemTimeMillis();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i = 0; i < totalVoices; i++){
        ofDrawBitmapString( "voice " + ofToString( i +1 ) + ": " + ofToString( voices[i].isPlaying() ) + " " + ofToString( voices[i].getPosition() * 100 ) + " %", 10, (i + 1) * 20  );
    }
    
    //    ofDrawBitmapString("auto play is " + ofToString( b_autoPlay) , 10, 160);
    ofDrawBitmapString("tempo is " + ofToString( tempo ) + " ms" , 10, 180);
    ofDrawBitmapString("press keys 1-7 to play voices \na to autoplay \n + /- to increase/decrease tempo", 10, 200);
    
    if (b_autoPlay){
        if (ofGetSystemTimeMillis() > currTime + tempo){
            
            int num = ofRandom(totalVoices);
            voices[num].play();
            currTime = ofGetSystemTimeMillis();
            cout << "playing voice " << num << endl;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '1':
            voices[0].play();
            break;
        case '2':
            voices[1].play();
            break;
        case '3':
            voices[2].play();
            break;
        case '4':
            voices[3].play();
            break;
        case '5':
            voices[4].play();
            break;
        case '6':
            voices[5].play();
            break;
        case '7':
            voices[6].play();
            break;
            
        case '8':
            if (voices.size()>7){
               voices[7].play();
            }
            break;
        case 'a':
            b_autoPlay= !b_autoPlay;
            break;
        case '=':
        case'+':
            tempo +=500;
            break;
            
        case '-':
        case'_':
            if (tempo > 1000){
                tempo -=500;
            }
            break;
            
        default:
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
