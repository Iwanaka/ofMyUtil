#include "ofxMyUtilEvent.h"
#include "ofMath.h"
#include <algorithm>

//--------------------------------------------------------------
// Event
//--------------------------------------------------------------
using namespace std;
using namespace ofxMyUtil;

//--------------------------------------------------------------
bool Event::rectButtonClickDetect(ofRectangle rect, int mouseX, int mouseY) {

	if (rect.x <= mouseX &&
		mouseX <= rect.x + rect.width &&
		rect.y <= mouseY &&
		mouseY <= rect.y + rect.height)
	{
		return 1;
	}
	else {
		return 0;
	}

}


//--------------------------------------------------------------
bool Event::rectButtonClickDetect(int rect_x, int rect_y, int rect_w, int rect_h, int mouseX, int mouseY) {

	return rectButtonClickDetect(ofRectangle(rect_x, rect_y, rect_w, rect_h), mouseX, mouseY);

}

//--------------------------------------------------------------
bool Event::circleButtonClickDetect(ofCircleInfo circle, int mouseX, int mouseY) {

	if (ofDist(circle.getX(), circle.getY(), mouseX, mouseY) < circle.getRadius()) return 1;
	else return 0;

}

//--------------------------------------------------------------
bool Event::circleButtonClickDetect(int circle_x, int circle_y, float radius, int mouseX, int mouseY) {

	return circleButtonClickDetect(ofCircleInfo(circle_x, circle_y, radius), mouseX, mouseY);

}

//--------------------------------------------------------------
bool Event::ellipseButtonClickDetect(ofVec4f ellipse, int mouseX, int mouseY) {

	return rectButtonClickDetect(ofRectangle(glm::vec2(ellipse.x - ellipse.z / 2, ellipse.y - ellipse.w / 2), ellipse.z, ellipse.w), mouseX, mouseY);

}

//--------------------------------------------------------------
bool Event::ellipseButtonClickDetect(
	int ellipse_x,
	int ellipse_y,
	int ellipse_w,
	int ellipse_h,
	int mouseX,
	int mouseY) {

	return ellipseButtonClickDetect(ofVec4f(ellipse_x, ellipse_y, ellipse_w, ellipse_h), mouseX, mouseY);

}

