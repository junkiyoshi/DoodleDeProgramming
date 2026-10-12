#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	float span = 0.5;
	float threshold_1 = 0.45;
	float threshold_2 = 0.55;
	float frame_param = ofGetFrameNum() * 0.05;
	float coordinate_param = 0.01;
	float len = 170;
	float angle;
	glm::highp_mat4 rotation;
	ofColor face_color(0), frame_color;

	for (float z = -len; z <= len; z += 17) {

		for (float x = -len; x <= len; x += span) {

			for (float y = -len; y <= len; y += span) {

				frame_color = ofColor(ofMap(z, -len, len, 239, 39));

				glm::vec3 noise_location = glm::vec4(x, y, z, 0) * rotation;
				auto noise_value = ofNoise(glm::vec4(
					noise_location.x * coordinate_param,
					noise_location.y * coordinate_param,
					noise_location.z * coordinate_param * 0.25,
					frame_param));
				if (noise_value < threshold_1 || noise_value > threshold_2) { continue; }

				glm::vec3 loc_1 = glm::vec4(x - span, y, z, 0) * rotation;
				auto noise_1 = ofNoise(glm::vec4(
					loc_1.x * coordinate_param,
					loc_1.y * coordinate_param,
					loc_1.z * coordinate_param * 0.25,
					frame_param));
				glm::vec3 loc_2 = glm::vec4(x, y + span, z, 0) * rotation;
				auto noise_2 = ofNoise(glm::vec4(
					loc_2.x * coordinate_param,
					loc_2.y * coordinate_param,
					loc_2.z * coordinate_param * 0.25,
					frame_param));
				glm::vec3 loc_3 = glm::vec4(x + span, y, z, 0) * rotation;
				auto noise_3 = ofNoise(glm::vec4(
					loc_3.x * coordinate_param,
					loc_3.y * coordinate_param,
					loc_3.z * coordinate_param * 0.25,
					frame_param));
				glm::vec3 loc_4 = glm::vec4(x, y - span, z, 0) * rotation;
				auto noise_4 = ofNoise(glm::vec4(
					loc_4.x * coordinate_param,
					loc_4.y * coordinate_param,
					loc_4.z * coordinate_param * 0.25,
					frame_param));

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec4(x - span * 0.5, y - span * 0.5, z, 0) * rotation);
				vertices.push_back(glm::vec4(x + span * 0.5, y - span * 0.5, z, 0) * rotation);
				vertices.push_back(glm::vec4(x + span * 0.5, y + span * 0.5, z, 0) * rotation);
				vertices.push_back(glm::vec4(x - span * 0.5, y + span * 0.5, z, 0) * rotation);

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
	this->cam.setPosition(glm::vec3(0, 0, 500));

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