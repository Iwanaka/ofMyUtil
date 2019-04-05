#pragma once
#include "ofRectangle.h"
#include "ofCircleInfo.h"
#include "ofVec4f.h"

//--------------------------------------------------------------
// ofxMyUtil String
//--------------------------------------------------------------
namespace ofxMyUtil {
	namespace Event {

		bool rectButtonClickDetect(ofRectangle rect, int mouseX, int mouseY);

		bool rectButtonClickDetect(int rect_x, int rect_y, int rect_w, int rect_h, int mouseX, int mouseY);
		
		bool circleButtonClickDetect(ofCircleInfo circle, int mouseX, int mouseY);
		
		bool circleButtonClickDetect(int circle_x, int circle_y, float radius, int mouseX, int mouseY);

		bool ellipseButtonClickDetect(ofVec4f ellipse, int mouseX, int mouseY);

		bool ellipseButtonClickDetect(int ellipse_x, int ellipse_y, int ellipse_w, int ellipse_h, int mouseX, int mouseY);

	}
}