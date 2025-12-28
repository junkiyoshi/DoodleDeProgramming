#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	int span = 6;
	for (int x = -120; x <= 120; x += span) {

		for (int y = -120; y <= 120; y += span) {

			for (int z = -120; z <= 120; z += span) {

				this->location_list.push_back(glm::vec3(x, y, z));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	float size = 6;
	for (int i = 0; i < this->location_list.size(); i++) {

		this->setBoxToMesh(this->face, this->frame, this->location_list[i], size);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.44);
	ofRotateX(ofGetFrameNum() * 0.72);

	this->face.draw();
	this->frame.drawWireframe();

	this->cam.end();

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
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float size) {

	this->setBoxToMesh(face_target, frame_target, location, size, size, size);
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float height, float width, float depth) {

	auto noise_value = ofNoise(glm::vec4(location.x * 0.01, location.y * 0.01, location.z * 0.01, ofGetFrameNum() * 0.01));

	ofColor face_color(39), frame_color(239);

	if (noise_value > 0.4 && noise_value < 0.6) {
	
		if (noise_value > 0.47 && noise_value < 0.53) {

			face_color = ofColor(255, 0, 0);
		}
		else {

			return;
		}
	}

	int face_index = face_target.getNumVertices();
	int frame_index = frame_target.getNumVertices();

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
		frame_target.addVertex(location + vertex);
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

	frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 1);
	frame_target.addIndex(frame_index + 1); frame_target.addIndex(frame_index + 2);
	frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 3);
	frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 0);

	frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 5);
	frame_target.addIndex(frame_index + 5); frame_target.addIndex(frame_index + 6);
	frame_target.addIndex(frame_index + 6); frame_target.addIndex(frame_index + 7);
	frame_target.addIndex(frame_index + 7); frame_target.addIndex(frame_index + 4);

	frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 4);
	frame_target.addIndex(frame_index + 1); frame_target.addIndex(frame_index + 5);
	frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 6);
	frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 7);

	for (int i = 0; i < 8; i++) {

		face_target.addColor(face_color);
		frame_target.addColor(frame_color);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}