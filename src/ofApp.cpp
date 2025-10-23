#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5 + 100);
	ofRotate(270);

	ofColor color;
	for (int radius = 0; radius <= 400; radius += 10) {

		int deg_start = radius * 0.5 + ofGetFrameNum() * 2.16;
		for (int deg = deg_start; deg < deg_start + 360; deg += 90) {

			vector<glm::vec2> vertices;
			for (int tmp_deg = deg; tmp_deg <= deg + 80; tmp_deg += 1) {

				vertices.push_back(glm::vec2(this->make_point(radius, tmp_deg)));
			}

			color.setHsb(ofMap(deg, deg_start, deg_start + 360, 0, 255), 255, 255);

			ofFill();
			ofSetColor(239);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(color);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 150;
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
glm::vec2 ofApp::make_point(int radius, int deg) {

	deg = deg % 360;

	int deg_a = (deg / 120) * 120;
	int deg_b = deg_a + 120;

	int remainder = deg % 120;
	int diff = deg - deg_a;

	auto point_a = glm::vec2(radius * cos(deg_a * DEG_TO_RAD), radius * sin(deg_a * DEG_TO_RAD));
	auto point_b = glm::vec2(radius * cos(deg_b * DEG_TO_RAD), radius * sin(deg_b * DEG_TO_RAD));
	auto distance = point_b - point_a;

	return point_a + (distance / 120) * diff;
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}