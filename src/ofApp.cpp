#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(360 - 60);

	float R = 200;
	float r = 50;
	float u_span = 5;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	for (int r = 100; r > 0; r -= 10) {

		int v_start = ofMap(ofNoise(r * 0.0075 + ofGetFrameNum() * 0.01), 0, 1, -720, 720);
		int v_end = v_start + 16;
		int v_span = 1;

		for (int v = v_start; v <= v_end; v += v_span) {

			for (int u = 0; u < 180; u += u_span) {

				face.addVertex(this->make_point(R, r, u - u_span * 0.5, v - v_span * 0.5));
				face.addVertex(this->make_point(R, r, u + u_span * 0.5, v - v_span * 0.5));
				face.addVertex(this->make_point(R, r, u + u_span * 0.5, v + v_span * 0.5));
				face.addVertex(this->make_point(R, r, u - u_span * 0.5, v + v_span * 0.5));

				line.addVertex(this->make_point(R, r, u - u_span * 0.51, v - v_span * 0.51));
				line.addVertex(this->make_point(R, r, u + u_span * 0.51, v - v_span * 0.51));
				line.addVertex(this->make_point(R, r, u + u_span * 0.51, v + v_span * 0.51));
				line.addVertex(this->make_point(R, r, u - u_span * 0.51, v + v_span * 0.51));

				for (int i = 0; i < 4; i++) {

					face.addColor(ofColor(39));
					line.addColor(ofColor(239));
				}

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				if (u == 0) {

					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
				}

				if (u == 180) {

					line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);
				}

				if (v == v_start) {

					line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);
				}

				if (v == v_end) {

					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
				}
			}
		}
	}

	face.draw();
	line.drawWireframe();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 250;
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
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}