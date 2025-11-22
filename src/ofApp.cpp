#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	for (float scale = 3; scale < 20; scale += 1) {

		auto start_index = this->face.getNumVertices();
		for (int deg = 0; deg < 360; deg += 1) {

			vector<glm::vec3> vertices;

			if (scale == 3) {

				vertices.push_back(glm::vec3(this->make_point(deg * DEG_TO_RAD) * 0, -2.5));
				vertices.push_back(glm::vec3(this->make_point(deg * DEG_TO_RAD) * (scale + 0.25), -2.5));
				vertices.push_back(glm::vec3(this->make_point((deg + 1) * DEG_TO_RAD) * (scale + 0.25), -2.5));
				vertices.push_back(glm::vec3(this->make_point((deg + 1) * DEG_TO_RAD) * 0, -2.5));

				vertices.push_back(glm::vec3(this->make_point(deg * DEG_TO_RAD) * 0, 2.5));
				vertices.push_back(glm::vec3(this->make_point(deg * DEG_TO_RAD) * (scale + 0.25), 2.5));
				vertices.push_back(glm::vec3(this->make_point((deg + 1) * DEG_TO_RAD) * (scale + 0.25), 2.5));
				vertices.push_back(glm::vec3(this->make_point((deg + 1) * DEG_TO_RAD) * 0, 2.5));
			}
			else {
			
				vertices.push_back(glm::vec3(this->make_point(deg * DEG_TO_RAD) * scale, -2.5));
				vertices.push_back(glm::vec3(this->make_point(deg * DEG_TO_RAD) * (scale + 0.25), -2.5));
				vertices.push_back(glm::vec3(this->make_point((deg + 1) * DEG_TO_RAD) * (scale + 0.25), -2.5));
				vertices.push_back(glm::vec3(this->make_point((deg + 1) * DEG_TO_RAD) * scale, -2.5));

				vertices.push_back(glm::vec3(this->make_point(deg * DEG_TO_RAD) * scale, 2.5));
				vertices.push_back(glm::vec3(this->make_point(deg * DEG_TO_RAD) * (scale + 0.25), 2.5));
				vertices.push_back(glm::vec3(this->make_point((deg + 1) * DEG_TO_RAD) * (scale + 0.25), 2.5));
				vertices.push_back(glm::vec3(this->make_point((deg + 1) * DEG_TO_RAD) * scale, 2.5));
			}

			for (auto& vertex : vertices) {

				auto angle = scale == 3 ? 0 : ofMap(ofNoise(scale * 0.025, vertex.y * 0.0003 + ofGetFrameNum() * 0.01), 0, 1, -PI * 2, PI * 2);
				auto rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 1, 0));
				vertex = glm::vec4(vertex, 0) * rotation;
			}

			auto index = this->face.getNumVertices();
			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
			this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);
			this->face.addIndex(index + 4); this->face.addIndex(index + 5); this->face.addIndex(index + 6);
			this->face.addIndex(index + 4); this->face.addIndex(index + 6); this->face.addIndex(index + 7);
			this->face.addIndex(index + 0); this->face.addIndex(index + 4); this->face.addIndex(index + 1);
			this->face.addIndex(index + 4); this->face.addIndex(index + 5); this->face.addIndex(index + 1);
			this->face.addIndex(index + 1); this->face.addIndex(index + 5); this->face.addIndex(index + 6);
			this->face.addIndex(index + 6); this->face.addIndex(index + 2); this->face.addIndex(index + 1);
			this->face.addIndex(index + 2); this->face.addIndex(index + 6); this->face.addIndex(index + 7);
			this->face.addIndex(index + 7); this->face.addIndex(index + 3); this->face.addIndex(index + 2);
			this->face.addIndex(index + 3); this->face.addIndex(index + 7); this->face.addIndex(index + 4);
			this->face.addIndex(index + 4); this->face.addIndex(index + 0); this->face.addIndex(index + 3);

			this->frame.addIndex(index + 0); this->frame.addIndex(index + 3);
			this->frame.addIndex(index + 1); this->frame.addIndex(index + 2);
			this->frame.addIndex(index + 4); this->frame.addIndex(index + 7);
			this->frame.addIndex(index + 5); this->frame.addIndex(index + 6);
		}

		if (this->face.getNumVertices() != start_index) {

			this->frame.addIndex(start_index + 0); this->frame.addIndex(start_index + 4);
			this->frame.addIndex(start_index + 0); this->frame.addIndex(start_index + 1);
			this->frame.addIndex(start_index + 5); this->frame.addIndex(start_index + 1);
			this->frame.addIndex(start_index + 5); this->frame.addIndex(start_index + 4);

			this->frame.addIndex(this->face.getNumVertices() - 1); this->frame.addIndex(this->face.getNumVertices() - 2);
			this->frame.addIndex(this->face.getNumVertices() - 1); this->frame.addIndex(this->face.getNumVertices() - 5);
			this->frame.addIndex(this->face.getNumVertices() - 6); this->frame.addIndex(this->face.getNumVertices() - 2);
			this->frame.addIndex(this->face.getNumVertices() - 6); this->frame.addIndex(this->face.getNumVertices() - 5);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	
	ofSetColor(0);
	this->face.draw();

	ofSetColor(239, 39, 239);
	this->frame.drawWireframe();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 400;
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
glm::vec2 ofApp::make_point(float theta) {

	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec2(x, -y);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}