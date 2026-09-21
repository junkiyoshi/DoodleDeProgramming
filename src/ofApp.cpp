#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 5;
	float theta_deg_step = 5;
	float noise_gap = 1;
	float noise_step = 0.035;
	float noise_threshold_1 = 0.45;
	float noise_threshold_2 = 0.55;

	for (float radius = 200; radius <= 300; radius += 5) {

		auto noise_radius = radius * 0.001;

		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

			for (float theta_deg = 60; theta_deg <= 120; theta_deg += theta_deg_step) {

				auto noise_value = ofNoise(
					noise_radius + cos(phi_deg * DEG_TO_RAD) * noise_gap,
					noise_radius + sin(phi_deg * DEG_TO_RAD) * noise_gap,
					noise_radius + cos(theta_deg * DEG_TO_RAD) * noise_gap,
					ofGetFrameNum() * noise_step);

				if (noise_value < noise_threshold_1 || noise_value > noise_threshold_2) { continue; }

				auto noise_value_1 = ofNoise(
					noise_radius + cos(phi_deg * DEG_TO_RAD) * noise_gap,
					noise_radius + sin(phi_deg * DEG_TO_RAD) * noise_gap,
					noise_radius + cos((theta_deg - theta_deg_step) * DEG_TO_RAD) * noise_gap,
					ofGetFrameNum() * noise_step);
				auto noise_value_2 = ofNoise(
					noise_radius + cos((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_gap,
					noise_radius + sin((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_gap,
					noise_radius + cos(theta_deg * DEG_TO_RAD) * noise_gap,
					ofGetFrameNum() * noise_step);
				auto noise_value_3 = ofNoise(
					noise_radius + cos((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_gap,
					noise_radius + sin((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_gap,
					noise_radius + cos(theta_deg * DEG_TO_RAD) * noise_gap,
					ofGetFrameNum() * noise_step);
				auto noise_value_4 = ofNoise(
					noise_radius + cos(phi_deg * DEG_TO_RAD) * noise_gap,
					noise_radius + sin(phi_deg * DEG_TO_RAD) * noise_gap,
					noise_radius + cos((theta_deg + theta_deg_step) * DEG_TO_RAD) * noise_gap,
					ofGetFrameNum() * noise_step);

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

				if (noise_value_1 < noise_threshold_1 || noise_value_1 > noise_threshold_2 || theta_deg == 60) {

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

				if (noise_value_4 < noise_threshold_1 || noise_value_4 > noise_threshold_2 || theta_deg == 120) {

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
	ofRotateZ(ofGetFrameNum() * 0.18);

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