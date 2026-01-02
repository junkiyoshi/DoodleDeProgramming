#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofNoFill();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 250, true, true, true);

	ofFbo fbo;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofClear(0);
	ofSetColor(0);

	auto word = "HNY";
	font.drawString(word, font.stringWidth(word) * -0.5, font.stringHeight(word) - 300);

	fbo.end();
	auto span = 2;
	ofPixels pixels;
	fbo.readToPixels(pixels);
	for (int x = 0; x < 700; x += span) {

		for (int y = 0; y < 720; y += span) {

			ofColor color = pixels.getColor(x, y);
			if (color != ofColor(0, 0)) {

				this->font_location_list.push_back(glm::vec3(x - ofGetWidth() * 0.5, y - ofGetHeight() * 0.25, 0));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		this->radius_list[i] += this->speed_list[i];

		if (this->radius_list[i] > this->max_radius_list[i]) {

			this->location_list.erase(this->location_list.begin() + i);
			this->radius_list.erase(this->radius_list.begin() + i);
			this->speed_list.erase(this->speed_list.begin() + i);
			this->max_radius_list.erase(this->max_radius_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}

	ofColor color;
	for (int i = 0; i < 30; i++) {

		int rnd_index = ofRandom(this->font_location_list.size());

		auto location = this->font_location_list[rnd_index];
		this->location_list.push_back(location);
		this->radius_list.push_back(1);
		this->speed_list.push_back(0.5);
		this->max_radius_list.push_back(13);
		color.setHsb(ofRandom(255), 180, 255);
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		if (this->radius_list[i] < this->max_radius_list[i] * 0.5) {

			ofSetColor(this->color_list[i]);
		}
		else {

			ofSetColor(ofColor(this->color_list[i], ofMap(this->radius_list[i], this->max_radius_list[i] * 0.5, this->max_radius_list[i], 255, 0)));
		}

		ofNoFill();
		ofDrawCircle(this->location_list[i], this->radius_list[i]);

		ofFill();
		ofDrawCircle(this->location_list[i], this->radius_list[i] * 0.4);
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