#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetCircleResolution(60);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	float start_radius = 100;
	float end_radius = 600;

	ofFill();
	ofSetColor(239, 39, 39);
	for (float deg = 0; deg < 360; deg += 0.25) {

		for (float radius = start_radius; radius < end_radius; radius += 1) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			auto noise_value = ofNoise(glm::vec3(noise_location * 5, radius * 0.005 - ofGetFrameNum() * 0.05));

			if (noise_value > 0.43 && noise_value < 0.57) {

				ofDrawCircle(location, 4);
			}
		}
	}

	for (float deg = 0; deg < 360; deg += 0.5) {

		ofDrawCircle(glm::vec2((start_radius - 8) * cos(deg * DEG_TO_RAD), (start_radius - 8) * sin(deg * DEG_TO_RAD)), 3);
	}

	ofSetColor(39);
	for (float deg = 0; deg < 360; deg += 0.25) {

		for (float radius = start_radius; radius < end_radius; radius += 1) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			auto noise_value = ofNoise(glm::vec3(noise_location * 5, radius * 0.005 - ofGetFrameNum() * 0.05));

			if (noise_value > 0.43 && noise_value < 0.57) {

				ofDrawCircle(location, 2);
			}
		}
	}

	for (float deg = 0; deg < 360; deg += 0.5) {

		ofDrawCircle(glm::vec2((start_radius - 8) * cos(deg * DEG_TO_RAD), (start_radius - 8) * sin(deg * DEG_TO_RAD)), 1);
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