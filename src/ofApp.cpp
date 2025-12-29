#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();

	float span = 0.5;
	for (float x = -200; x <= 200; x += span) {

		for (float y = -200; y <= 200; y += span) {

			for (float z = -200; z <= 200; z += span) {

				if (abs(x) >= 200 || abs(y) >= 200 || abs(z) >= 200) {
				
					this->location_list.push_back(glm::vec3(x, y, z));
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();

	float size = 0.5;
	for (int i = 0; i < this->location_list.size(); i++) {

		this->setBoxToMesh(this->face, this->location_list[i], size);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.44);

	this->face.draw();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 2;
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
void ofApp::setBoxToMesh(ofMesh& face_target, glm::vec3 location, float size) {

	this->setBoxToMesh(face_target, location, size, size, size);
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, glm::vec3 location, float height, float width, float depth) {

	auto noise_value = ofNoise(glm::vec4(location.x * 0.023, location.y * 0.001, location.z * 0.023, ofGetFrameNum() * 0.01));
	
	if (noise_value < 0.47 || noise_value > 0.53) { return; }
	ofColor face_color(128, 128, 255);

	int face_index = face_target.getNumVertices();

	vector<glm::vec3> vertices;
	vertices.push_back(glm::vec3(width * -0.5, height * 0.5, depth * -0.5));
	vertices.push_back(glm::vec3(width * 0.5, height * 0.5, depth * -0.5));
	vertices.push_back(glm::vec3(width * 0.5, height * 0.5, depth * 0.5));
	vertices.push_back(glm::vec3(width * -0.5, height * 0.5, depth * 0.5));

	vertices.push_back(glm::vec3(width * -0.5, height * -0.5, depth * -0.5));
	vertices.push_back(glm::vec3(width * 0.5, height * -0.5, depth * -0.5));
	vertices.push_back(glm::vec3(width * 0.5, height * -0.5, depth * 0.5));
	vertices.push_back(glm::vec3(width * -0.5, height * -0.5, depth * 0.5));

	for (auto& vertex : vertices) {

		face_target.addVertex(location + vertex * 0.99);
	}

	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 2);
	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 3);

	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);

	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 1);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 1);

	face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
	face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 1);

	face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);
	face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 2);

	face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 4);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 3);

	for (int i = 0; i < 8; i++) {

		face_target.addColor(face_color);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}