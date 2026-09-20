#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 0.25;
	float theta_deg_step = 0.25;
	float noise_gap = 2;
	float noise_step = 0.035;
	float noise_threshold_1 = 0.47;
	float noise_threshold_2 = 0.53;

	for (float radius = 500; radius <= 550; radius += 25) {

		float noise_radius = radius * 0.0075;

		for (float phi_deg = 0; phi_deg < 180; phi_deg += phi_deg_step) {

			for (float theta_deg = 30; theta_deg <= 150; theta_deg += theta_deg_step) {

				auto noise_value = ofNoise(
					cos(phi_deg * DEG_TO_RAD) * noise_gap,
					sin(phi_deg * DEG_TO_RAD) * noise_gap,
					cos(theta_deg * DEG_TO_RAD) * noise_gap,
					noise_radius + ofGetFrameNum() * noise_step);

				if (noise_value < noise_threshold_1 || noise_value > noise_threshold_2) { continue; }

				auto noise_value_1 = ofNoise(
					cos(phi_deg * DEG_TO_RAD) * noise_gap,
					sin(phi_deg * DEG_TO_RAD) * noise_gap,
					cos((theta_deg - theta_deg_step) * DEG_TO_RAD) * noise_gap,
					noise_radius + ofGetFrameNum() * noise_step);
				auto noise_value_2 = ofNoise(
					cos((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_gap,
					sin((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_gap,
					cos(theta_deg * DEG_TO_RAD) * noise_gap,
					noise_radius + ofGetFrameNum() * noise_step);
				auto noise_value_3 = ofNoise(
					cos((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_gap,
					sin((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_gap,
					cos(theta_deg * DEG_TO_RAD) * noise_gap,
					noise_radius + ofGetFrameNum() * noise_step);
				auto noise_value_4 = ofNoise(
					cos(phi_deg * DEG_TO_RAD) * noise_gap,
					sin(phi_deg * DEG_TO_RAD) * noise_gap,
					cos((theta_deg + theta_deg_step) * DEG_TO_RAD) * noise_gap,
					noise_radius + ofGetFrameNum() * noise_step);

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

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
				this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

				if (noise_value_1 < noise_threshold_1 || noise_value_1 > noise_threshold_2) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[1]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_value_2 < noise_threshold_1 || noise_value_2 > noise_threshold_2) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[2]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_value_3 < noise_threshold_1 || noise_value_3 > noise_threshold_2) {

					this->line.addVertex(vertices[1]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_value_4 < noise_threshold_1 || noise_value_4 > noise_threshold_2) {

					this->line.addVertex(vertices[2]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	ofSetColor(0);
	this->face.draw();

	ofSetColor(255);
	this->line.draw();

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