#include "ofCircleInfo.h"

using namespace ofxMyUtil;

//--------------------------------------------------------------
void ofCircleInfo::Set(float px, float py, float radius) 
{
	
	mPosition = glm::vec2(px, py);
	mRadius = radius;

}