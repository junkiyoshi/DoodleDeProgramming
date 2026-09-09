#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 4);
	this->triangle_list.insert(this->triangle_list.end(), ico_sphere.getMesh().getUniqueFaces().begin(), ico_sphere.getMesh().getUniqueFaces().end());

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();
	this->frame.clear();

	int radius = 300;
	for (int i = 0; i < this->triangle_list.size(); i++) {

		glm::vec3 avg = (this->triangle_list[i].getVertex(0) + this->triangle_list[i].getVertex(1) + this->triangle_list[i].getVertex(2)) / 3;
		auto noise_value = ofNoise(avg.x * 0.01, avg.y * 0.01, avg.z * 0.01 + ofGetFrameNum() * 0.002);
		glm::highp_dmat4 rotation_x, rotation_y, rotation_z;

		if (noise_value < 0.55) {

			auto angle = 0.f;
			if (noise_value < 0.5) {

				angle = ofMap(noise_value, 0, 0.5, PI * 2, PI);
			}
			else {

				angle = ofMap(noise_value, 0.5, 0.55, PI, 0);
			}

			rotation_x = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));
			rotation_y = glm::rotate(glm::mat4(), angle, glm::vec3(0, 1, 0));
			rotation_z = glm::rotate(glm::mat4(), angle, glm::vec3(0, 0, 1));
		}
		else {

			rotation_x = glm::rotate(glm::mat4(), 0.f, glm::vec3(1, 0, 0));
			rotation_y = glm::rotate(glm::mat4(), 0.f, glm::vec3(0, 1, 0));
			rotation_z = glm::rotate(glm::mat4(), 0.f, glm::vec3(0, 0, 1));
		}

		vector<glm::vec3> vertices;

		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(0)) * (radius + 1) - avg);
		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(1)) * (radius + 1) - avg);
		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(2)) * (radius + 1) - avg);

		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(0)) * (radius - 1) - avg);
		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(1)) * (radius - 1) - avg);
		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(2)) * (radius - 1) - avg);

		for (auto& vertex : vertices) {

			vertex = glm::vec4(vertex, 0) * rotation_z * rotation_y * rotation_x;
			if (noise_value < 0.55) {

				vertex *= ofMap(noise_value, 0, 0.55, 0.01, 1);
				vertex += glm::normalize(avg) * ofMap(noise_value, 0, 0.55, radius * 0.15, radius);
			}
			else {

				vertex += avg;
			}
		}

		this->mesh.addVertices(vertices);
		this->frame.addVertices(vertices);

		this->mesh.addColor(ofColor(39));
		this->mesh.addColor(ofColor(39));
		this->mesh.addColor(ofColor(39));

		this->mesh.addColor(ofColor(39));
		this->mesh.addColor(ofColor(39));
		this->mesh.addColor(ofColor(39));

		this->frame.addColor(ofColor(239));
		this->frame.addColor(ofColor(239));
		this->frame.addColor(ofColor(239));

		this->frame.addColor(ofColor(239));
		this->frame.addColor(ofColor(239));
		this->frame.addColor(ofColor(239));

		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3);
		this->mesh.addTriangle(this->mesh.getNumVertices() - 4, this->mesh.getNumVertices() - 5, this->mesh.getNumVertices() - 6);

		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 5);
		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 5, this->mesh.getNumVertices() - 4);

		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 3, this->mesh.getNumVertices() - 6);
		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 6, this->mesh.getNumVertices() - 4);

		this->mesh.addTriangle(this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3, this->mesh.getNumVertices() - 6);
		this->mesh.addTriangle(this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 6, this->mesh.getNumVertices() - 5);

		this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 2);
		this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 3);
		this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 3);

		this->frame.addIndex(this->frame.getNumVertices() - 4); this->frame.addIndex(this->frame.getNumVertices() - 5);
		this->frame.addIndex(this->frame.getNumVertices() - 5); this->frame.addIndex(this->frame.getNumVertices() - 6);
		this->frame.addIndex(this->frame.getNumVertices() - 4); this->frame.addIndex(this->frame.getNumVertices() - 6);

		this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 4);
		this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 5);
		this->frame.addIndex(this->frame.getNumVertices() - 3); this->frame.addIndex(this->frame.getNumVertices() - 6);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.09);

	ofSetColor(239);
	this->mesh.drawFaces();

	ofSetColor(39);
	this->frame.drawWireframe();

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
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}