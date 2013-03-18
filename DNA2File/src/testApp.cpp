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
	
	// generate map
	string PREFIX_PRIMER_string = PREFIX_PRIMER;
	string SUFIX_PRIMER_string = SUFIX_PRIMER;
	int requiredSegmentLenght = SEGMENT_LENGHT*8;
	int requiredLineLenght = PREFIX_PRIMER_string.length() + MAX_OLIGOS + requiredSegmentLenght + SUFIX_PRIMER_string.length();
	
	map<int, vector<string> > segmentMap;
	
	while (!buffer.isLastLine()) {
		string line = buffer.getNextLine();
		if(!ofIsStringInString(line, PREFIX_PRIMER)
		   || !ofIsStringInString(line, SUFIX_PRIMER)
		   || line.length() != requiredLineLenght)
			continue;
		ofStringReplace(line, PREFIX_PRIMER, "");
		ofStringReplace(line, SUFIX_PRIMER, "");
		string bits = dnaToBits(line);
		string indexBits = bits.substr(0, MAX_OLIGOS);
		reverse(indexBits.begin(), indexBits.end());
		int index = ofBinaryToInt(indexBits);
		string segment = bits.substr(MAX_OLIGOS, requiredSegmentLenght);
		if(!segmentMap.count(index)) segmentMap[index] = vector<string>();
		segmentMap[index].push_back(segment);
		
	}
	
	// evaluate final bytes
	int realIndex = 0;
	string bytes = "";
	string emptySegment;
	for (int i = 0; i < requiredSegmentLenght; i++) emptySegment += "0";
	for(map<int, vector<string> >::const_iterator iterator = segmentMap.begin(); iterator != segmentMap.end(); ++iterator){
		int index = iterator->first;
		// fill possible blanks with null
		while (realIndex != index) {
			bytes += emptySegment;
			realIndex++;
		}
		// get the "consensus" segment
		bytes += getConsensus(iterator->second);
		
		realIndex++;
	}
	
	int byteLen = bytes.length() / 8;
	char * chars = new char[byteLen];
	
	for (int i = 0; i < byteLen; i++) {
		chars[i] = ofBinaryToChar(bytes.substr(i*8, 8));
	}
	ofBuffer decodedBuffer = ofBuffer(chars, byteLen);
	ofFileDialogResult saveFileResult = ofSystemSaveDialog(ofFilePath::removeExt(ofFilePath::getFileName(path)), "Save your file");
	if (saveFileResult.bSuccess){
		ofBufferToFile(saveFileResult.filePath, decodedBuffer);
	}
	
}

string testApp::dnaToBits(string dna){
	string bits = ofToUpper(dna);
	ofStringReplace(bits, "A", "0");
	ofStringReplace(bits, "C", "0");
	ofStringReplace(bits, "G", "1");
	ofStringReplace(bits, "T", "1");
	return bits;
}
string testApp::getConsensus(vector<string> bundle){
	map<string, int> bySegment;
	map<int, string> byCount;
	for (int i = 0; i < bundle.size(); i++) {
		string key = bundle[i]; 
		if(!bySegment.count(key)) bySegment[key] = 0;
		bySegment[key]++;
	}
	for(map<string, int>::const_iterator iterator = bySegment.begin(); iterator != bySegment.end(); ++iterator){
		int key = (*iterator).second;
		string value = (*iterator).first;
		if(!byCount.count(key)) byCount[key] = value;
	}
	map<int, string>::reverse_iterator rit = byCount.rbegin();
	
	return rit->second;
}
