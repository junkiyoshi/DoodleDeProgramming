#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	for (int i = 0; i < 3; i++) {

		this->noise_seed_list.push_back(glm::vec2(ofRandom(1000), ofRandom(1000)));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	int index = 0;
	auto radius = 60;
	for (auto& noise_seed : this->noise_seed_list) {

		auto deg = ofGetFrameNum() * 3 + index * 120;
		auto next_deg = deg + 3;

		auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		auto next = glm::vec2(radius * cos(next_deg * DEG_TO_RAD), radius * sin(next_deg * DEG_TO_RAD));

		auto distance = location - next;
		distance *= 1;

		for (int i = 0; i < 2; i++) {

			auto future = location + distance * 8;
			auto random_deg = ofRandom(360);
			future += glm::vec2(4 * cos(random_deg * DEG_TO_RAD), 4 * sin(random_deg * DEG_TO_RAD));
			auto future_distance = future - location;

			this->location_list.push_back(location);
			this->velocity_list.push_back(glm::normalize(future_distance) * glm::length(distance));
		}

		index++;
	}

	for (int i = this->location_list.size() - 1; i > -1; i--) {

		this->location_list[i] += this->velocity_list[i];
		this->velocity_list[i] *= 1.01;

		if (glm::length(this->location_list[i]) > 360) {

			this->location_list.erase(this->location_list.begin() + i);
			this->velocity_list.erase(this->velocity_list.begin() + i);
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	ofRotateY(180);

	ofSetColor(0);
	for (auto& location : this->location_list) {

		ofPushMatrix();
		ofTranslate(location);

		auto size = ofMap(glm::length(location), 60, 320, 5, 50);
		ofDrawRectangle(glm::vec2(), size, size);

		ofPopMatrix();
	}

	ofSetColor(239);
	for (auto& location : this->location_list) {

		ofPushMatrix();
		ofTranslate(location);

		auto size = ofMap(glm::length(location), 60, 320, 1, 50);
		ofDrawRectangle(glm::vec2(), size, size);

		ofPopMatrix();
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 350;
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