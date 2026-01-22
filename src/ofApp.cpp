#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	auto seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 0.25;
	float theta_deg_step = 0.25;
	float threshold = 0.5;
	float noise_span = 0.005;

	float R = 200;
	float base_r = R * 0.25;

	float r = ofGetFrameNum() % 50 < 25 ? ofMap(ofGetFrameNum() % 50, 0, 25, R * 0.2, R * 0.4) : ofMap(ofGetFrameNum() % 50, 25, 50, R * 0.4, R * 0.2);

	ofColor face_color = ofColor(239);
	ofColor line_color = ofColor(239, 139, 139);

	for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

		for (float theta_deg = 0; theta_deg < 360; theta_deg += theta_deg_step) {

			auto noise_value = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg, phi_deg) * noise_span, ofGetFrameNum() * 0.025));
			if (noise_value <= threshold) { continue; }

			auto noise_1 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg - theta_deg_step, phi_deg) * noise_span, ofGetFrameNum() * 0.025));
			auto noise_2 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg, phi_deg + phi_deg_step) * noise_span, ofGetFrameNum() * 0.025));
			auto noise_3 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg, phi_deg - phi_deg_step) * noise_span, ofGetFrameNum() * 0.025));
			auto noise_4 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg + theta_deg_step, phi_deg) * noise_span, ofGetFrameNum() * 0.025));

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));

			this->face.addVertices(vertices);

			this->face.addColor(face_color);
			this->face.addColor(face_color);
			this->face.addColor(face_color);
			this->face.addColor(face_color);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
			this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

			if (noise_1 <= threshold) {

				this->line.addVertex(vertices[0]);
				this->line.addVertex(vertices[2]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_2 <= threshold) {

				this->line.addVertex(vertices[2]);
				this->line.addVertex(vertices[3]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_3 <= threshold) {

				this->line.addVertex(vertices[0]);
				this->line.addVertex(vertices[1]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_4 <= threshold) {

				this->line.addVertex(vertices[1]);
				this->line.addVertex(vertices[3]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);


			}
		}
	}

	r = ofGetFrameNum() % 50 < 25 ? ofMap(ofGetFrameNum() % 50, 0, 25, R * 0.4, R * 0.2) : ofMap(ofGetFrameNum() % 50, 25, 50, R * 0.2, R * 0.4);

	face_color = ofColor(239, 139, 139);
	line_color = ofColor(239);

	for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

		for (float theta_deg = 0; theta_deg < 360; theta_deg += theta_deg_step) {

			auto noise_value = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg, phi_deg) * noise_span, ofGetFrameNum() * 0.025));
			if (noise_value >= threshold) { continue; }

			auto noise_1 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg - theta_deg_step, phi_deg) * noise_span, ofGetFrameNum() * 0.025));
			auto noise_2 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg, phi_deg + phi_deg_step) * noise_span, ofGetFrameNum() * 0.025));
			auto noise_3 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg, phi_deg - phi_deg_step) * noise_span, ofGetFrameNum() * 0.025));
			auto noise_4 = ofNoise(glm::vec4(this->make_point(R, base_r, theta_deg + theta_deg_step, phi_deg) * noise_span, ofGetFrameNum() * 0.025));

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));

			this->face.addVertices(vertices);

			this->face.addColor(face_color);
			this->face.addColor(face_color);
			this->face.addColor(face_color);
			this->face.addColor(face_color);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
			this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

			if (noise_1 >= threshold) {

				this->line.addVertex(vertices[0]);
				this->line.addVertex(vertices[2]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_2 >= threshold) {

				this->line.addVertex(vertices[2]);
				this->line.addVertex(vertices[3]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_3 >= threshold) {

				this->line.addVertex(vertices[0]);
				this->line.addVertex(vertices[1]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_4 >= threshold) {

				this->line.addVertex(vertices[1]);
				this->line.addVertex(vertices[3]);

				this->line.addColor(line_color);
				this->line.addColor(line_color);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);


			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270 + 45);

	this->line.draw();
	this->face.draw();

	this->cam.end();

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