#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetCircleResolution(60);

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->noise_param += 0.025;
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	float start_radius = 5;
	float end_radius = 600;

	for (float deg = 0; deg < 360; deg += 0.25) {

		for (float radius = start_radius; radius < end_radius; radius += 1) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			auto noise_value = ofNoise(glm::vec4(noise_location * 3, radius * 0.005, this->noise_param));

			if (noise_value >= 0.4 && noise_value <= 0.6) {

				ofSetColor(ofMap(abs(0.5 - noise_value), 0, 0.1, 255, 39));
				ofDrawCircle(location, 1.5);
			}
		}
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 50;
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