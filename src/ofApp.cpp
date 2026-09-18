#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int span = 1;
	int len = 100;
	ofColor face_color(0);
	ofColor line_color(239);

	int z = len + span * 0.5;

	float angle;
	glm::highp_mat4 rotation, twist;
	for (auto i = 0; i < 3; i++) {

		for (auto x = -len * 0.125; x <= len * 0.125; x += span) {

			for (auto y = -len * 12; y <= len * 6; y += span) {

				angle = PI * 0.125 * i;
				rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 1, 0));

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec4(x - span * 0.5, y - span * 0.5, z, 0) * rotation);
				vertices.push_back(glm::vec4(x + span * 0.5, y - span * 0.5, z, 0) * rotation);
				vertices.push_back(glm::vec4(x + span * 0.5, y + span * 0.5, z, 0) * rotation);
				vertices.push_back(glm::vec4(x - span * 0.5, y + span * 0.5, z, 0) * rotation);

				for (auto& vertex : vertices) {

					auto noise_value = ofNoise(vertex.y * 0.0008 + ofGetFrameNum() * 0.008);
					auto twist_rad = ofMap(noise_value, 0, 1, PI * -10, PI * 10);
					twist = glm::rotate(glm::mat4(), twist_rad, glm::vec3(0, 1, 0));

					vertex = glm::vec4(vertex, 0) * twist;
				}

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				this->face.addColor(face_color);
				this->face.addColor(face_color);
				this->face.addColor(face_color);
				this->face.addColor(face_color);

				if (x == -len * 0.125) {

					this->frame.addVertex(vertices[0]);
					this->frame.addVertex(vertices[3]);

					this->frame.addColor(line_color);
					this->frame.addColor(line_color);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);
				}

				if (x >= len * 0.125 - span) {

					this->frame.addVertex(vertices[1]);
					this->frame.addVertex(vertices[2]);

					this->frame.addColor(line_color);
					this->frame.addColor(line_color);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	this->frame.drawWireframe();
	this->face.draw();

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
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}