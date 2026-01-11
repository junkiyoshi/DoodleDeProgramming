#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	int len = 300;
	int span = 1;

	float angle;
	glm::highp_mat4 rotation;
	for (int i = 0; i <= 6; i++) {

		for (int x = len * -0.5; x < len * 0.5; x += span) {

			for (int y = len * -0.5; y < len * 0.5; y += span) {

				if (i <= 4) {

					angle = PI * 0.5 * i;
					rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 1, 0));
				}

				if (i == 5) {

					angle = PI * 0.5;
					rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));
				}

				if (i == 6) {

					angle = PI * 0.5 * 3;
					rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));
				}

				glm::vec3 noise_location = glm::vec4(x, y, len * 0.5, 0) * rotation;
				auto noise_value = ofNoise(noise_location.x * 0.012, noise_location.y * 0.012, noise_location.z * 0.012, ofGetFrameNum() * 0.001);

				if (noise_value < 0.4 || noise_value > 0.5) {

					continue;
				}

				vector<glm::vec3> vertices;
				vertices.push_back(glm::vec4(x, y, len * 0.5, 0) * rotation);
				vertices.push_back(glm::vec4(x + span, y, len * 0.5, 0) * rotation);
				vertices.push_back(glm::vec4(x + span, y + span, len * 0.5, 0) * rotation);
				vertices.push_back(glm::vec4(x, y + span, len * 0.5, 0) * rotation);
				this->mesh.addVertices(vertices);

				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);


				for (int i = 0; i < 4; i++) {

					if (noise_value > 0.44 && noise_value < 0.46) {

						this->mesh.addColor(ofColor(239, 39, 39));
					}
					else {

						this->mesh.addColor(ofColor(0));
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.44);
	ofRotateX(ofGetFrameNum() * 2.88);

	this->mesh.draw();

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