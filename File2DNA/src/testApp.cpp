#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetWindowShape(350, 60);
	ofSetWindowTitle("File2DNA");
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofClear(0, 0, 0);
	ofDrawBitmapString("Drag and drop files to convert to DNA", 20,20);
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
			
			encode(dragInfo.files[k]);
			
		}
	}
}

void testApp::encode(string path){
	ofFileDialogResult saveFileResult = ofSystemSaveDialog(ofFilePath::removeExt(ofFilePath::getFileName(path)) + ".dna", "Save your file");
	if (saveFileResult.bSuccess){
		string script = ofFilePath::getEnclosingDirectory(ofFilePath::getCurrentExePath(), false) + "../Resources/Bits2DNA.pl";
		string command = "perl " + script + " \"" + path + "\" \"" + saveFileResult.filePath + "\"";
		system(command.c_str());
	}
}