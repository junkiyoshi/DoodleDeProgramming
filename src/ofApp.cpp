#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_DISABLED);

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	float span = 50;
	for (int x = -3000; x <= 3000; x += span) {

		for (int y = -2400; y <= 2400; y += span) {

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(x, y, 0));
			vertices.push_back(glm::vec3(x + span, y, 0));
			vertices.push_back(glm::vec3(x + span, y + span, 0));
			vertices.push_back(glm::vec3(x, y + span, 0));

			this->face.addVertices(vertices);

			this->face.addIndex(this->face.getNumVertices() - 1);
			this->face.addIndex(this->face.getNumVertices() - 4);
			this->face.addIndex(this->face.getNumVertices() - 3);

			this->face.addIndex(this->face.getNumVertices() - 1);
			this->face.addIndex(this->face.getNumVertices() - 2);
			this->face.addIndex(this->face.getNumVertices() - 3);

			this->frame.addVertices(vertices);

			this->frame.addIndex(this->frame.getNumVertices() - 1);
			this->frame.addIndex(this->frame.getNumVertices() - 2);

			this->frame.addIndex(this->frame.getNumVertices() - 1);
			this->frame.addIndex(this->frame.getNumVertices() - 4);

			this->frame.addIndex(this->frame.getNumVertices() - 3);
			this->frame.addIndex(this->frame.getNumVertices() - 4);

			this->frame.addIndex(this->frame.getNumVertices() - 3);
			this->frame.addIndex(this->frame.getNumVertices() - 2);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	auto index = 0;
	for (auto& vertex : this->face.getVertices()) {

		auto noise_value = ofNoise(glm::distance(glm::vec3(0, 2700, 0), vertex) * 0.0008 - ofGetFrameNum() * 0.05, vertex.x * 0.00025, vertex.y * 0.00025);
		vertex.z = pow(ofMap(noise_value, 0, 1, 0, 28), 2);

		this->frame.setVertex(index++, vertex);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	ofColor color;
	color.setHsb(ofMap(ofGetFrameNum() % 500, 0, 500, 0, 255), 180, 255);

	ofSetColor(color);
	this->face.draw();

	ofSetColor(0);
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