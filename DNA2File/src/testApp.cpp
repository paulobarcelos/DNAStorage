#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_VERBOSE);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
	if( dragInfo.files.size() > 0 ){
		for(int k = 0; k < dragInfo.files.size(); k++){

			decode(dragInfo.files[k]);
			
		}
	}
}

void testApp::decode(string path){
	ofBuffer buffer = ofBufferFromFile(path);
	string bytes = "";
	while (!buffer.isLastLine()) {
		string line = buffer.getNextLine();
		if(!ofIsStringInString(line, PREFIX)
		   || !ofIsStringInString(line, SUFIX)
		   || line.length() != 159)
			continue;
		ofStringReplace(line, PREFIX, "");
		ofStringReplace(line, SUFIX, "");
		string bits = dnaToBits(line);
		string indexBits = bits.substr(0,19);
		reverse(indexBits.begin(), indexBits.end());
		int index = ofBinaryToInt(indexBits);
		bytes += bits.substr(19,96);
	}
	int byteLen = bytes.length() / 8;
	char * chars = new char[byteLen];
	for (int i = 0; i < byteLen; i++) {
		chars[i] = ofBinaryToChar(bytes.substr(i*8, 8));
	}
	ofBuffer decodedBuffer = ofBuffer(chars, byteLen);
	ofBufferToFile(ofFilePath::removeExt(ofFilePath::getFileName(path)), decodedBuffer);
}

string testApp::dnaToBits(string dna){
	string bits = ofToUpper(dna);
	ofStringReplace(bits, "A", "0");
	ofStringReplace(bits, "C", "0");
	ofStringReplace(bits, "G", "1");
	ofStringReplace(bits, "T", "1");
	return bits;
}

