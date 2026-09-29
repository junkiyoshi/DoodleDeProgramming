#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	ofColor color;
	this->number_of_sphere = 250;
	while (this->box_list.size() < this->number_of_sphere) {

		auto tmp_location = this->make_point(250, ofRandom(0, 30), ofRandom(360), ofRandom(360));
		auto radius = this->box_list.size() < 60 ? ofRandom(10, 30) : ofRandom(5, 20);

		bool flag = true;
		for (int i = 0; i < this->box_list.size(); i++) {

			if (glm::distance(tmp_location, get<1>(this->box_list[i])) < get<2>(this->box_list[i]) + radius) {

				flag = false;
				break;
			}
		}

		if (flag) {

			color.setHsb(ofRandom(255), 180, 255);
			auto size = (radius * 2) / sqrt(3);
			this->box_list.push_back(std::make_tuple(color, tmp_location, size));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 1.5;
	float theta_deg_step = 6;

	float R = 250;
	float r = R * 0.25;

	for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

		for (float theta_deg = 0; theta_deg < 360; theta_deg += theta_deg_step) {

			auto noise_value = ofNoise(glm::vec4(this->make_point(R, r, theta_deg, phi_deg) * 0.01, ofGetFrameNum() * 0.01));
			if (noise_value < 0.43 || noise_value > 0.57) { continue; }

			auto noise_1 = ofNoise(glm::vec4(this->make_point(R, r, theta_deg - theta_deg_step, phi_deg) * 0.01, ofGetFrameNum() * 0.01));
			auto noise_2 = ofNoise(glm::vec4(this->make_point(R, r, theta_deg, phi_deg + phi_deg_step) * 0.01, ofGetFrameNum() * 0.01));
			auto noise_3 = ofNoise(glm::vec4(this->make_point(R, r, theta_deg, phi_deg - phi_deg_step) * 0.01, ofGetFrameNum() * 0.01));
			auto noise_4 = ofNoise(glm::vec4(this->make_point(R, r, theta_deg + theta_deg_step, phi_deg) * 0.01, ofGetFrameNum() * 0.01));

			auto index = this->face.getNumVertices();
			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg - phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg - theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));
			vertices.push_back(glm::vec3(this->make_point(R, r, theta_deg + theta_deg_step * 0.5, phi_deg + phi_deg_step * 0.5)));

			this->face.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
			this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

			if (noise_1 < 0.43 || noise_1 > 0.57) {

				this->line.addVertex(vertices[0]);
				this->line.addVertex(vertices[2]);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);

				this->line.addColor(ofColor(255));
				this->line.addColor(ofColor(255));
			}

			if (noise_2 < 0.43 || noise_2 > 0.57) {

				this->line.addVertex(vertices[2]);
				this->line.addVertex(vertices[3]);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);

				this->line.addColor(ofColor(255));
				this->line.addColor(ofColor(255));
			}

			if (noise_3 < 0.43 || noise_3 > 0.57) {

				this->line.addVertex(vertices[0]);
				this->line.addVertex(vertices[1]);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);

				this->line.addColor(ofColor(255));
				this->line.addColor(ofColor(255));
			}

			if (noise_4 < 0.43 || noise_4 > 0.57) {

				this->line.addVertex(vertices[1]);
				this->line.addVertex(vertices[3]);

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);

				this->line.addColor(ofColor(255));
				this->line.addColor(ofColor(255));
			}
		}
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

	ofRotateZ(ofGetFrameNum() * 0.72);

	for (int i = 0; i < this->box_list.size(); i++) {

		auto color = get<0>(this->box_list[i]);
		auto location = get<1>(this->box_list[i]);
		auto size = get<2>(this->box_list[i]);

		ofPushMatrix();
		ofTranslate(location);

		ofRotateZ(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 5));
		ofRotateY(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 5));
		ofRotateX(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 5));

		ofFill();
		ofSetColor(color);
		ofDrawBox(size);

		ofNoFill();
		ofSetColor(255);
		ofDrawBox(size);

		ofPopMatrix();
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