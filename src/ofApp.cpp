#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->noise_param += 0.01;

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 3;
	float theta_deg_step = 3;
	float theta_start = 80;
	float theta_end = 100;
	float threshold_1 = 0.45;
	float threshold_2 = 0.55;
	float noise_spam = 5;

	for (float radius = 250; radius <= 300; radius += 5) {

		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

			for (float theta_deg = theta_start; theta_deg <= theta_end; theta_deg += theta_deg_step) {

				auto noise_value = ofNoise(
					radius * 0.001 * cos(phi_deg * DEG_TO_RAD) * noise_spam,
					radius * 0.001 * sin(phi_deg * DEG_TO_RAD) * noise_spam,
					radius * 0.001 * cos(theta_deg * DEG_TO_RAD) * noise_spam,
					this->noise_param);

				if (noise_value < threshold_1 || noise_value > threshold_2) { continue; }

				auto noise_value_1 = ofNoise(
					radius * 0.001 * cos(phi_deg * DEG_TO_RAD) * noise_spam,
					radius * 0.001 * sin(phi_deg * DEG_TO_RAD) * noise_spam,
					radius * 0.001 * cos((theta_deg - theta_deg_step) * DEG_TO_RAD) * noise_spam,
					this->noise_param);
				auto noise_value_2 = ofNoise(
					radius * 0.001 * cos((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_spam,
					radius * 0.001 * sin((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_spam,
					radius * 0.001 * cos(theta_deg * DEG_TO_RAD) * noise_spam,
					this->noise_param);
				auto noise_value_3 = ofNoise(
					radius * 0.001 * cos((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_spam,
					radius * 0.001 * sin((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_spam,
					radius * 0.001 * cos(theta_deg * DEG_TO_RAD) * noise_spam,
					this->noise_param);
				auto noise_value_4 = ofNoise(
					radius * 0.001 * cos(phi_deg * DEG_TO_RAD) * noise_spam,
					radius * 0.001 * sin(phi_deg * DEG_TO_RAD) * noise_spam,
					radius * 0.001 * cos((theta_deg + theta_deg_step) * DEG_TO_RAD) * noise_spam,
					this->noise_param);

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

				if ((noise_value_1 < threshold_1 || noise_value_1 > threshold_2) || theta_deg == theta_start) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[1]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_value_2 < threshold_1 || noise_value_2 > threshold_2) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[2]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_value_3 < threshold_1 || noise_value_3 > threshold_2) {

					this->line.addVertex(vertices[1]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if ((noise_value_4 < threshold_1 || noise_value_4 > threshold_2) || theta_deg >= theta_end - theta_deg_step) {

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

	ofRotateX(90);
	ofRotateZ(ofGetFrameNum() * 0.05);

	ofSetColor(39);
	this->face.draw();

	ofSetColor(39, 239, 39);
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