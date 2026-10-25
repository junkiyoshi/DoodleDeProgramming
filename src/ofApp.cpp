#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(90);
	ofRotateZ(ofGetFrameNum() * 0.36);

	int radius = 150;
	int size = (radius * 2 * PI) / 360 * 3;
	for (int deg = 0; deg < 360; deg += 6) {

		auto location = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
		auto height = 150;
		auto power = ofMap(ofNoise(location.x * 0.02, location.y * 0.02, ofGetFrameNum() * 0.01), 0, 1, 0, 25);

		ofPushMatrix();
		ofTranslate(location);
		ofRotateZ(deg);

		ofFill();
		ofSetColor(0);
		ofDrawBox(height - 1, size - 1, size * power - 1);

		ofNoFill();
		ofSetColor(255);
		ofDrawBox(height, size, size * power);

		ofPopMatrix();
	}

	this->cam.end();

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