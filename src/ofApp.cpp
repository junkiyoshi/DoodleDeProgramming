#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}
//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);
	ofRotateZ(ofGetFrameNum() * 0.77);

	auto target_deg = ofGetFrameNum() % 360;
	auto deg_span = 5;

	for (auto radius = 50; radius <= 300; radius += 50) {

		for (auto deg = 0; deg < 360; deg += deg_span) {

			auto location_1 = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
			auto location_2 = glm::vec3(radius * cos((deg + deg_span) * DEG_TO_RAD), radius * sin((deg + deg_span) * DEG_TO_RAD), 0);
			auto len_1 = ofMap(ofNoise(glm::vec4(location_1 * 0.005, ofGetFrameNum() * 0.01)), 0, 1, -250, 250);
			auto len_2 = ofMap(ofNoise(glm::vec4(location_2 * 0.005, ofGetFrameNum() * 0.01)), 0, 1, -250, 250);

			vector<glm::vec3> vertices;
			vertices.push_back(location_1);
			vertices.push_back(location_2);
			vertices.push_back(location_2 + glm::vec3(0, 0, len_2));
			vertices.push_back(location_1 + glm::vec3(0, 0, len_1));

			ofFill();
			ofSetColor(39, 39, 239, 128);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(39, 39, 239);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}
	}

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 150;
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