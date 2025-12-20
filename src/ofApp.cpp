#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 75 < 15) {

		this->noise_value = ofRandom(1000);
	}

	for (int i = 0; i < 300; i++) {

		this->location_list.push_back(glm::vec2(ofRandom(-360, 360), ofRandom(-360, 360)));
		this->life_list.push_back(0);
	}

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		if (this->life_list[i] > 100) {

			this->location_list.erase(this->location_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
		}
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		auto deg = ofMap(ofNoise(this->location_list[i].x * 0.002, this->location_list[i].y * 0.002, this->noise_value), 0, 1, -360, 360);
		auto next = this->location_list[i] + glm::vec2(5 * cos(deg * DEG_TO_RAD), 5 * sin(deg * DEG_TO_RAD));
		next = glm::length(next) > 280 ? glm::normalize(next) * 280 : next;
		this->location_list[i] = next;
		this->life_list[i] += 1;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofSetColor(0);
	for (int i = 0; i < this->location_list.size(); i++) {

		auto size = this->life_list[i] < 30 ? ofMap(this->life_list[i], 0, 30, 0, 4) : 4;
		ofDrawCircle(this->location_list[i], size);
	}

	ofSetColor(255);
	for (int i = 0; i < this->location_list.size(); i++) {

		auto size = this->life_list[i] < 30 ? ofMap(this->life_list[i], 0, 30, 0, 4) : 4;
		ofDrawCircle(this->location_list[i], size * 0.4);
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 750;
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