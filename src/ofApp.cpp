#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateZ(ofGetFrameNum() * 0.16);

	int radius = 150;
	int size = (radius * 2 * PI) / 360 * 3;
	for (int deg = 0; deg < 360; deg += 3) {

		auto location = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
		auto height = 120;
		auto power = ofMap(ofNoise(location.x * 0.02, location.y * 0.02, ofGetFrameNum() * 0.01), 0, 1, 0, 25);

		ofPushMatrix();
		ofTranslate(location);
		ofRotateZ(deg);
		ofTranslate(height * 0.25, 0, 0);

		ofTranslate(0, 0, size * power * 0.5);

		ofFill();
		ofSetColor(0);
		ofDrawBox(height - 1, size - 1, size * power - 1);

		ofNoFill();
		ofSetColor(255);
		ofDrawBox(height, size, size * power);

		ofPopMatrix();
	}

	this->cam.end();

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
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}