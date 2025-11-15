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

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 0.5;
	float theta_deg_step = 0.5;

	float noise_scale = 2;
	float noise_threshold_start = 0.45;
	float noise_threshold_end = 0.55;

	ofColor line_color = ofColor(255);
	ofColor face_color = ofColor(0);

	for (float radius = 230; radius > 180; radius -= 5) {

		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

			for (float theta_deg = 0; theta_deg <= 180; theta_deg += theta_deg_step) {

				auto noise_value = ofNoise(
					noise_scale * cos(phi_deg * DEG_TO_RAD),
					noise_scale * sin(phi_deg * DEG_TO_RAD),
					noise_scale * cos(theta_deg * DEG_TO_RAD),
					radius * 0.01 + ofGetFrameNum() * 0.05);

				if (noise_threshold_start > noise_value || noise_value > noise_threshold_end) { continue; }

				auto noise_value_1 = ofNoise(
					noise_scale * cos(phi_deg * DEG_TO_RAD),
					noise_scale * sin(phi_deg * DEG_TO_RAD),
					noise_scale * cos((theta_deg - theta_deg_step) * DEG_TO_RAD),
					radius * 0.01 + ofGetFrameNum() * 0.05);
				auto noise_value_2 = ofNoise(
					noise_scale * cos((phi_deg + phi_deg_step) * DEG_TO_RAD),
					noise_scale * sin((phi_deg + phi_deg_step) * DEG_TO_RAD),
					noise_scale * cos(theta_deg * DEG_TO_RAD),
					radius * 0.01 + ofGetFrameNum() * 0.05);
				auto noise_value_3 = ofNoise(
					noise_scale * cos((phi_deg - phi_deg_step) * DEG_TO_RAD),
					noise_scale * sin((phi_deg - phi_deg_step) * DEG_TO_RAD),
					noise_scale * cos(theta_deg * DEG_TO_RAD),
					radius * 0.01 + ofGetFrameNum() * 0.05);
				auto noise_value_4 = ofNoise(
					noise_scale * cos(phi_deg * DEG_TO_RAD),
					noise_scale * sin(phi_deg * DEG_TO_RAD),
					noise_scale * cos((theta_deg + theta_deg_step) * DEG_TO_RAD),
					radius * 0.01 + ofGetFrameNum() * 0.05);

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

				if (noise_threshold_start > noise_value_1 || noise_value_1 > noise_threshold_end) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[1]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				if (noise_threshold_start > noise_value_2 || noise_value_2 > noise_threshold_end) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[2]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				if (noise_threshold_start > noise_value_3 || noise_value_3 > noise_threshold_end) {

					this->line.addVertex(vertices[1]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				if (noise_threshold_start > noise_value_4 || noise_value_4 > noise_threshold_end) {

					this->line.addVertex(vertices[2]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				for (int i = 0; i < vertices.size(); i++) {

					this->face.addColor(face_color);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	this->face.draw();
	this->line.draw();

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
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}