#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("openFrameworks");
	ofSetFrameRate(25);

	ofBackground(39);
	ofSetColor(239);
	ofNoFill();
	ofEnableDepthTest();

	this->noise_step = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->noise_step -= 0.005;
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.72);

	ofColor color;
	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	int size_span = 10;
	vector<glm::vec3> vertices, before_verices;
	for (int size = 20; size < 3000; size += size_span) {

		auto x_value = ofNoise(noise_seed.x, size * 0.00015 + this->noise_step);
		auto y_value = ofNoise(noise_seed.y, size * 0.00015 + this->noise_step);
		auto z_value = ofNoise(noise_seed.z, size * 0.00015 + this->noise_step);

		auto x_deg = x_value < 0.5 ? ofMap(x_value, 0, 0.5, -270, 0) : x_value > 0.5 ? ofMap(x_value, 0.5, 1, 0, 270) : 0;
		auto y_deg = y_value < 0.5 ? ofMap(y_value, 0, 0.5, -270, 0) : y_value > 0.5 ? ofMap(y_value, 0.5, 1, 0, 270) : 0;
		auto z_deg = z_value < 0.5 ? ofMap(z_value, 0, 0.5, -270, 0) : z_value > 0.5 ? ofMap(z_value, 0.5, 1, 0, 270) : 0;

		auto rotation_x = glm::rotate(glm::mat4(), (float)(x_deg * DEG_TO_RAD), glm::vec3(1, 0, 0));
		auto rotation_y = glm::rotate(glm::mat4(), (float)(y_deg * DEG_TO_RAD), glm::vec3(0, 1, 0));
		auto rotation_z = glm::rotate(glm::mat4(), (float)(z_deg * DEG_TO_RAD), glm::vec3(0, 0, 1));

		vertices.clear();

		vertices.push_back(glm::vec3(size * 0.5, size * 0.5, size * 0.5));
		vertices.push_back(glm::vec3(size * 0.5, -size * 0.5, size * 0.5));
		vertices.push_back(glm::vec3(-size * 0.5, size * 0.5, size * 0.5));
		vertices.push_back(glm::vec3(-size * 0.5, -size * 0.5, size * 0.5));

		vertices.push_back(glm::vec3(size * 0.5, size * 0.5, -size * 0.5));
		vertices.push_back(glm::vec3(size * 0.5, -size * 0.5, -size * 0.5));
		vertices.push_back(glm::vec3(-size * 0.5, size * 0.5, -size * 0.5));
		vertices.push_back(glm::vec3(-size * 0.5, -size * 0.5, -size * 0.5));

		for (auto& vertex : vertices) {

			vertex = glm::vec4(vertex, 0) * rotation_z * rotation_y * rotation_x;
		}

		ofColor color(ofMap(size, 30, 3000, 239, 39));
		ofSetColor(color);

		for (int i = 0; i < 8; i++) {

			if (before_verices.size() <= 0) {

				break;
			}

			ofDrawLine(vertices[i], before_verices[i]);
		}

		before_verices = vertices;
	}

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 400;
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