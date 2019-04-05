#include "ofCircleInfo.h"

using namespace ofxMyUtil;

//--------------------------------------------------------------
ofCircleInfo::ofCircleInfo() {}

//--------------------------------------------------------------
ofCircleInfo::ofCircleInfo(float px, float py, float radius) { set(px, py, radius); }

//--------------------------------------------------------------
ofCircleInfo::ofCircleInfo(const glm::vec2& pos, float radius) { set(pos, radius); }

//--------------------------------------------------------------
ofCircleInfo::ofCircleInfo(const ofCircleInfo& circle) { set(circle); }

//--------------------------------------------------------------
ofCircleInfo::~ofCircleInfo() {}

//--------------------------------------------------------------
void ofCircleInfo::set(float px, float py, float radius) {
	
	position = glm::vec2(px, py);
	this->radius = radius;

}

//--------------------------------------------------------------
void ofCircleInfo::set(const glm::vec2 &p, float radius) { set(p.x, p.y, radius); }

//--------------------------------------------------------------
void ofCircleInfo::set(const ofCircleInfo &circle) { set(circle.position, circle.radius); }

//--------------------------------------------------------------
void ofCircleInfo::setX(float px) { position.x = px; }

//--------------------------------------------------------------
void ofCircleInfo::setY(float py) { position.y = py; }

//--------------------------------------------------------------
void ofCircleInfo::setRadius(float radius) { this->radius = radius; }

//--------------------------------------------------------------
void ofCircleInfo::setPosition(float px, float py) { position = glm::vec2(px, py); }

//--------------------------------------------------------------
void ofCircleInfo::setPosition(const glm::vec2 &p) { this->position = p; }

//--------------------------------------------------------------
float ofCircleInfo::getX() { return position.x; }

//--------------------------------------------------------------
float ofCircleInfo::getY() { return position.y; }

//--------------------------------------------------------------
glm::vec2 ofCircleInfo::getPos() { return position; }

//--------------------------------------------------------------
float ofCircleInfo::getRadius() { return radius; }