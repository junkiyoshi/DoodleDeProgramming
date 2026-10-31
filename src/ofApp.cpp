#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int R = 235;
	int v_span = 6;
	int u_span = 20;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	ofColor face_color = ofColor(0);
	ofColor line_color = ofColor(39, 39, 239);

	for (int v = 0; v < 360; v += v_span) {

		for (int u = 0; u < 360; u += u_span) {

			for (int r = 30; r <= 60; r += 5) {

				auto noise_value = ofNoise(glm::vec4(this->make_point(R, 5, u, v) * 0.02, r * 0.05 - ofGetFrameNum() * 0.025));
				auto param = noise_value > 0.5 ? noise_value < 0.6 ? ofMap(noise_value, 0.5, 0.6, 1, 0) : 0 : 1;
				auto v_size = v_span * param;
				auto u_size = u_span * param;

				face.addVertex(this->make_point(R, r, u - u_size * 0.5, v - v_size * 0.5));
				face.addVertex(this->make_point(R, r, u + u_size * 0.5, v - v_size * 0.5));
				face.addVertex(this->make_point(R, r, u + u_size * 0.5, v + v_size * 0.5));
				face.addVertex(this->make_point(R, r, u - u_size * 0.5, v + v_size * 0.5));

				line.addVertex(this->make_point(R, r, u - u_size * 0.5, v - v_size * 0.5));
				line.addVertex(this->make_point(R, r, u + u_size * 0.5, v - v_size * 0.5));
				line.addVertex(this->make_point(R, r, u + u_size * 0.5, v + v_size * 0.5));
				line.addVertex(this->make_point(R, r, u - u_size * 0.5, v + v_size * 0.5));

				face.addColor(face_color);
				face.addColor(face_color);
				face.addColor(face_color);
				face.addColor(face_color);

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				line.addColor(line_color);
				line.addColor(line_color);
				line.addColor(line_color);
				line.addColor(line_color);

				auto noise_value_1 = ofNoise(glm::vec4(this->make_point(R, 5, u - u_span, v) * 0.02, r * 0.05 - ofGetFrameNum() * 0.025));
				auto noise_value_2 = ofNoise(glm::vec4(this->make_point(R, 5, u, v + v_span) * 0.02, r * 0.05 - ofGetFrameNum() * 0.025));
				auto noise_value_3 = ofNoise(glm::vec4(this->make_point(R, 5, u, v - v_span) * 0.02, r * 0.05 - ofGetFrameNum() * 0.025));
				auto noise_value_4 = ofNoise(glm::vec4(this->make_point(R, 5, u + u_span, v) * 0.02, r * 0.05 - ofGetFrameNum() * 0.025));

				auto param_1 = noise_value_1 > 0.5 ? noise_value_1 < 0.6 ? ofMap(noise_value_1, 0.5, 0.6, 1, 0) : 0 : 1;
				auto param_2 = noise_value_2 > 0.5 ? noise_value_2 < 0.6 ? ofMap(noise_value_2, 0.5, 0.6, 1, 0) : 0 : 1;
				auto param_3 = noise_value_3 > 0.5 ? noise_value_3 < 0.6 ? ofMap(noise_value_3, 0.5, 0.6, 1, 0) : 0 : 1;
				auto param_4 = noise_value_4 > 0.5 ? noise_value_4 < 0.6 ? ofMap(noise_value_3, 0.5, 0.6, 1, 0) : 0 : 1;

				if (param_1 < 1 || param < 1) {

					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
				}

				if (param_2 < 1 || param < 1) {


					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
				}

				if (param_3 < 1 || param < 1) {


					line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);
				}

				if (param_4 < 1 || param < 1) {

					line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);
				}
			}
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