#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 525, true, true, true);

}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 25 == 0) {

		this->location_list.clear();

		ofFbo fbo;
		fbo.allocate(ofGetWidth(), ofGetHeight());
		fbo.begin();
		ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
		ofClear(0);
		ofSetColor(0);

		string word = ofGetFrameNum() % 50 == 0 ? "2" : "5";
		font.drawString(word, font.stringWidth(word) * -0.5, font.stringHeight(word) - 300);

		fbo.end();

		auto span = 20;
		ofPixels pixels;
		fbo.readToPixels(pixels);
		for (int x = 60; x < 700; x += span) {

			for (int y = 0; y < 720; y += span) {

				ofColor color = pixels.getColor(x, y);
				if (color != ofColor(0, 0)) {

					this->location_list.push_back(glm::vec3(x - ofGetWidth() * 0.5, y - ofGetHeight() * 0.45, 0));
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int span = 20;
	ofColor color;
	for (auto& location : this->location_list) {

		auto x = location.x;
		auto y = location.y;

		auto p = ofGetFrameNum() % 25;
		auto next_p = (ofGetFrameNum() + 1) % 25;

		auto param = p < 5 ? 0 : p < 15 ? ofMap(p, 5, 15, 0, 1) : p < 20 ? 1 : ofMap(p, 20, 25, 1, 0);
		auto next_param = next_p < 5 ? 0 : next_p < 15 ? ofMap(next_p, 5, 15, 0, 1) : next_p < 20 ? 1 : ofMap(next_p, 20, 25, 1, 0);

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

		auto param_x = ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.01), 0, 1, span * -8, span * 8) * param;
		auto param_y = ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.01), 0, 1, span * -8, span * 8) * param;

		auto next_param_x = ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + 1) * 0.01), 0, 1, span * -8, span * 8) * next_param;
		auto next_param_y = ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + 1) * 0.01), 0, 1, span * -8, span * 8) * next_param;

		color.setHsb(0, 255, ofMap(p, 0, 25, 255, 100));

		ofSetColor(0);
		ofFill();
		ofDrawCircle(x + param_x, y + param_y, span * 0.35);

		ofSetColor(color);
		ofNoFill();
		ofDrawCircle(x + param_x, y + param_y, span * 0.35);
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 50;
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