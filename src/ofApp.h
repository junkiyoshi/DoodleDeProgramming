#pragma once
#include "ofMain.h"

class Particle {
public:
	Particle();
	~Particle();

	void update(vector<std::unique_ptr<Particle>>& particles);
	void draw();
	glm::vec2 separate(vector<std::unique_ptr<Particle>>& particles);
	glm::vec2 align(vector<std::unique_ptr<Particle>>& particles);
	glm::vec2 cohesion(vector<std::unique_ptr<Particle>>& particles);
	glm::vec2 seek(glm::vec2 target);
	void applyForce(glm::vec2 force);

private:
	glm::vec2 location;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	vector<glm::vec2> log;

	float range;
	float max_force;
	float max_speed;
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

	vector<std::unique_ptr<Particle>> particles;
};