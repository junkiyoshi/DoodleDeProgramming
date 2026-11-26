#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	auto deg_width = 10;
	auto deg_span = 3;
	auto height_span = 3;
	auto max_height = 1000;

	ofColor face_color(0), line_color(255);

	auto frame_step = 0.03;
	auto threshold = 0.25;
	auto noise_seed = ofRandom(1000);

	for (auto radius = 100; radius <= 250; radius += 50) {
		
		for (auto deg_start = 0; deg_start < 360; deg_start += deg_width + 1) {

			auto deg = deg_start;

			for (auto height = 0; height < max_height; height += height_span) {

				auto prev_noise_value = ofNoise(noise_seed * cos(deg_start * DEG_TO_RAD) * 0.005, noise_seed * sin(deg_start * DEG_TO_RAD) * 0.005, (height - height_span) * 0.002 + ofGetFrameNum() * frame_step);
				auto noise_value = ofNoise(noise_seed * cos(deg_start * DEG_TO_RAD) * 0.005, noise_seed * sin(deg_start * DEG_TO_RAD) * 0.005, height * 0.002 + ofGetFrameNum() * frame_step);
				auto next_noise_value = ofNoise(noise_seed * cos(deg_start * DEG_TO_RAD) * 0.005, noise_seed * sin(deg_start * DEG_TO_RAD) * 0.005, (height + height_span) * 0.002 + ofGetFrameNum() * frame_step);

				if (noise_value < threshold) {

					this->face.addVertex(glm::vec3(radius * cos((deg)*DEG_TO_RAD), height, radius * sin((deg)*DEG_TO_RAD)));
					this->face.addVertex(glm::vec3(radius * cos((deg + deg_width) * DEG_TO_RAD), height, radius * sin((deg + deg_width) * DEG_TO_RAD)));
					this->face.addVertex(glm::vec3(radius * cos((deg + deg_span + deg_width) * DEG_TO_RAD), height + height_span, radius * sin((deg + deg_span + deg_width) * DEG_TO_RAD)));
					this->face.addVertex(glm::vec3(radius * cos((deg + deg_span) * DEG_TO_RAD), height + height_span, radius * sin((deg + deg_span) * DEG_TO_RAD)));

					this->line.addVertex(glm::vec3(radius * cos((deg)*DEG_TO_RAD), height, radius * sin((deg)*DEG_TO_RAD)));
					this->line.addVertex(glm::vec3(radius * cos((deg + deg_width) * DEG_TO_RAD), height, radius * sin((deg + deg_width) * DEG_TO_RAD)));
					this->line.addVertex(glm::vec3(radius * cos((deg + deg_span + deg_width) * DEG_TO_RAD), height + height_span, radius * sin((deg + deg_span + deg_width) * DEG_TO_RAD)));
					this->line.addVertex(glm::vec3(radius * cos((deg + deg_span) * DEG_TO_RAD), height + height_span, radius * sin((deg + deg_span) * DEG_TO_RAD)));

					for (int i = 0; i < 4; i++) {

						this->face.addColor(face_color);
						this->line.addColor(line_color);
					}

					this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 3);
					this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 4);

					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 4);
					this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 3);

					if (height >= max_height - height_span || next_noise_value > threshold) {

						this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					}

					if (height < height_span || prev_noise_value > threshold) {

						this->line.addIndex(this->line.getNumVertices() - 3); this->line.addIndex(this->line.getNumVertices() - 4);
					}
				}

				deg += deg_span;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateX(180);
	ofTranslate(0, -500, 0);

	this->face.drawFaces();
	this->line.drawWireframe();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 600;
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