#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	//ofSetLineWidth(2);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int theta = 90;
	int radius_span = 10;
	for (int base_x = -430; base_x < 430; base_x += 860) {

		for (int radius = 30; radius <= 360; radius += radius_span) {

			auto noise_value = ofNoise(radius * 0.002 - ofGetFrameNum() * 0.015);
			float angle;
			glm::highp_mat4 rotation;
			auto face_color = ofColor(0);
			auto frame_color = ofColor(0);

			if (noise_value < 0.55) {

				angle = ofMap(noise_value, 0, 0.55, -PI * 2, PI * 2);
				rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 1, 0));
				frame_color.setHsb(ofMap(radius, 30, 360, 0, 255), 100, 255);
			}

			for (int phi = 0; phi < 360; phi += 3) {

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(
					radius * cos(phi * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					radius * sin(phi * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					radius * cos((theta + 3) * DEG_TO_RAD)
				));
				vertices.push_back(glm::vec3(
					radius * cos((phi + 3) * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					radius * sin((phi + 3) * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					radius * cos((theta + 3) * DEG_TO_RAD)
				));
				vertices.push_back(glm::vec3(
					radius * cos((phi + 3) * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					radius * sin((phi + 3) * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					radius * cos((theta - 3) * DEG_TO_RAD)
				));
				vertices.push_back(glm::vec3(
					radius * cos(phi * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					radius * sin(phi * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					radius * cos((theta - 3) * DEG_TO_RAD)
				));

				vertices.push_back(glm::vec3(
					(radius - radius_span) * cos(phi * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					(radius - radius_span) * sin(phi * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					radius * cos((theta + 3) * DEG_TO_RAD)
				));
				vertices.push_back(glm::vec3(
					(radius - radius_span) * cos((phi + 3) * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					(radius - radius_span) * sin((phi + 3) * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					radius * cos((theta + 3) * DEG_TO_RAD)
				));
				vertices.push_back(glm::vec3(
					(radius - radius_span) * cos((phi + 3) * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					(radius - radius_span) * sin((phi + 3) * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					radius * cos((theta - 3) * DEG_TO_RAD)
				));
				vertices.push_back(glm::vec3(
					(radius - radius_span) * cos(phi * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					(radius - radius_span) * sin(phi * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					radius * cos((theta - 3) * DEG_TO_RAD)
				));

				for (auto& vertex : vertices) {

					vertex += glm::vec3(base_x, 0, 0);
					vertex = glm::vec4(vertex, 0) * rotation;
				}

				auto frame_index = this->frame.getNumVertices();

				this->face.addVertices(vertices);
				this->frame.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				this->face.addIndex(index + 4); this->face.addIndex(index + 5); this->face.addIndex(index + 6);
				this->face.addIndex(index + 4); this->face.addIndex(index + 6); this->face.addIndex(index + 7);

				this->face.addIndex(index + 0); this->face.addIndex(index + 4); this->face.addIndex(index + 5);
				this->face.addIndex(index + 0); this->face.addIndex(index + 5); this->face.addIndex(index + 1);

				this->face.addIndex(index + 2); this->face.addIndex(index + 6); this->face.addIndex(index + 7);
				this->face.addIndex(index + 2); this->face.addIndex(index + 7); this->face.addIndex(index + 3);

				this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
				this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);

				this->frame.addIndex(index + 4); this->frame.addIndex(index + 5);
				this->frame.addIndex(index + 6); this->frame.addIndex(index + 7);

				for (int i = 0; i < vertices.size(); i++) {

					this->face.addColor(face_color);
					this->frame.addColor(frame_color);
				}
			}
		}
	}
}


//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->face.draw();
	this->frame.drawWireframe();

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