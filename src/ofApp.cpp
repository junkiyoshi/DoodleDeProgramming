#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	float radius = 280;
	ofColor color;
	for (int i = 0; i < 8; i++) {

		float len = ofMap(i, 0, 8, 5, 60);

		vector<glm::vec2> vertices_1, vertices_2;
		float deg_start = ofMap(ofNoise(i * 0.1 - ofGetFrameNum() * 0.01), 0, 1, -360, 360);

		for (float deg = deg_start; deg < deg_start + 90; deg += 1) {

			vertices_1.push_back(glm::vec2((radius - len * 0.5) * cos(deg * DEG_TO_RAD), (radius - len * 0.5) * sin(deg * DEG_TO_RAD)));
			vertices_2.push_back(glm::vec2((radius + len * 0.5) * cos(deg * DEG_TO_RAD), (radius + len * 0.5) * sin(deg * DEG_TO_RAD)));
		}

		reverse(vertices_2.begin(), vertices_2.end());

		color.setHsb(180, ofMap(i, 0, 8, 255, 100), 255);

		ofNoFill();
		ofSetColor(color);

		ofBeginShape();
		ofVertices(vertices_1);
		ofVertices(vertices_2);
		ofEndShape(true);

		ofFill();
		ofSetColor(color, 128);

		ofBeginShape();
		ofVertices(vertices_1);
		ofVertices(vertices_2);
		ofEndShape(true);
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