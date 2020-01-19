/*
 Project Title: generating nGrams for markov text
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

using namespace std;


//--------------------------------------------------------------
void ofApp::setup(){
    
    gramLength = 3;
    sourceText = "I wandered lonely as a cloud That floats on high o'er vales and hills, When all at once I saw a crowd, A host, of golden daffodils; Beside the lake, beneath the trees, Fluttering and dancing in the breeze.";
    
    // force to lowercase
    std::transform(sourceText.begin(), sourceText.end(), sourceText.begin(), [](unsigned char c){ return std::tolower(c); });
    
    // remove punctuation
    for (int i = 0, len = sourceText.size(); i < len; i++)
    {
        // check whether parsing character is punctuation or not
        if (ispunct(sourceText[i]))
        {
            sourceText.erase(i--, 1);
            len = sourceText.size();
        }
    }
    
    // generate a vector of all grams
    for (int i = 0; i < sourceText.length()-gramLength; i++){
        string newGram = sourceText.substr(i, gramLength);
        allGrams.push_back(newGram);
    }
    
    // sort unique grams into new vector of grams
    vector<string> row;
    for (int i = 0; i < allGrams.size(); i++){
        row.clear();
        if ( !does_exist(uniqueGrams, allGrams[i])){
            // cout << "Item " << allGrams[i] << " is not a duplicate" << endl;
            row.push_back(allGrams[i]);
            uniqueGrams.push_back(row);
        }
    }
    
    // find all following letters to the grams
    for (int i = 0; i < uniqueGrams.size(); i ++){
        string gram = uniqueGrams[i][0];
        
        int pos = sourceText.find(gram);
        if (pos != sourceText.length()){
            // uniqueGrams[i].push_back(sourceText.substr(pos + 3, 1));
            size_t pos = sourceText.find(gram);
            // Repeat till end is reached
            while( pos != std::string::npos) {
                //           // Add position to the vector
                uniqueGrams[i].push_back(sourceText.substr(pos + 3, 1));
                cout << gram << " gram: " << sourceText.substr(pos + 3, 1) << endl;
                
                //           // Get the next occurrence from the current position
                pos =sourceText.find(gram, pos + gram.size());
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            makeText();
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

//--------------------------------------------------------------
bool ofApp::does_exist(const vector< vector<string> >&  v, string item){
    // find existence of a string in a 2D vector
    vector< vector<string> >::const_iterator row;
    for (row = v.begin(); row != v.end(); row++) {
        if(find(row->begin(), row->end(), item) != row->end() )
            return true;
    }
    return false;
}
//--------------------------------------------------------------

void ofApp::makeText(){
    string startText = "and";
    string nextLetter;
    int numLetters = 100;
    // need to fix this as it crashes if it gets to a null gram at the end (breeze)
    for (int i=0; i<numLetters; i++){
        for (int j = 0; j < uniqueGrams.size(); j++){
            if (uniqueGrams[j][0] == startText.substr(i,gramLength)){
                nextLetter = uniqueGrams[j][ofRandom(uniqueGrams[j].size()-1 ) +1 ];
                cout << nextLetter << endl;
                startText+= nextLetter;
            }
        }
    }
    cout << startText << endl;
}
