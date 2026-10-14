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
	void mouseEntered(int x, int y) {};
	void mouseExited(int x, int y) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	void draw_digital(glm::vec2 location, int number_index, ofColor fill_color, ofColor no_fill_color);
	void draw_hexagon(glm::vec2 location, float deg, ofColor fill_color, ofColor no_fill_color);

	vector<pair<glm::vec2, int>> number_list;

	float hexagon_height;
	float hexagon_width;
};