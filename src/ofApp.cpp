#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(239);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 60 < 35) {

		this->noise_param += ofMap(ofGetFrameNum() % 60, 0, 35, 0.05, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	ofRotateY(ofGetFrameNum() * 1.44);

	float radius = 180;
	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (int deg = 0; deg < 360; deg += 5) {

		auto noise_location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		auto noise_value = ofNoise(glm::vec4(noise_seed.x, noise_location * 0.0075, this->noise_param));
		auto noise_deg = ofMap(noise_value, 0, 1, -360, 360);
		auto len = radius * 0.5;

		ofPushMatrix();
		ofRotate(deg);
		ofTranslate(glm::vec2(radius, 0));
		ofRotateY(noise_deg);

		ofDrawLine(glm::vec2(), glm::vec2(len, 0));
		ofDrawSphere(glm::vec3(), 3);
		
		ofTranslate(glm::vec2(len, 0));

		noise_value = ofNoise(glm::vec4(noise_seed.y, noise_location * 0.0075, this->noise_param));
		noise_deg = ofMap(noise_value, 0, 1, -360, 360);

		ofRotateY(noise_deg);

		ofDrawLine(glm::vec2(), glm::vec2(len * 0.5, 0));
		ofDrawSphere(glm::vec3(), 3);

		ofTranslate(glm::vec2(len * 0.5, 0));

		noise_value = ofNoise(glm::vec4(noise_seed.z, noise_location * 0.0075, this->noise_param));
		noise_deg = ofMap(noise_value, 0, 1, -360, 360);

		ofRotateY(noise_deg);

		ofDrawLine(glm::vec2(), glm::vec2(len * 0.25, 0));
		ofDrawSphere(glm::vec3(), 3);

		ofDrawSphere(glm::vec3(len * 0.25, 0, 0), 3);

		ofPopMatrix();
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 250;
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