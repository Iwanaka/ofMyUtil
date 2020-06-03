#pragma once
#include "ofGraphics.h"
#include "ofAppRunner.h"
#include "ofMath.h"
#include "ofCircleInfo.h"

namespace ofxMyUtil {
	class ofScaleable
	{

	private:

		int w, h;

	public:

		ofScaleable() :
			w(ofGetWidth()),
			h(ofGetHeight()) {}
		~ofScaleable() {}

		void setDefalut(int w, int h) {
			this->w = w;
			this->h = h;
		}

		void begin() {

			ofPushStyle();
			ofPushMatrix();
			float _w = (float)ofGetWidth() / (float)w;
			float _h = (float)ofGetHeight() / (float)h;
			ofScale(_w, _h);
		}

		void end() {
			ofPopMatrix();
			ofPopStyle();
		}

		ofVec2f scaleMouse(ofVec2f mousePosition) {
			
			float _w = ofMap(mousePosition.x, 0.0, w, 0.0, ofGetWidth());
			float _h = ofMap(mousePosition.y, 0.0, h, 0.0, ofGetHeight());
			
			return ofVec2f(_w, _h);

		}

		ofRectangle scaleRect(ofRectangle r) {

			float _x = ofMap(r.x, 0.0, w, 0.0, ofGetWidth());
			float _y = ofMap(r.y, 0.0, h, 0.0, ofGetHeight());
			float _w = ofMap(r.width, 0.0, w, 0.0, ofGetWidth());
			float _h = ofMap(r.height, 0.0, h, 0.0, ofGetHeight());

			return ofRectangle(_x, _y, _w, _h);
		}


		ofVec4f scaleCircle(ofCircleInfo c) {

			float _x = ofMap(c.getX(), 0.0, w, 0.0, ofGetWidth());
			float _y = ofMap(c.getY(), 0.0, h, 0.0, ofGetHeight());
			float _w = ofMap(c.getRadius(), 0.0, w, 0.0, ofGetWidth());
			float _h = ofMap(c.getRadius(), 0.0, h, 0.0, ofGetHeight());

			return ofVec4f(_x, _y, _w * 2, _h * 2);

		}

	};
}
