#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	float span = 1;
	float threshold_1 = 0.45;
	float threshold_2 = 0.55;
	float frame_param = ofGetFrameNum() * -0.02;
	float coordinate_param = 0.01;
	float len = 170;
	float angle;
	ofColor face_color(0), frame_color(239);

	for (float z = -len; z <= len; z += 17) {

		for (float x = -len; x <= len; x += span) {

			for (float y = -len; y <= len; y += span) {

				auto radius = glm::length(glm::vec3(x, y, z));
				auto noise_value = ofNoise(radius * coordinate_param + frame_param);
				if (noise_value < threshold_1 || noise_value > threshold_2) { continue; }

				auto radius_1 = glm::length(glm::vec3(x - span, y, z));
				auto noise_1 = ofNoise(radius_1 * coordinate_param + frame_param);

				auto radius_2 = glm::length(glm::vec3(x, y + span, z));
				auto noise_2 = ofNoise(radius_2 * coordinate_param + frame_param);

				auto radius_3 = glm::length(glm::vec3(x + span, y, z));
				auto noise_3 = ofNoise(radius_3 * coordinate_param + frame_param);

				auto radius_4 = glm::length(glm::vec3(x, y - span, z));
				auto noise_4 = ofNoise(radius_4 * coordinate_param + frame_param);
				
				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec4(x - span * 0.5, y - span * 0.5, z, 0));
				vertices.push_back(glm::vec4(x + span * 0.5, y - span * 0.5, z, 0));
				vertices.push_back(glm::vec4(x + span * 0.5, y + span * 0.5, z, 0));
				vertices.push_back(glm::vec4(x - span * 0.5, y + span * 0.5, z, 0));

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				this->face.addColor(face_color); this->face.addColor(face_color);
				this->face.addColor(face_color); this->face.addColor(face_color);

				if (noise_1 < threshold_1 || noise_1 > threshold_2 || x == -len) {

					this->frame.addVertex(vertices[0]);
					this->frame.addVertex(vertices[3]);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);

					this->frame.addColor(frame_color); this->frame.addColor(frame_color);
				}

				if (noise_2 < threshold_1 || noise_2 > threshold_2 || y == len) {

					this->frame.addVertex(vertices[2]);
					this->frame.addVertex(vertices[3]);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);

					this->frame.addColor(frame_color); this->frame.addColor(frame_color);
				}

				if (noise_3 < threshold_1 || noise_3 > threshold_2 || x == len) {

					this->frame.addVertex(vertices[1]);
					this->frame.addVertex(vertices[2]);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);

					this->frame.addColor(frame_color); this->frame.addColor(frame_color);
				}

				if (noise_4 < threshold_1 || noise_4 > threshold_2 || y == -len) {

					this->frame.addVertex(vertices[0]);
					this->frame.addVertex(vertices[1]);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);

					this->frame.addColor(frame_color); this->frame.addColor(frame_color);
				}
			}

		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(310);

	this->frame.draw();
	this->face.draw();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 5;
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

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}