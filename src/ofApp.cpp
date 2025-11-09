#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableDepthTest();
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto radius = 50;
	auto len = 5;
	auto noise_seed = glm::vec3(ofRandom(100), ofRandom(100), ofRandom(100));
	for (int z = 0; z < 300; z += 10) {

		auto rotate_x = ofMap(ofNoise(noise_seed.x, z * 0.0025 + ofGetFrameNum() * 0.01), 0, 1, -30, 30);
		auto rotate_y = ofMap(ofNoise(noise_seed.y, z * 0.0025 + ofGetFrameNum() * 0.01), 0, 1, -30, 30);
		auto rotate_z = ofMap(ofNoise(noise_seed.z, z * 0.0025 + ofGetFrameNum() * 0.01), 0, 1, -30, 30);

		ofPushMatrix();
		ofRotateZ(rotate_z);
		ofRotateY(rotate_y);
		ofRotateX(rotate_x);

		for (int deg = 0; deg < 360; deg += 1) {

			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z));
			vertices.push_back(glm::vec3(radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), z));
			vertices.push_back(glm::vec3((radius + len) * cos((deg + 1) * DEG_TO_RAD), (radius + len) * sin((deg + 1) * DEG_TO_RAD), z));
			vertices.push_back(glm::vec3((radius + len) * cos(deg * DEG_TO_RAD), (radius + len) * sin(deg * DEG_TO_RAD), z));

			ofSetColor(0);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape();

			ofSetColor(255);
			ofDrawLine(vertices[0], vertices[1]);
			ofDrawLine(vertices[2], vertices[3]);
		}

		ofPopMatrix();
	}

	this->cam.end();

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