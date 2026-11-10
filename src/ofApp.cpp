#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(300);
	ofRotateZ(ofGetFrameNum() * 0.18);
	
	for (float radius = 100; radius <= 300; radius += 50) {

		for (int deg = 0; deg < 360; deg += 5) {

			ofPushMatrix();
			ofRotateZ(deg);
			ofTranslate(glm::vec2(radius * cos(0 * DEG_TO_RAD), radius * sin(0 * DEG_TO_RAD)));

			auto noise_location = glm::vec2(radius * 2 * cos(deg * DEG_TO_RAD), radius * 2 * sin(deg * DEG_TO_RAD));
			auto noise_radius = ofMap(ofNoise(glm::vec3(noise_location * 0.0025, ofGetFrameNum() * 0.005)), 0, 1, -120, 120);

			ofRotateY(90);

			this->draw_arrow(glm::vec2(), glm::vec2(noise_radius * cos(0 * DEG_TO_RAD), noise_radius * sin(0 * DEG_TO_RAD)), 18, ofColor(255));

			ofPopMatrix();
		}
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
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);
	auto distance = glm::distance(target, location);

	if (glm::length(distance) > size * 0.1) {

		ofPushMatrix();
		ofTranslate(target);

		ofSetColor(color);
		ofFill();
		ofBeginShape();
		ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
		ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)));
		ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)));
		ofEndShape();

		ofBeginShape();
		ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)) * 0.25);
		ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
		ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
		ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)) * 0.25);
		ofEndShape();

		ofPopMatrix();
	}

	ofDrawSphere(glm::vec3(location, 0), 3);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}