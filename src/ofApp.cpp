#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(255);
	ofNoFill();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	noise_param += 0.02;
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5 + glm::vec2(0, -50));

	ofColor color;
	vector<ofColor> color_list;
	for (int value = 0; value < 256; value += 64) {

		color.setHsb(value, 180, 255);
		color_list.push_back(color);
	}

	float scale_span = 0.05;
	float deg_span = 0.05;
	float noise_seed = ofRandom(1000);
	for (int i = 0; i < color_list.size(); i++) {

		ofMesh mesh;
		noise_seed += 0.5;
		for (float scale = 0; scale < 20; scale += scale_span) {

			for (float deg = 0; deg < 360; deg += deg_span) {

				auto noise_location = this->make_point((deg + deg_span * 0.5) * DEG_TO_RAD) * (scale + scale_span * 0.5);
				auto noise_value = ofNoise(noise_seed, noise_location.x * 0.005, noise_location.y * 0.005 + noise_param);

				if (noise_value > 0.45 && noise_value < 0.55) {

					mesh.addVertex(this->make_point(deg * DEG_TO_RAD) * scale);
					mesh.addVertex(this->make_point((deg + deg_span) * DEG_TO_RAD) * scale);
					mesh.addVertex(this->make_point((deg + deg_span) * DEG_TO_RAD) * (scale + scale_span));
					mesh.addVertex(this->make_point(deg * DEG_TO_RAD) * (scale + scale_span));

					mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 2); mesh.addIndex(mesh.getNumVertices() - 3);
					mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 3); mesh.addIndex(mesh.getNumVertices() - 4);

					mesh.addColor(color_list[i]);
					mesh.addColor(color_list[i]);
					mesh.addColor(color_list[i]);
					mesh.addColor(color_list[i]);
				}
			}
		}
		mesh.draw();
	}

	ofBeginShape();
	for (float deg = 0; deg < 360; deg += 1) {

		ofVertex(this->make_point(deg * DEG_TO_RAD) * 20);
	}
	ofEndShape(true);

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 2;
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
// Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec3 ofApp::make_point(float theta) {

	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec3(x, -y, 0);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}