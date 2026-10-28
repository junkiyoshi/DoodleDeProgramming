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

	float phi_deg_step = 3;
	float theta_deg_step = 2;
	float noise_param = 0.35;
	float threshold = 0.55;
	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

	for (float radius = 50; radius <= 250; radius += 2) {

		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

			for (float theta_deg = 0; theta_deg <= 40; theta_deg += theta_deg_step) {

				float angle_x = ofMap(ofNoise(noise_seed.x, radius * 0.0015 + ofGetFrameNum() * 0.01), 0, 1, PI * -2, PI * 2);
				auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));

				float angle_y = ofMap(ofNoise(noise_seed.y, radius * 0.0015 + ofGetFrameNum() * 0.01), 0, 1, PI * -2, PI * 2);
				auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));

				float angle_z = ofMap(ofNoise(noise_seed.z, radius * 0.0015 + ofGetFrameNum() * 0.01), 0, 1, PI * -2, PI * 2);
				auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 1, 0));

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));

				for (auto& vertex : vertices) {

					vertex = glm::vec4(vertex, 0) * rotation_z * rotation_y * rotation_x;
				}

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
				this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

				for (int k = 0; k < 4; k++) {

					this->face.addColor(ofColor(0));
				}

				if (theta_deg == 40) {

					this->frame.addVertex(vertices[2]);
					this->frame.addVertex(vertices[3]);

					this->frame.addIndex(this->frame.getNumVertices() - 1);
					this->frame.addIndex(this->frame.getNumVertices() - 2);

					this->frame.addColor(ofColor(255, 0, 0));
					this->frame.addColor(ofColor(255, 0, 0));
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->frame.draw();
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