#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->noise_param += 0.01;

	this->face.clear();
	this->line.clear();

	float threshold_1 = 0.47;
	float threshold_2 = 0.53;
	float deg_span = 0.2;
	float z_span = 1;
	float noise_span = 0.0015;
	float noise_span_z_scale = 0.5;

	for (float radius = 160; radius <= 320; radius += 160) {

		for (float deg = 0; deg < 360; deg += deg_span) {

			for (float z = -500; z <= 500; z += z_span) {

				auto noise_value = ofNoise(glm::vec4(radius * 100, radius * cos(deg * DEG_TO_RAD) * noise_span, radius * sin(deg * DEG_TO_RAD) * noise_span, z * noise_span * noise_span_z_scale + noise_param));
				noise_value = abs(z) > 470 ? 0.5 : noise_value;
				if (noise_value <= threshold_1 || noise_value >= threshold_2) { continue; }

				auto noise_1 = ofNoise(glm::vec4(radius * 100, radius * cos((deg - deg_span) * DEG_TO_RAD) * noise_span, radius * sin((deg - deg_span) * DEG_TO_RAD) * noise_span, z * noise_span * noise_span_z_scale + noise_param));
				auto noise_2 = ofNoise(glm::vec4(radius * 100, radius * cos(deg * DEG_TO_RAD) * noise_span, radius * sin(deg * DEG_TO_RAD) * noise_span, (z + z_span) * noise_span * noise_span_z_scale + noise_param));
				auto noise_3 = ofNoise(glm::vec4(radius * 100, radius * cos(deg * DEG_TO_RAD) * noise_span, radius * sin(deg * DEG_TO_RAD) * noise_span, (z - z_span) * noise_span * noise_span_z_scale + noise_param));
				auto noise_4 = ofNoise(glm::vec4(radius * 100, radius * cos((deg + deg_span) * DEG_TO_RAD) * noise_span, radius * sin((deg + deg_span) * DEG_TO_RAD) * noise_span, z * noise_span * noise_span_z_scale + noise_param));

				noise_1 = abs(z) > 470 ? 0.5 : noise_1;
				noise_2 = abs(z + z_span) > 470 ? 0.5 : noise_2;
				noise_3 = abs(z - z_span) > 470 ? 0.5 : noise_3;
				noise_4 = abs(z) > 470 ? 0.5 : noise_4;

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), z - z_span * 0.5));
				vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), z - z_span * 0.5));
				vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), z + z_span * 0.5));
				vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), z + z_span * 0.5));

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
				this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				ofColor face_color(255);
				for (int i = 0; i < 4; i++) {

					this->face.addColor(face_color);
				}

				ofColor line_color(0);
				if (noise_1 <= threshold_1 || noise_1 >= threshold_2 || abs(z) == 500) {

					this->line.addVertex(vertices[0]);
					this->line.addVertex(vertices[2]);

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);

					this->line.addColor(line_color);
					this->line.addColor(line_color);
				}

				if (noise_2 <= threshold_1 || noise_2 >= threshold_2 || abs(z) == 500) {

					this->line.addVertex(vertices[2]);
					this->line.addVertex(vertices[3]);

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);

					this->line.addColor(line_color);
					this->line.addColor(line_color);
				}

				if (noise_3 <= threshold_1 || noise_3 >= threshold_2 || abs(z) == 500) {

					this->line.addVertex(vertices[0]);
					this->line.addVertex(vertices[1]);

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);

					this->line.addColor(line_color);
					this->line.addColor(line_color);
				}

				if (noise_4 <= threshold_1 || noise_4 >= threshold_2 || abs(z) == 500) {

					this->line.addVertex(vertices[1]);
					this->line.addVertex(vertices[3]);

					this->line.addIndex(this->line.getNumVertices() - 1);
					this->line.addIndex(this->line.getNumVertices() - 2);

					this->line.addColor(line_color);
					this->line.addColor(line_color);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	this->cam.setPosition(0, 0, 1200);
	ofRotateX(90);
	ofRotateZ(ofGetFrameNum() * 1.44);

	this->line.draw();
	this->face.draw();

	this->cam.end();

	/*
	int start = 25;
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
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}