#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(2);

	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int radius = 10;
	int len = 5;
	int gap_x = radius * cos(0 * DEG_TO_RAD);
	int gap_y = radius + (radius - cos(210 * DEG_TO_RAD)) * 0.6;
	ofColor color;

	auto switch_flag = false;
	for (int y = -gap_y * 15; y <= gap_y * 15; y += gap_y) {

		ofPushMatrix();
		if (switch_flag = !switch_flag) {
		
			ofTranslate(gap_x, 0, 0);
		}

		for (int x = -gap_x * 25; x <= gap_x * 25; x += gap_x) {

			color.setHsb(175, 255, 255);

			auto noise_x = x - (switch_flag ? 0 : gap_x);
			auto noise_param = ofNoise(noise_x * 0.008, y * 0.008, ofGetFrameNum() * 0.01);
			
			if (noise_param < 0.35 || noise_param > 0.65) { continue; }

			int flag = abs(x) % (gap_x * 2) == 0;
			int deg_start = flag ? 90 : 270;
			int tmp_y = flag ? y : y + (radius - cos(210 * DEG_TO_RAD)) * 0.5;

			ofFill();
			ofSetColor(color);

			ofBeginShape();

			for (int deg = deg_start; deg < deg_start + 360; deg += 120) {

				ofVertex(glm::vec3(x + radius * cos(deg * DEG_TO_RAD), tmp_y + radius * sin(deg * DEG_TO_RAD), 0));
			}

			ofNextContour(true);

			for (int deg = deg_start; deg < deg_start + 360; deg += 120) {

				ofVertex(glm::vec3(x + (radius - len) * cos(deg * DEG_TO_RAD), tmp_y + (radius - len) * sin(deg * DEG_TO_RAD), 0));
			}

			ofEndShape(true);


			ofNoFill();
			ofSetColor(255);

			ofBeginShape();

			for (int deg = deg_start; deg < deg_start + 360; deg += 120) {

				ofVertex(glm::vec3(x + radius * cos(deg * DEG_TO_RAD), tmp_y + radius * sin(deg * DEG_TO_RAD), 0));
			}

			ofNextContour(true);

			for (int deg = deg_start; deg < deg_start + 360; deg += 120) {

				ofVertex(glm::vec3(x + (radius - len) * cos(deg * DEG_TO_RAD), tmp_y + (radius - len) * sin(deg * DEG_TO_RAD), 0));
			}

			ofEndShape(true);
		}

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
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}