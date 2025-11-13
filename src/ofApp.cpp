#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto deg_span = 0.25;
	auto radius_span = 0.25;
	ofColor color;

	for(int i = 0; i < 4; i++){

		ofMesh face;
		color.setHsb(ofMap(i, 0, 4, 0, 255), 180, 255);
		auto noise_seed = ofRandom(1000);

		for (auto deg = 0.f; deg < 360; deg += deg_span) {

			for (auto radius = 30.f; radius <= 1024; radius += radius_span) {

				auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
				auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));

				auto left = glm::vec2(radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD));
				auto right = glm::vec2(radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD));
				auto next_left = glm::vec2((radius + radius_span) * cos((deg + deg_span * 0.5) * DEG_TO_RAD), (radius + radius_span) * sin((deg + deg_span * 0.5) * DEG_TO_RAD));
				auto next_right = glm::vec2((radius + radius_span) * cos((deg - deg_span * 0.5) * DEG_TO_RAD), (radius + radius_span) * sin((deg - deg_span * 0.5) * DEG_TO_RAD));

				auto noise_value = ofNoise(glm::vec3(noise_location * 10, i * 0.1 + radius * 0.001 - ofGetFrameNum() * 0.025));
				auto threshold = 0.25;
				if (noise_value < threshold) {

					face.addVertex(glm::vec3(left, 0));
					face.addVertex(glm::vec3(next_left, 0));
					face.addVertex(glm::vec3(next_right, 0));
					face.addVertex(glm::vec3(right, 0));

					face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
					face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);
				}
			}
		}

		ofSetColor(color);
		face.draw();
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 1;
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