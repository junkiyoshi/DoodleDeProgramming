#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
	for (auto radius = 5; radius < 360; radius += 5) {

		this->setRingToMesh(this->face, this->frame, glm::vec3(), radius, 3, 60, noise_seed, ofColor(0), ofColor(255));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(180 + 90);

	this->face.draw();

	this->frame.drawWireframe();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 250;
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
void ofApp::setRingToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float radius, float width, float height, glm::vec2 noise_seed, ofColor face_color, ofColor frame_color) {

	auto noise_value = glm::vec2(
		ofNoise(noise_seed.x, radius * 0.005 + ofGetFrameNum() * 0.01), 
		ofNoise(noise_seed.y, radius * 0.005 + ofGetFrameNum() * 0.01));

	auto angle_x = ofMap(noise_value.x, 0, 1, -PI * 0.5, PI * 0.5);
	auto angle_y = ofMap(noise_value.y, 0, 1, -PI * 0.5, PI * 0.5);

	auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
	auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));

	int max = 10;
	for (int deg = 0; deg < max; deg += 1) {

		auto face_index = face_target.getNumVertices();

		vector<glm::vec3> vertices;
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos(deg * DEG_TO_RAD), (radius + width * 0.5) * sin(deg * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos((deg + 1) * DEG_TO_RAD), (radius + width * 0.5) * sin((deg + 1) * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos((deg + 1) * DEG_TO_RAD), (radius + width * 0.5) * sin((deg + 1) * DEG_TO_RAD), height * 0.5));
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos(deg * DEG_TO_RAD), (radius + width * 0.5) * sin(deg * DEG_TO_RAD), height * 0.5));

		vertices.push_back(glm::vec3((radius - width * 0.5) * cos(deg * DEG_TO_RAD), (radius - width * 0.5) * sin(deg * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius - width * 0.5) * cos((deg + 1) * DEG_TO_RAD), (radius - width * 0.5) * sin((deg + 1) * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius - width * 0.5) * cos((deg + 1) * DEG_TO_RAD), (radius - width * 0.5) * sin((deg + 1) * DEG_TO_RAD), height * 0.5));
		vertices.push_back(glm::vec3((radius - width * 0.5) * cos(deg * DEG_TO_RAD), (radius - width * 0.5) * sin(deg * DEG_TO_RAD), height * 0.5));

		for (auto& vertex : vertices) {

			vertex = location + glm::vec4(vertex, 0) * rotation_y * rotation_x;
		}

		face_target.addVertices(vertices);

		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 2);
		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 3);

		face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
		face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);

		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5);
		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 1);

		face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 6);
		face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 2);

		auto frame_index = frame_target.getNumVertices();

		frame_target.addVertices(vertices);

		frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 1);
		frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 3);
		frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 5);
		frame_target.addIndex(frame_index + 6); frame_target.addIndex(frame_index + 7);

		if (deg == 0) {

			frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 3);
			frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 7);

			frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 4);
			frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 7);
		}

		if (deg == max -1) {

			frame_target.addIndex(frame_index + 1); frame_target.addIndex(frame_index + 2);
			frame_target.addIndex(frame_index + 5); frame_target.addIndex(frame_index + 6);

			frame_target.addIndex(frame_index + 1); frame_target.addIndex(frame_index + 5);
			frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 6);
		}

		for (int i = 0; i < 8; i++) {

			face_target.addColor(face_color);
			frame_target.addColor(frame_color);
		}
	}


}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}