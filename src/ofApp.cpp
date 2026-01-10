#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableDepthTest();

	this->frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face_mesh.clear();
	this->frame_mesh.clear();

	auto R = 200;
	auto r = 100;
	auto v_span = 2;
	auto u_span = 3;

	int index = 0;
	for (auto v = 0; v < 360; v += v_span) {

		for (auto u = 0; u < 360; u += u_span) {

			vector<glm::vec3> vertices;
			vertices.push_back(this->make_point(R, r, u, v));
			vertices.push_back(this->make_point(R, r, u + u_span, v));
			vertices.push_back(this->make_point(R, r, u + u_span, v + v_span));
			vertices.push_back(this->make_point(R, r, u, v + v_span));

			float noise_value, height;

			auto avg = (vertices[0] + vertices[1] + vertices[2] + vertices[3]) / 4;
			noise_value = ofNoise(glm::vec4(avg * 0.03, ofGetFrameNum() * 0.005));
			height = noise_value > 0.45 && noise_value < 0.55 ? 60 : 0;

			vertices.push_back(this->make_point(R, r - height, u, v));
			vertices.push_back(this->make_point(R, r - height, u + u_span, v));
			vertices.push_back(this->make_point(R, r - height, u + u_span, v + v_span));
			vertices.push_back(this->make_point(R, r - height, u, v + v_span));

			int index = this->face_mesh.getNumVertices();
			this->face_mesh.addVertices(vertices);
			this->frame_mesh.addVertices(vertices);

			// Face Index

			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 2);
			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 3);

			this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 6);
			this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 7);

			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 5);
			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 1);

			this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 6);
			this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 2);

			this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 7);
			this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 7); this->face_mesh.addIndex(index + 3);

			this->face_mesh.addIndex(index + 3); this->face_mesh.addIndex(index + 7); this->face_mesh.addIndex(index + 4);
			this->face_mesh.addIndex(index + 3); this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 0);

			// Frame Index

			this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 1);
			this->frame_mesh.addIndex(index + 1); this->frame_mesh.addIndex(index + 2);
			this->frame_mesh.addIndex(index + 2); this->frame_mesh.addIndex(index + 3);
			this->frame_mesh.addIndex(index + 3); this->frame_mesh.addIndex(index + 0);

			this->frame_mesh.addIndex(index + 4); this->frame_mesh.addIndex(index + 5);
			this->frame_mesh.addIndex(index + 5); this->frame_mesh.addIndex(index + 6);
			this->frame_mesh.addIndex(index + 6); this->frame_mesh.addIndex(index + 7);
			this->frame_mesh.addIndex(index + 7); this->frame_mesh.addIndex(index + 4);

			this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 4);
			this->frame_mesh.addIndex(index + 1); this->frame_mesh.addIndex(index + 5);
			this->frame_mesh.addIndex(index + 2); this->frame_mesh.addIndex(index + 6);
			this->frame_mesh.addIndex(index + 3); this->frame_mesh.addIndex(index + 7);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);
	ofRotateZ(ofGetFrameNum() * 0.36);

	ofSetColor(0);
	this->face_mesh.drawFaces();

	ofSetColor(139);
	this->frame_mesh.drawWireframe();

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