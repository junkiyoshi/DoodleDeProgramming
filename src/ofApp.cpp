#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetCircleResolution(60);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int deg_span = 40;
	int radius_span = 1;
	int deg_len = 3;

	ofFill();
	ofSetColor(239, 39, 39);
	ofDrawCircle(glm::vec2(), 320 + radius_span);

	ofSetColor(0);
	ofFill();

	for (int deg = 0; deg < 360; deg += deg_span) {

		for (int radius = 5; radius < 320; radius += radius_span) {

			ofSetColor(radius < 50 ? 0 : ofMap(radius, 50, 320, 0, 239));

			auto noise_deg = ofGetFrameNum() * 2 + ofMap(ofNoise(radius * 0.0023 - ofGetFrameNum() * 0.0001), 0, 1, 180, -180);
			auto next_noise_deg = ofGetFrameNum() * 2 + ofMap(ofNoise((radius + radius_span) * 0.0023 - ofGetFrameNum() * 0.0001), 0, 1, 180, -180);

			ofBeginShape();
			ofVertex(glm::vec2(radius * cos((deg + noise_deg - deg_len) * DEG_TO_RAD), radius * sin((deg + noise_deg - deg_len) * DEG_TO_RAD)));
			ofVertex(glm::vec2(radius * cos((deg + noise_deg + deg_len) * DEG_TO_RAD), radius * sin((deg + noise_deg + deg_len) * DEG_TO_RAD)));
			ofVertex(glm::vec2((radius + radius_span) * cos((deg + next_noise_deg + deg_len) * DEG_TO_RAD), (radius + radius_span) * sin((deg + next_noise_deg + deg_len) * DEG_TO_RAD)));
			ofVertex(glm::vec2((radius + radius_span) * cos((deg + next_noise_deg - deg_len) * DEG_TO_RAD), (radius + radius_span) * sin((deg + next_noise_deg - deg_len) * DEG_TO_RAD)));
			ofEndShape(true);

			noise_deg = ofMap(ofNoise(radius * 0.0023 - ofGetFrameNum() * 0.0001), 0, 1, -180, 180) - ofGetFrameNum() * 2;
			next_noise_deg = ofMap(ofNoise((radius + radius_span) * 0.0023 - ofGetFrameNum() * 0.0001), 0, 1, -180, 180) - ofGetFrameNum() * 2;

			ofBeginShape();
			ofVertex(glm::vec2(radius * cos((deg + noise_deg - deg_len) * DEG_TO_RAD), radius * sin((deg + noise_deg - deg_len) * DEG_TO_RAD)));
			ofVertex(glm::vec2(radius * cos((deg + noise_deg + deg_len) * DEG_TO_RAD), radius * sin((deg + noise_deg + deg_len) * DEG_TO_RAD)));
			ofVertex(glm::vec2((radius + radius_span) * cos((deg + next_noise_deg + deg_len) * DEG_TO_RAD), (radius + radius_span) * sin((deg + next_noise_deg + deg_len) * DEG_TO_RAD)));
			ofVertex(glm::vec2((radius + radius_span) * cos((deg + next_noise_deg - deg_len) * DEG_TO_RAD), (radius + radius_span) * sin((deg + next_noise_deg - deg_len) * DEG_TO_RAD)));
			ofEndShape(true);
		}
	}

	ofNoFill();
	ofDrawCircle(glm::vec2(), 320 + radius_span);

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