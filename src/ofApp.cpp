#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofSetColor(0);
	ofFill();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 400, true, true, true);

	ofFbo fbo;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofClear(0);
	ofSetColor(0);

	auto word = "25";
	this->font.drawString(word, font.stringWidth(word) * -0.5, font.stringHeight(word) - 200);

	fbo.end();
	auto span = 12;
	ofPixels pixels;
	fbo.readToPixels(pixels);
	for (int x = 0; x < 720; x += span) {

		for (int y = 0; y < 720; y += span) {

			ofColor color = pixels.getColor(x, y);
			if (color != ofColor(0, 0)) {

				this->font_location_list.push_back(glm::vec3(x - ofGetWidth() * 0.5, y - ofGetHeight() * 0.5, 0));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->font_location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->font_location_list[i]);

		auto span = 12;
		auto len = span / 2;
		auto noise_span = 0.02;
		auto noise_value = ofNoise(this->font_location_list[i].x * noise_span, this->font_location_list[i].y * noise_span, ofGetFrameNum() * 0.005);

		auto loc_1 = glm::vec2((this->font_location_list[i].x - span), this->font_location_list[i].y - span);
		auto noise_1 = ofNoise(loc_1.x * noise_span, loc_1.y * noise_span, ofGetFrameNum() * 0.005);
		auto find_loc_1 = std::find(this->font_location_list.begin(), this->font_location_list.end(), loc_1) == this->font_location_list.end();

		auto loc_2 = glm::vec2((this->font_location_list[i].x + span), this->font_location_list[i].y + span);
		auto noise_2 = ofNoise(loc_2.x * noise_span, loc_2.y * noise_span, ofGetFrameNum() * 0.005);
		auto find_loc_2 = std::find(this->font_location_list.begin(), this->font_location_list.end(), loc_2) == this->font_location_list.end();

		auto loc_3 = glm::vec2((this->font_location_list[i].x - span), this->font_location_list[i].y + span);
		auto noise_3 = ofNoise(loc_3.x * noise_span, loc_3.y * noise_span, ofGetFrameNum() * 0.005);
		auto find_loc_3 = std::find(this->font_location_list.begin(), this->font_location_list.end(), loc_3) == this->font_location_list.end();

		auto loc_4 = glm::vec2((this->font_location_list[i].x + span), this->font_location_list[i].y - span);
		auto noise_4 = ofNoise(loc_4.x * noise_span, loc_4.y * noise_span, ofGetFrameNum() * 0.005);
		auto find_loc_4 = std::find(this->font_location_list.begin(), this->font_location_list.end(), loc_4) == this->font_location_list.end();

		if (noise_value <= 0.5) {

			ofDrawLine(-len, -len, len, len);

			if (noise_1 > 0.5 || find_loc_1) { ofDrawCircle(-len, -len, 3); }
			if (noise_2 > 0.5 || find_loc_2) { ofDrawCircle(len, len, 3); }

		}
		else {

			ofDrawLine(-len, len, len, -len);

			if (noise_3 <= 0.5 || find_loc_3) { ofDrawCircle(-len, len, 3); }
			if (noise_4 <= 0.5 || find_loc_4) { ofDrawCircle(len, -len, 3); }
		}


		ofPopMatrix();
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 25;
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