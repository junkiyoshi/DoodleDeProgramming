#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	auto size = 20;
	auto base_radius = 400;
	auto noise_seed = ofRandom(1000);

	ofColor color;
	for (int i = 0; i < 3; i++) {

		color.setHsb(ofMap(i, 0, 3, 0, 255), 180, 255);
		noise_seed += 0.05;

		for (int deg = 0; deg < 360; deg += 6) {

			auto base_location = glm::vec2(base_radius * cos(deg * DEG_TO_RAD), base_radius * sin(deg * DEG_TO_RAD));

			auto base_noise_value = ofNoise(glm::vec4(noise_seed, base_location * 0.01, ofGetFrameNum() * 0.025));
			auto prev_base_noise_value = ofNoise(glm::vec4(noise_seed, base_location * 0.01, (ofGetFrameNum() - 1) * 0.025));

			auto radius = base_radius * 0.5;
			auto prev_radius = base_radius * 0.5;

			if (base_noise_value < 0.45) { radius = ofMap(base_noise_value, 0, 0.45, base_radius * 0, base_radius * 0.5); }
			else if (base_noise_value > 0.55) { radius = ofMap(base_noise_value, 0.55, 1, base_radius * 0.5, base_radius * 0.9); }

			if (prev_base_noise_value < 0.45) { prev_radius = ofMap(prev_base_noise_value, 0, 0.45, base_radius * 0, base_radius * 0.5); }
			else if (prev_base_noise_value > 0.55) { prev_radius = ofMap(prev_base_noise_value, 0.55, 1, base_radius * 0.5, base_radius * 0.9); }

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto prev_location = glm::vec2(prev_radius * cos(deg * DEG_TO_RAD), prev_radius * sin(deg * DEG_TO_RAD));

			if (location == prev_location) {

				ofFill();
				ofSetColor(ofColor(color, 200));
				ofDrawCircle(prev_location, size * 0.5);
			}
			else {

				ofFill();
				ofSetColor(ofColor(color, 128));
				ofDrawCircle(location, radius < base_radius * 0.5 ? ofMap(radius, 3, base_radius * 0.5, 0, size * 0.5) : size * 0.5);

				ofNoFill();
				ofSetColor(color);
				ofDrawCircle(location, radius < base_radius * 0.5 ? ofMap(radius, 3, base_radius * 0.5, 0, size * 0.5) : size * 0.5);
			}
		}
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 450;
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