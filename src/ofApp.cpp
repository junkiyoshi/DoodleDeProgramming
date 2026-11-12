#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(3);

	this->noise_step = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 50 < 5) {

		this->noise_step += 0.5;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int size = 30;

	ofFill();
	for (int x = size * -12; x < size * 12; x += size) {

		ofColor color;
		color.setHsb(ofMap(x, size * -12, size * 12, 0, 255), 130, 255);
		ofSetColor(color);

		for (int y = size * -8; y < size * 8; y += size) {

			ofPushMatrix();
			ofTranslate(x, y);

			int param = ofMap(ofNoise(this->noise_step, x * 0.004, y * 0.004), 0, 1, 0, 4);
			param = param % 2;

			switch (param) {
			case 0:

				ofDrawLine(0, size, size, 0);
				break;
			case 1:

				ofDrawLine(0, 0, size, size);
				break;
			case 2:

				ofDrawLine(0, 0, size, 0);
				break;
			case 3:

				ofDrawLine(size, 0, size, size);
				break;
			default:
				break;
			}

			ofPopMatrix();
		}
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 500;
	if (ofGetFrameNum() > start) {

		std::ostringstream os;
		os << std::setw(4) << std::setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}