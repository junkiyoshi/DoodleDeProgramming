#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	auto seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

	this->face.clear();
	this->line.clear();

	float threshold_1 = 0.48;
	float threshold_2 = 0.52;
	float deg_span = 0.25;
	float z_span = 1;

	float noise_span = 0.005;
	float noise_radius = 300;

	for(float radius = 280; radius <= 420; radius += 10){

		for (float deg = 0; deg < 360; deg += deg_span) {

			for (float z = -1024; z < 1024; z += z_span) {

				auto noise_value = ofNoise(glm::vec4(radius * 0.003 + ofGetFrameNum() * 0.025, noise_radius * cos(deg * DEG_TO_RAD) * noise_span, noise_radius * sin(deg * DEG_TO_RAD) * noise_span, z * noise_span));
				if (noise_value <= threshold_1 || noise_value >= threshold_2) { continue; }

				auto noise_1 = ofNoise(glm::vec4(radius * 0.003 + ofGetFrameNum() * 0.025, noise_radius * cos((deg - deg_span) * DEG_TO_RAD) * noise_span, noise_radius * sin((deg - deg_span) * DEG_TO_RAD) * noise_span, z * noise_span));
				auto noise_2 = ofNoise(glm::vec4(radius * 0.003 + ofGetFrameNum() * 0.025, noise_radius * cos(deg * DEG_TO_RAD) * noise_span, noise_radius * sin(deg * DEG_TO_RAD) * noise_span, (z + z_span) * noise_span));
				auto noise_3 = ofNoise(glm::vec4(radius * 0.003 + ofGetFrameNum() * 0.025, noise_radius * cos(deg * DEG_TO_RAD) * noise_span, noise_radius * sin(deg * DEG_TO_RAD) * noise_span, (z - z_span) * noise_span));
				auto noise_4 = ofNoise(glm::vec4(radius * 0.003 + ofGetFrameNum() * 0.025, noise_radius * cos((deg + deg_span) * DEG_TO_RAD) * noise_span, noise_radius * sin((deg + deg_span) * DEG_TO_RAD) * noise_span, z * noise_span));

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), z - z_span * 0.5));
				vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), z - z_span * 0.5));
				vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), z + z_span * 0.5));
				vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), z + z_span * 0.5));

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
				this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				if (noise_1 <= threshold_1 || noise_1 >= threshold_2) {

					this->line.addVertex(vertices[0]);
					this->line.addVertex(vertices[2]);

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_2 <= threshold_1 || noise_2 >= threshold_2) {

					this->line.addVertex(vertices[2]);
					this->line.addVertex(vertices[3]);

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_3 <= threshold_1 || noise_3 >= threshold_2) {

					this->line.addVertex(vertices[0]);
					this->line.addVertex(vertices[1]);

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_4 <= threshold_1 || noise_4 >= threshold_2) {

					this->line.addVertex(vertices[1]);
					this->line.addVertex(vertices[3]);

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);

				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	this->cam.setPosition(0, 0, 1000);

	ofSetColor(239);
	this->line.draw();

	ofSetColor(39);
	this->face.draw();

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

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}