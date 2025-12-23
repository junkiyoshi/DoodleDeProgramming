#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->frame.clear();

	for (auto y = -300; y < 300; y += 30) {

		for (auto x = -600; x <= 600; x += 1) {

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(x, y, 0));
			vertices.push_back(glm::vec3(x + 1, y, 0));
			vertices.push_back(glm::vec3(x + 1, y, 100));
			vertices.push_back(glm::vec3(x, y, 100));

			for (auto& vertex : vertices) {

				if (vertex.z == 100) {

					auto noise_value = ofNoise(y * 0.005, vertex.x * 0.0025, vertex.y * 0.0025, ofGetFrameNum() * 0.005);
					if (noise_value > 0.5) {

						vertex.z = ofMap(noise_value, 0.5, 1, 0, 1000);
						vertex.z *= ofMap(y, -300, 300, 0, 1);
						vertex.z *= ofMap(abs(x), 0, 600, 1, 0);
					}
					else {

						vertex.z = 0;
					}
				}
			}

			this->frame.addVertices(vertices);

			this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 2);
			this->frame.addIndex(this->frame.getNumVertices() - 3); this->frame.addIndex(this->frame.getNumVertices() - 4);

			ofColor frame_color = ofColor(y < -100 ? 239 : ofMap(y, -100, 300, 239, 39));

			this->frame.addColor(frame_color);
			this->frame.addColor(frame_color);
			this->frame.addColor(frame_color);
			this->frame.addColor(frame_color);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	this->frame.drawWireframe();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 350;
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