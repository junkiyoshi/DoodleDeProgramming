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
	float noise_threshold = 0.53;
	float noise_span = 0.5;
	float radius_span = 0.015;

	ofColor face_color(255, 0, 0), line_color(0);

	for (float radius = 230; radius > 30; radius -= 5) {

		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

			for (float theta_deg = 40; theta_deg <= 140; theta_deg += theta_deg_step) {

				auto noise_value = ofNoise(
					cos(phi_deg * DEG_TO_RAD) * noise_span,
					sin(phi_deg * DEG_TO_RAD) * noise_span,
					cos(theta_deg * DEG_TO_RAD) * noise_span,
					radius * radius_span + ofGetFrameNum() * 0.04);

				if (noise_value < noise_threshold) { continue; }

				auto noise_value_1 = ofNoise(
					cos(phi_deg * DEG_TO_RAD) * noise_span,
					sin(phi_deg * DEG_TO_RAD) * noise_span,
					cos((theta_deg - theta_deg_step) * DEG_TO_RAD) * noise_span,
					radius * radius_span + ofGetFrameNum() * 0.04);
				auto noise_value_2 = ofNoise(
					cos((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_span,
					sin((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_span,
					cos(theta_deg * DEG_TO_RAD) * noise_span,
					radius * radius_span + ofGetFrameNum() * 0.04);
				auto noise_value_3 = ofNoise(
					cos((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_span,
					sin((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_span,
					cos(theta_deg * DEG_TO_RAD) * noise_span,
					radius * radius_span + ofGetFrameNum() * 0.04);
				auto noise_value_4 = ofNoise(
					cos(phi_deg * DEG_TO_RAD) * noise_span,
					sin(phi_deg * DEG_TO_RAD) * noise_span,
					cos((theta_deg + theta_deg_step) * DEG_TO_RAD) * noise_span,
					radius * radius_span + ofGetFrameNum() * 0.04);

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

				if (noise_value_1 < noise_threshold || theta_deg == 40) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[1]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				if (noise_value_2 < noise_threshold) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[2]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				if (noise_value_3 < noise_threshold) {

					this->line.addVertex(vertices[1]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				if (noise_value_4 < noise_threshold || theta_deg == 140) {

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
	ofRotateX(310);
	ofRotateZ(ofGetFrameNum() * 0.72);

	this->face.draw();
	this->line.draw();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 10;
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