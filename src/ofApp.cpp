#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(0);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int deg_span = 30;
	int radius_span = 1;
	for (int deg = 0; deg < 360; deg += deg_span) {

		for (int radius = 15; radius < 720; radius += radius_span) {

			auto noise_deg = ofMap(ofNoise(radius * 0.0015 - ofGetFrameNum() * 0.005), 0, 1, 360, -360);
			auto next_noise_deg = ofMap(ofNoise((radius + radius_span) * 0.0015 - ofGetFrameNum() * 0.005), 0, 1, 360, -360);

			ofBeginShape();
			ofVertex(glm::vec2(radius * cos((deg + noise_deg - 5) * DEG_TO_RAD), radius * sin((deg + noise_deg - 5) * DEG_TO_RAD)));
			ofVertex(glm::vec2(radius * cos((deg + noise_deg + 5) * DEG_TO_RAD), radius * sin((deg + noise_deg + 5) * DEG_TO_RAD)));
			ofVertex(glm::vec2((radius + radius_span) * cos((deg + next_noise_deg + 5) * DEG_TO_RAD), (radius + radius_span) * sin((deg + next_noise_deg + 5) * DEG_TO_RAD)));
			ofVertex(glm::vec2((radius + radius_span) * cos((deg + next_noise_deg - 5) * DEG_TO_RAD), (radius + radius_span) * sin((deg + next_noise_deg - 5) * DEG_TO_RAD)));
			ofEndShape(true);

			noise_deg = ofMap(ofNoise(radius * 0.0015 - ofGetFrameNum() * 0.005), 0, 1, -360, 360);
			next_noise_deg = ofMap(ofNoise((radius + radius_span) * 0.0015 - ofGetFrameNum() * 0.005), 0, 1, -360, 360);

			ofBeginShape();
			ofVertex(glm::vec2(radius * cos((deg + noise_deg - 5) * DEG_TO_RAD), radius * sin((deg + noise_deg - 5) * DEG_TO_RAD)));
			ofVertex(glm::vec2(radius * cos((deg + noise_deg + 5) * DEG_TO_RAD), radius * sin((deg + noise_deg + 5) * DEG_TO_RAD)));
			ofVertex(glm::vec2((radius + radius_span) * cos((deg + next_noise_deg + 5) * DEG_TO_RAD), (radius + radius_span) * sin((deg + next_noise_deg + 5) * DEG_TO_RAD)));
			ofVertex(glm::vec2((radius + radius_span) * cos((deg + next_noise_deg - 5) * DEG_TO_RAD), (radius + radius_span) * sin((deg + next_noise_deg - 5) * DEG_TO_RAD)));
			ofEndShape(true);
		}
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