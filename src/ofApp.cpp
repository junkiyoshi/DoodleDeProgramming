#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);

	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int radius = 15;
	int len = 7;
	int gap_x = radius * cos(0 * DEG_TO_RAD);
	int gap_y = radius + (radius - cos(210 * DEG_TO_RAD)) * 0.6;
	ofColor color;

	auto flag = false;
	for (int y = -gap_y * 10; y <= gap_y * 10; y += gap_y) {

		ofPushMatrix();
		if (flag = !flag) {
		
			ofTranslate(gap_x, 0, 0);
		}

		for (int x = -gap_x * 12 ; x <= gap_x * 12; x += gap_x) {

			color.setHsb(ofMap(x, -gap_x * 12, gap_x * 12, 0, 255), 180, 255);

			for (int z = 0; z <= 50; z += 10) {

				auto noise_param = ofNoise(x * 0.005, y * 0.005, z * 0.005 + ofGetFrameNum() * 0.01);

				if (noise_param < 0.35 || noise_param > 0.65) { continue; }

				auto alpha = 255;
				int flag = abs(x) % (gap_x * 2) == 0;
				int deg_start = flag ? 90 : 270;
				int tmp_y = flag ? y : y + (radius - cos(210 * DEG_TO_RAD)) * 0.5;

				ofFill();
				ofSetColor(ofColor(color, alpha));

				ofBeginShape();

				for (int deg = deg_start; deg < deg_start + 360; deg += 120) {

					ofVertex(glm::vec3(x + radius * cos(deg * DEG_TO_RAD), tmp_y + radius * sin(deg * DEG_TO_RAD), z));
				}

				ofNextContour(true);

				for (int deg = deg_start; deg < deg_start + 360; deg += 120) {

					ofVertex(glm::vec3(x + (radius - len) * cos(deg * DEG_TO_RAD), tmp_y + (radius - len) * sin(deg * DEG_TO_RAD), z));
				}

				ofEndShape(true);


				ofNoFill();
				ofSetColor(ofColor(239, alpha));

				ofBeginShape();

				for (int deg = deg_start; deg < deg_start + 360; deg += 120) {

					ofVertex(glm::vec3(x + radius * cos(deg * DEG_TO_RAD), tmp_y + radius * sin(deg * DEG_TO_RAD), z));
				}

				ofNextContour(true);

				for (int deg = deg_start; deg < deg_start + 360; deg += 120) {

					ofVertex(glm::vec3(x + (radius - len) * cos(deg * DEG_TO_RAD), tmp_y + (radius - len) * sin(deg * DEG_TO_RAD), z));
				}

				ofEndShape(true);
			}
		}

		ofPopMatrix();
	}

	this->cam.end();

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
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}