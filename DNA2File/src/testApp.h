#pragma once

#include "ofMain.h"

#define PREFIX_PRIMER "CTACACGACGCTCTTCCGATCT"
#define SUFIX_PRIMER "AGATCGGAAGAGCGGTTCAGCA"
//Length of segment in bytes (not including segment number)
#define SEGMENT_LENGHT 12
// 2^19 = 524,288 = max number of oligos -> 00010011
#define MAX_OLIGOS 19

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		void decode(string path);
		string dnaToBits(string dna);
		string getConsensus(vector<string> bundle);

};
