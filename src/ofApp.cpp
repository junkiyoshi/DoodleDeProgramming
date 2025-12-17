#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetColor(239);
	ofSetCircleResolution(60);
	ofNoFill();
	ofEnableDepthTest();

	this->noise_step = ofRandom(1000);
	this->color_param = 0;
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	auto param = ofGetFrameNum() % 50;
	if (param < 20) { 

		this->noise_step += 0; 
	}
	else if (param < 25) {

		this->noise_step += ofMap(param, 20, 25, 0, 0.015); 
		this->color_param += 2;
	}
	else if (param < 45) { 
		
		this->noise_step += 0.015; 
		this->color_param += 2;
	}
	else { 

		this->noise_step += ofMap(param, 45, 50, 0.015, 0);
		this->color_param += 2;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 2.88);

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	ofColor color;
	for (int i = 0; i < 32; i++) {

		ofPushMatrix();
		ofRotateZ(ofMap(ofNoise(noise_seed.z, this->noise_step + i * 0.0075), 0, 1, -360, 360));
		ofRotateY(ofMap(ofNoise(noise_seed.y, this->noise_step + i * 0.0075), 0, 1, -360, 360));
		ofRotateX(ofMap(ofNoise(noise_seed.x, this->noise_step + i * 0.0075), 0, 1, -360, 360));

		color.setHsb((i * 2 + this->color_param) % 255, 200, 255);
		ofSetColor(color);

		auto radius = ofMap(i, 0, 32, 150, 350);

		ofMesh face, line;
		line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

		for (int deg = 0; deg < 360; deg++) {
		
			face.addVertex(glm::vec3() + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
			face.addVertex(glm::vec3() + glm::vec3((radius - 10) * cos(deg * DEG_TO_RAD), (radius - 10) * sin(deg * DEG_TO_RAD), 0));
			face.addVertex(glm::vec3() + glm::vec3((radius - 10) * cos((deg + 1) * DEG_TO_RAD), (radius - 10) * sin((deg + 1) * DEG_TO_RAD), 0));
			face.addVertex(glm::vec3() + glm::vec3(radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), 0));

			face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 4);
			face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

			face.addColor(ofColor(color, 64));
			face.addColor(ofColor(color, 64));
			face.addColor(ofColor(color, 64));
			face.addColor(ofColor(color, 64));

			line.addVertex(glm::vec3() + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
			line.addVertex(glm::vec3() + glm::vec3((radius - 5) * cos(deg * DEG_TO_RAD), (radius - 5) * sin(deg * DEG_TO_RAD), 0));
			line.addVertex(glm::vec3() + glm::vec3((radius - 5) * cos((deg + 1) * DEG_TO_RAD), (radius - 5) * sin((deg + 1) * DEG_TO_RAD), 0));
			line.addVertex(glm::vec3() + glm::vec3(radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), 0));

			line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
			line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);

			line.addColor(color);
			line.addColor(color);
			line.addColor(color);
			line.addColor(color);
		}

		face.draw();
		line.draw();

		ofPopMatrix();
	}

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 300;
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