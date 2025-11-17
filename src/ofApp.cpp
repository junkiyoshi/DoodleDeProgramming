#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(0.5);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 3);
	this->triangle_list.insert(this->triangle_list.end(), ico_sphere.getMesh().getUniqueFaces().begin(), ico_sphere.getMesh().getUniqueFaces().end());

	//this->frame.setMode(OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();
	this->frame.clear();

	auto radius = 250;

	for (int i = 0; i < this->triangle_list.size(); i++) {

		glm::vec3 avg = (this->triangle_list[i].getVertex(0) + this->triangle_list[i].getVertex(1) + this->triangle_list[i].getVertex(2)) / 3;
		avg = glm::normalize(avg) * radius;
		auto noise_value = ofNoise(avg.x * 0.006, avg.y * 0.006, avg.z * 0.006, ofGetFrameNum() * 0.005);
		auto height = 0;

		if (noise_value > 0.48 && noise_value < 0.52) {

			height = 400;
		}
		else  if (noise_value > 0.45 && noise_value < 0.48) {

			height = ofMap(noise_value, 0.45, 0.48, 0, 400);
		}
		else if (noise_value > 0.52 && noise_value < 0.55) {

			height = ofMap(noise_value, 0.52, 0.55, 400, 0);
		}

		vector<glm::vec3> vertices;

		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(0)) * radius - avg);
		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(1)) * radius - avg);
		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(2)) * radius - avg);

		vertices.push_back(glm::normalize(avg) * (radius + height) - avg);

		for (auto& vertex : vertices) {

			vertex *= 0.9;
			vertex += avg;
		}

		this->mesh.addVertices(vertices);
		this->frame.addVertices(vertices);

		ofColor mesh_color = ofColor(0);
		ofColor frame_color = ofColor(255);

		for (int k = 0; k < vertices.size(); k++) {

			this->mesh.addColor(mesh_color);
			this->frame.addColor(frame_color);
		}

		this->mesh.addTriangle(this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3, this->mesh.getNumVertices() - 4);
		this->frame.addTriangle(this->frame.getNumVertices() - 2, this->frame.getNumVertices() - 3, this->frame.getNumVertices() - 4);

		if (height > 250) {

			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3);
			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 3, this->mesh.getNumVertices() - 4);
			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 4);

			this->frame.addTriangle(this->frame.getNumVertices() - 1, this->frame.getNumVertices() - 2, this->frame.getNumVertices() - 3);
			this->frame.addTriangle(this->frame.getNumVertices() - 1, this->frame.getNumVertices() - 3, this->frame.getNumVertices() - 4);
			this->frame.addTriangle(this->frame.getNumVertices() - 1, this->frame.getNumVertices() - 2, this->frame.getNumVertices() - 4);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.72);
	ofRotateX(ofGetFrameNum() * 1.44);

	this->mesh.drawFaces();
	this->frame.drawWireframe();

	this->cam.end(); 

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 150;
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