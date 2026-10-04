#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto radius = 24;
	auto x_span = radius * sqrt(3);
	auto flg = true;

	auto x_seed = ofRandom(1000);
	auto y_seed = ofRandom(1000);

	for (float y = 0; y <= 720 + radius; y += radius * 1.5) {

		for (float x = 0; x <= 720 + radius; x += x_span) {

			glm::vec3 location;
			if (flg) {

				location = glm::vec3(x, y, 0);
			}
			else {

				location = glm::vec3(x + (x_span / 2), y, 0);
			}

			auto noise_value = ofNoise(location.x * 0.0025, location.y * 0.0025, ofGetFrameNum() * 0.01, x_seed);
			if (noise_value < 0.4 || noise_value > 0.6) { continue; }

			ofPushMatrix();
			ofTranslate(location);
			ofRotate(90);

			ofBeginShape();
			for (int deg = 0; deg <= 360; deg += 1) {

				int draw_radius = radius * 0.8;
				int param = deg % 60;

				glm::vec2 location;
				if (param == 0) {

					location = glm::vec2(draw_radius * cos(deg * DEG_TO_RAD), draw_radius * sin(deg * DEG_TO_RAD));
				}
				else {

					int p1 = deg / 60;
					int p2 = p1 + 1;

					auto p1_deg = p1 * 60;
					auto p2_deg = p2 * 60;

					auto source = glm::vec2(draw_radius * cos(p1_deg * DEG_TO_RAD), draw_radius * sin(p1_deg * DEG_TO_RAD));
					auto target = glm::vec2(draw_radius * cos(p2_deg * DEG_TO_RAD), draw_radius * sin(p2_deg * DEG_TO_RAD));

					location = source + ((target - source) / 60 * param);
				}

				ofVertex(location);
			}
			ofEndShape(false);

			ofPopMatrix();
		}
		flg = !flg;
	}

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