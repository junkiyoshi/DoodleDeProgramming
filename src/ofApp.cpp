#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetColor(239);

	ofNoFill();
	ofSetLineWidth(2);

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 50 < 25) {

		this->noise_param += ofMap(ofGetFrameNum() % 25, 0, 25, 0.3, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto radius = 24;
	auto x_span = radius * sqrt(3);
	auto flg = true;

	for (float y = 0; y <= 720 + radius; y += radius * 1.5) {

		for (float x = 0; x <= 720 + radius; x += x_span) {

			glm::vec3 location;
			if (flg) {

				location = glm::vec3(x, y, 0);
			}
			else {

				location = glm::vec3(x + (x_span / 2), y, 0);
			}

			auto noise_value = ofNoise(location.x * 0.0025, location.y * 0.0025 + this->noise_param, this->noise_param * 0.25);
			if (noise_value < 0.35 || noise_value > 0.65) { continue; }

			ofPushMatrix();
			ofTranslate(location);
			ofRotate(90);

			ofBeginShape();
			for (int deg = 0; deg <= 360; deg += 60) {

				auto draw_radius = radius * 0.8;
				auto target = glm::vec2(draw_radius * cos(deg * DEG_TO_RAD), draw_radius * sin(deg * DEG_TO_RAD));
				
				ofVertex(target);
			}
			ofEndShape(false);

			ofPopMatrix();
		}
		flg = !flg;
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