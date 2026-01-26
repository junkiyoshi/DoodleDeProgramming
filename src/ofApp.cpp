#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->font.loadFont("fonts/msgothic.ttc", 28, true, true, true);
	this->word = "junkiyoshi.com ";
}

//--------------------------------------------------------------
void ofApp::update() {


}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 33;
	ofColor color;
	for (int y = 0; y < ofGetWindowHeight() + 33; y += span) {

		int x_start = ofMap(ofNoise(y * 0.1, ofGetFrameNum() * 0.005), 0, 1, 0, 1000);

		for (int i = 0; i < this->word.size() * 2; i++) {

			color.setHsb((int)(ofMap(y, 0, ofGetWindowHeight() + 33, 0, 255) + ofGetFrameNum() * 10) % 255, 100, 255);

			auto x = (int)(x_start + i * span) % 1000 - 100;
			auto location = glm::vec2(x, y);

			ofPushMatrix();
			ofTranslate(location);

			ofPath chara_path = this->font.getCharacterAsPoints(this->word[i % this->word.size()], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();

			ofNoFill();
			ofSetColor(color);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					ofVertex(vertex);
				}
			}
			ofEndShape(true);

			ofPopMatrix();
		}
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 100;
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