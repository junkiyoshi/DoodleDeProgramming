#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 1.5;
	float theta_deg_step = 6;

	float R = 250;
	float r = R * 0.25;

	for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

		for (float theta_deg = 0; theta_deg < 360; theta_deg += theta_deg_step) {

			auto noise_value = ofNoise(glm::vec4(this->make_point(R, r, theta_deg, phi_deg) * 0.01, ofGetFrameNum() * 0.001));
			if (noise_value < 0.45 || noise_value > 0.55) { continue; }

			auto noise_1 = ofNoise(glm::vec4(this->make_point(R, r, theta_deg - theta_deg_step, phi_deg) * 0.01, ofGetFrameNum() * 0.001));
			auto noise_2 = ofNoise(glm::vec4(this->make_point(R, r, theta_deg, phi_deg + phi_deg_step) * 0.01, ofGetFrameNum() * 0.001));
			auto noise_3 = ofNoise(glm::vec4(this->make_point(R, r, theta_deg, phi_deg - phi_deg_step) * 0.01, ofGetFrameNum() * 0.001));
			auto noise_4 = ofNoise(glm::vec4(this->make_point(R, r, theta_deg + theta_deg_step, phi_deg) * 0.01, ofGetFrameNum() * 0.001));

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));

			this->face.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
			this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

			if (noise_1 < 0.45 || noise_1 > 0.55) {

				this->line.addVertex(vertices[0]);
				this->line.addVertex(vertices[2]);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_2 < 0.45 || noise_2 > 0.55) {

				this->line.addVertex(vertices[2]);
				this->line.addVertex(vertices[3]);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_3 < 0.45 || noise_3 > 0.55) {

				this->line.addVertex(vertices[0]);
				this->line.addVertex(vertices[1]);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

			if (noise_4 < 0.45 || noise_4 > 0.55) {

				this->line.addVertex(vertices[1]);
				this->line.addVertex(vertices[3]);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);

			}
		}
	}

	ofSeedRandom(39);

	this->walker_log_list.clear();
	this->walker_color_list.clear();
	ofColor color;
	for (int i = 0; i < 150; i++) {

		vector<glm::vec3> walker_location_list;
		auto noise_param = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		auto step_u = ofRandom(1, 1.5);
		auto step_v = ofRandom(1, 1.5);
		auto tmp_r = ofRandom(r * 0.3, r * 0.7);
		for (int k = 0; k < 60; k++) {

			auto tmp_u = noise_param.y + (ofGetFrameNum() * 3 + k) * step_u;
			auto tmp_v = noise_param.z + (ofGetFrameNum() * 3 + k) * step_v;

			walker_location_list.push_back(this->make_point(R, tmp_r, tmp_u, tmp_v));
		}

		color.setHsb((int)ofMap(i, 0, 150, 180, 280) % 255, 255, 255);

		this->walker_log_list.push_back(walker_location_list);
		this->walker_color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetLineWidth(1);

	ofSetColor(255);
	this->line.draw();

	ofSetColor(0);
	this->face.draw();

	ofSetLineWidth(2);

	for (int i = 0; i < this->walker_log_list.size(); i++) {

		auto walker_log = this->walker_log_list[i];
		ofSetColor(this->walker_color_list[i]);

		ofNoFill();
		ofBeginShape();
		for (auto& walker_location : walker_log) {

			ofVertex(walker_location);
		}
		ofEndShape();
	}

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