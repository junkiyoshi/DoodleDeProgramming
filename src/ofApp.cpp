#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(0);
	ofNoFill();
	ofSetLineWidth(1.5);
}
//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);
	ofRotateZ(ofGetFrameNum() * 0.77);

	int deg_span = 5;

	auto target_deg = ofGetFrameNum() % 360;
	for (int radius = 50; radius <= 250; radius += 200) {

		vector<glm::vec3> vertices, vertices_2;
		for (int deg = 0; deg < 360; deg += deg_span) {

			auto location = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
			auto len = ofMap(ofNoise(glm::vec4(location * 0.01, ofGetFrameNum() * 0.01)), 0, 1, -250, 250);

			auto location_2 = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), len);

			ofDrawLine(location, location_2);

			vertices.push_back(location);
			vertices_2.push_back(location_2);
		}

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofBeginShape();
		ofVertices(vertices_2);
		ofEndShape(true);
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