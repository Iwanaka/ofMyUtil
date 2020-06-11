#pragma once
#include "ofGraphics.h"

namespace ofxMyUtil 
{
	class ofCircleInfo
	{
	public:
		ofCircleInfo() {}
		ofCircleInfo(float px, float py, float radius) { Set(px, py, radius); }
		ofCircleInfo(const glm::vec2& pos, float radius) { Set(pos, radius); }
		ofCircleInfo(const ofCircleInfo& circle) { Set(circle.mPosition, circle.mRadius); }
		~ofCircleInfo() {}

		void Set(float px, float py, float radius);
		void Set(const glm::vec2 &p, float radius) { Set(p.x, p.y, radius); }
		void Set(const ofCircleInfo &circle) { Set(circle.mPosition, circle.mRadius); }

		void SetX(float px){ mPosition.x = px; }
		void SetY(float py){ mPosition.y = py; }
		void SetRadius(float radius) { mRadius = radius; }

		void SetPosition(float px, float py) { mPosition = glm::vec2(px, py); }
		void SetPosition(const glm::vec2 &p) { mPosition = p; }

		float GetX() { return mPosition.x; }
		float GetY() { return mPosition.y; }
		glm::vec2 GetPos() { return mPosition; }
		float GetRadius() { return mRadius; }

	private:

		glm::vec2 mPosition;
		float mRadius;

	};
}