#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(0.5);
	ofEnableDepthTest();

	this->base_radius = 65;
	this->ico_sphere = ofIcoSpherePrimitive(this->base_radius, 2);
	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int radius_start = this->base_radius;
	int radius_max = this->base_radius * 12;
	for (auto& triangle : this->ico_sphere.getMesh().getUniqueFaces()) {

		auto noise_seed_x = ofRandom(1000);
		auto noise_seed_y = ofRandom(1000);
		auto noise_seed_z = ofRandom(1000);

		auto noise_value = ofNoise(ofRandom(1000), this->noise_param);
		int radius_end = radius_max;
		this->frame.addVertex(glm::vec3());

		for (int radius = radius_start; radius <= radius_end; radius += 1) {

			auto mesh_index = this->face.getNumVertices();
			auto frame_index = this->frame.getNumVertices();

			auto param = ofMap(radius, radius_start, radius_max, 0, PI * 0.15);

			auto angle_x = ofMap(ofNoise(noise_seed_x, radius * 0.02 + this->noise_param), 0, 1, -param, param);
			auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
			auto angle_y = ofMap(ofNoise(noise_seed_y, radius * 0.02 + this->noise_param), 0, 1, -param, param);
			auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
			auto angle_z = ofMap(ofNoise(noise_seed_z, radius * 0.02 + this->noise_param), 0, 1, -param, param);
			auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

			glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
			glm::vec3 location = glm::normalize(avg) * radius;

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec4(location + glm::normalize(triangle.getVertex(0) - avg) * ofMap(radius, radius_start, radius_end, glm::length(triangle.getVertex(0) - avg), 0), 0) * rotation_z * rotation_y * rotation_x);
			vertices.push_back(glm::vec4(location + glm::normalize(triangle.getVertex(1) - avg) * ofMap(radius, radius_start, radius_end, glm::length(triangle.getVertex(1) - avg), 0), 0) * rotation_z * rotation_y * rotation_x);
			vertices.push_back(glm::vec4(location + glm::normalize(triangle.getVertex(2) - avg) * ofMap(radius, radius_start, radius_end, glm::length(triangle.getVertex(2) - avg), 0), 0) * rotation_z * rotation_y * rotation_x);

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			for (int i = 0; i < vertices.size(); i++) {

				this->face.addColor(ofColor(39, 200, 39));
				this->frame.addColor(ofColor(239));
			}

			if (radius == radius_start || radius == radius_end) {

				this->face.addIndex(mesh_index + 0); this->face.addIndex(mesh_index + 1); this->face.addIndex(mesh_index + 2);

				this->frame.addIndex(frame_index + 0); this->frame.addIndex(frame_index + 1);
				this->frame.addIndex(frame_index + 1); this->frame.addIndex(frame_index + 2);
				this->frame.addIndex(frame_index + 2); this->frame.addIndex(frame_index + 0);
			}

			if (radius > radius_start) {

				this->face.addIndex(mesh_index + 0); this->face.addIndex(mesh_index + 1); this->face.addIndex(mesh_index - 2);
				this->face.addIndex(mesh_index + 0); this->face.addIndex(mesh_index - 2); this->face.addIndex(mesh_index - 3);

				this->face.addIndex(mesh_index + 1); this->face.addIndex(mesh_index + 2); this->face.addIndex(mesh_index - 1);
				this->face.addIndex(mesh_index + 1); this->face.addIndex(mesh_index - 1); this->face.addIndex(mesh_index - 2);

				this->face.addIndex(mesh_index + 2); this->face.addIndex(mesh_index + 0); this->face.addIndex(mesh_index - 3);
				this->face.addIndex(mesh_index + 2); this->face.addIndex(mesh_index - 3); this->face.addIndex(mesh_index - 1);

				this->frame.addIndex(frame_index + 0); this->frame.addIndex(frame_index - 3);
				this->frame.addIndex(frame_index + 1); this->frame.addIndex(frame_index - 2);
				this->frame.addIndex(frame_index + 2); this->frame.addIndex(frame_index - 1);
			}
		}
	}

	this->noise_param -= 0.03;
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->frame.drawWireframe();
	this->face.draw();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 50;
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