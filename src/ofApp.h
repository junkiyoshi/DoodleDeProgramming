#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	glm::vec3 make_point(float R, float r, float u, float v);

	ofEasyCam cam;
	ofMesh face, line;

	vector<glm::vec3> base_location_list;

	vector<std::tuple<ofColor, glm::vec3, float>> box_list; // BodyColor, Location, size
	int number_of_sphere;
};