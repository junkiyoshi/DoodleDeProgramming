#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 13, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int x = 0; x < ofGetWidth(); x += 15) {

		for (int y = 15; y <= ofGetHeight(); y += 15) {

			auto noise_value = ofNoise(x * 0.0035, y * 0.0035, ofGetFrameNum() * 0.007);

			if (noise_value > 0.1 && noise_value <= 0.3) {

				ofSetColor(239, 139, 139);
				char c = ofMap(noise_value, 0.1, 0.3, 'a', 'c');
				this->font.drawString({ c }, x, y);

			}
			else if (noise_value > 0.4 && noise_value <= 0.6) {

				ofSetColor(139, 239, 139);
				char c = ofMap(noise_value, 0.4, 0.5, 'n', 'o');
				this->font.drawString({ c }, x, y);

			}
			else if (noise_value > 0.7 && noise_value <= 0.9) {

				ofSetColor(139, 139, 239);
				char c = ofMap(noise_value, 0.7, 0.9, 'x', 'z');
				this->font.drawString({ c }, x, y);
			}
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