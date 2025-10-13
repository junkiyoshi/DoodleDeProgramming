#pragma once
#include "ofMain.h"

class Actor {
public:
	Actor(vector<glm::vec3>& location_list, vector<vector<int>>& next_index_list, vector<int>& destination_list);
	void update(const int& frame_span, vector<glm::vec3>& location_list, vector<vector<int>>& next_index_list, vector<int>& destination_list);
	glm::vec3 getLocation();
	glm::vec3 getLocation(int i);
	vector<glm::vec3> getLog();
	void setColor(ofColor color);
	ofColor getColor();

private:

	int select_index;
	int next_index;

	glm::vec3 location;
	vector<glm::vec3> log;
	ofColor color;
};

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

	vector<glm::vec3> parent_location_group;
	vector<vector<int>> parent_next_index_group;
	vector<int> parent_destination_group;
	vector<std::unique_ptr<Actor>> parent_actor_group;

	vector<vector<glm::vec3>> location_group_list;
	vector<vector<vector<int>>> next_index_group_list;
	vector<vector<int>> destination_group_list;
	vector<vector<std::unique_ptr<Actor>>> actor_group_list;

	ofEasyCam cam;
};