#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->seed = ofRandom(39);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 25 < 5) {

		this->seed = ofRandom(10000);
	}

	ofSeedRandom(this->seed);

	this->sphere_list.clear();

	auto ico_sphere = ofIcoSpherePrimitive(1, 5);
	this->base_location_list = ico_sphere.getMesh().getVertices();

	this->number_of_sphere = 1800;
	while (this->sphere_list.size() < this->number_of_sphere) {

		int index = ofRandom(this->base_location_list.size());
		auto tmp_location = this->base_location_list[index];
		tmp_location = glm::normalize(tmp_location) * ofRandom(0, 100);

		auto radius = this->sphere_list.size() < 130 ? ofRandom(10, 50) : ofRandom(2, 20);

		bool flag = true;
		for (int i = 0; i < this->sphere_list.size(); i++) {

			if (glm::distance(tmp_location, get<1>(this->sphere_list[i])) < get<2>(this->sphere_list[i]) + radius) {

				flag = false;
				break;
			}
		}

		if (flag) {

			ofColor color;
			color.setHsb(ofRandom(255), 180, 255);

			auto size = (radius * 2) / sqrt(3);

			this->sphere_list.push_back(std::make_tuple(color, tmp_location, size));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.72);

	for (int i = 0; i < this->sphere_list.size(); i++) {

		auto location = get<1>(this->sphere_list[i]);
		auto size = get<2>(this->sphere_list[i]);

		ofPushMatrix();
		ofTranslate(location);

		ofRotateZ(ofRandom(360));
		ofRotateY(ofRandom(360));
		ofRotateX(ofRandom(360));

		ofFill();
		ofSetColor(0);
		ofDrawBox(size);

		ofNoFill();
		ofSetColor(get<0>(this->sphere_list[i]));
		ofDrawBox(size);

		ofPopMatrix();
	}

	this->cam.end();

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
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}