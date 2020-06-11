#pragma once
#include "ofGraphics.h"
#include "ofAppRunner.h"
#include "ofMath.h"
#include "ofCircleInfo.h"

// ウィンドウサイズに応じてGuiのスケール調整
namespace ofxMyUtil 
{
	class ofScaleable
	{
	private:
		int w, h;
	public:
		ofScaleable() : w(ofGetWidth()), h(ofGetHeight()) {}
		~ofScaleable() {}

		void SetDefalutScale(int w, int h) 
		{
			this->w = w;
			this->h = h;
		}

		void Begin() 
		{
			ofPushStyle();
			ofPushMatrix();
			float _w = (float)ofGetWidth() / (float)w;
			float _h = (float)ofGetHeight() / (float)h;
			ofScale(_w, _h);
		}

		void End() 
		{
			ofPopMatrix();
			ofPopStyle();
		}

		ofVec2f ScaleMouse(ofVec2f mousePosition) 
		{	
			float _w = ofMap(mousePosition.x, 0.0, w, 0.0, ofGetWidth());
			float _h = ofMap(mousePosition.y, 0.0, h, 0.0, ofGetHeight());			
			return ofVec2f(_w, _h);
		}

		ofRectangle ScaleRect(ofRectangle r) 
		{
			float _x = ofMap(r.x, 0.0, w, 0.0, ofGetWidth());
			float _y = ofMap(r.y, 0.0, h, 0.0, ofGetHeight());
			float _w = ofMap(r.width, 0.0, w, 0.0, ofGetWidth());
			float _h = ofMap(r.height, 0.0, h, 0.0, ofGetHeight());

			return ofRectangle(_x, _y, _w, _h);
		}


		ofVec4f scaleCircle(ofCircleInfo c) 
		{
			float _x = ofMap(c.GetX(), 0.0, w, 0.0, ofGetWidth());
			float _y = ofMap(c.GetY(), 0.0, h, 0.0, ofGetHeight());
			float _w = ofMap(c.GetRadius(), 0.0, w, 0.0, ofGetWidth());
			float _h = ofMap(c.GetRadius(), 0.0, h, 0.0, ofGetHeight());

			return ofVec4f(_x, _y, _w * 2, _h * 2);
		}

	};
}
