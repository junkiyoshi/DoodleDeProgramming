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

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int v_span = 40;
	int u_span = 90;
	int R = 200;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	int r = 70;
	float noise_seed = ofRandom(1000);
	for (int v = 0; v <= 360; v += v_span * 1.5) {

		int u_start = ofMap(ofNoise(noise_seed, cos(v * DEG_TO_RAD) * 0.35, sin(v * DEG_TO_RAD) * 0.35, ofGetFrameNum() * 0.015), 0, 1, -180, 180);
		int next_u = ofMap(ofNoise(noise_seed, cos((v + v_span * 0.9) * DEG_TO_RAD) * 0.35, sin((v + v_span * 0.9) * DEG_TO_RAD) * 0.35, ofGetFrameNum() * 0.015), 0, 1, -180, 180);
		for (int u = u_start; u < u_start + 360; u += u_span) {

			face.addVertex(this->make_point(R, r, u, v));
			face.addVertex(this->make_point(R, r, u + u_span, v));
			face.addVertex(this->make_point(R, r, next_u + u_span, v + v_span * 0.5));
			face.addVertex(this->make_point(R, r, next_u, v + v_span * 0.5));

			line.addVertex(this->make_point(R, r, u, v));
			line.addVertex(this->make_point(R, r, u + u_span, v));
			line.addVertex(this->make_point(R, r, next_u + u_span, v + v_span * 0.5));
			line.addVertex(this->make_point(R, r, next_u, v + v_span * 0.5));

			ofColor face_color = ofColor(39);
			ofColor line_color = ofColor(239, 39, 39);

			face.addColor(face_color);
			face.addColor(face_color);
			face.addColor(face_color);
			face.addColor(face_color);

			line.addColor(line_color);
			line.addColor(line_color);
			line.addColor(line_color);
			line.addColor(line_color);

			face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
			face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

			line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
			line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);

			line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
			line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);

			if (v > 0) {

				line.addIndex(line.getNumVertices() - 4); line.addIndex(line.getNumVertices() - 17);
			}

			next_u += u_span;

		}
	}

	face.drawFaces();
	line.drawWireframe();

	this->cam.end();

	/*
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