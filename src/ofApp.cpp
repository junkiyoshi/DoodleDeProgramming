#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->hexagon_height = 32;
	this->hexagon_width = 6;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);
	ofRotateZ(ofGetFrameNum() * 0.72);

	for (int deg = 0; deg < 360; deg += 10) {

		int number_index = ofMap(ofNoise(cos(deg * DEG_TO_RAD) * 2, sin(deg * DEG_TO_RAD) * 2, ofGetFrameNum() * 0.015), 0, 1, 0, 10);

		ofPushMatrix();
		ofRotate(deg);

		ofTranslate(glm::vec3(0, 300, 0));
		ofRotateX(90);

		ofColor color;
		color.setHsb(ofMap(deg, 0, 360, 0, 255), 180, 255);

		this->draw_digital(glm::vec3(0), number_index, color);

		ofPopMatrix();
	}

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
void ofApp::draw_digital(glm::vec3 location, int number_index, ofColor color) {

	vector<pair<glm::vec3, float>> part_list = {
		std::make_pair<glm::vec3, float>(location + glm::vec2(0, -this->hexagon_height), 90),
		std::make_pair<glm::vec3, float>(location + glm::vec2(this->hexagon_height * -0.5, this->hexagon_height * 0.5), 0),
		std::make_pair<glm::vec3, float>(location + glm::vec2(this->hexagon_height * 0.5, this->hexagon_height * 0.5), 0),
		std::make_pair<glm::vec3, float>(location + glm::vec2(0, 0), 90),
		std::make_pair<glm::vec3, float>(location + glm::vec2(this->hexagon_height * -0.5, this->hexagon_height * -0.5), 0),
		std::make_pair<glm::vec3, float>(location + glm::vec2(this->hexagon_height * 0.5, this->hexagon_height * -0.5), 0),
		std::make_pair<glm::vec3, float>(location + glm::vec2(0, this->hexagon_height), 90)
	};

	vector<vector<int>> index_list = {
		{ 0, 1, 2, 4, 5, 6 },
		{ 2, 5 },
		{ 0, 1, 3, 5, 6 },
		{ 0, 2, 3, 5, 6 },
		{ 2, 3, 4, 5 },
		{ 0, 2, 3, 4, 6 },
		{ 0, 1, 2, 3, 4, 6 },
		{ 0, 2, 5 },
		{ 0, 1, 2, 3, 4, 5, 6 },
		{ 0, 2, 3, 4, 5, 6 },
	};

	for (auto& index : index_list[number_index]) {

		this->draw_hexagon(part_list[index].first, part_list[index].second, color);
	}
}

//--------------------------------------------------------------
void ofApp::draw_hexagon(glm::vec3 location, float deg, ofColor color) {

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(deg);

	vector<glm::vec2> vertices;
	vertices.push_back(glm::vec2(this->hexagon_width * -0.4, this->hexagon_height * -0.4));
	vertices.push_back(glm::vec2(this->hexagon_width * -0.4, this->hexagon_height * 0.4));
	vertices.push_back(glm::vec2(0, this->hexagon_height * 0.5));
	vertices.push_back(glm::vec2(this->hexagon_width * 0.4, this->hexagon_height * 0.4));
	vertices.push_back(glm::vec2(this->hexagon_width * 0.4, this->hexagon_height * -0.4));
	vertices.push_back(glm::vec2(0, this->hexagon_height * -0.5));

	ofFill();
	ofSetColor(0);

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofNoFill();
	ofSetColor(color);

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}