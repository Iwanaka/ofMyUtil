#pragma once
#include "ofGraphics.h"

namespace ofxMyUtil {
	class ofCircleInfo
	{
	public:
		ofCircleInfo();
		ofCircleInfo(float px, float py, float radius);
		ofCircleInfo(const glm::vec2& pos, float radius);
		ofCircleInfo(const ofCircleInfo& circle);
		~ofCircleInfo();

		void set(float px, float py, float radius);
		void set(const glm::vec2 &p, float radius);
		void set(const ofCircleInfo &circle);

		void setX(float px);
		void setY(float py);
		void setRadius(float radius);

		void setPosition(float px, float py);
		void setPosition(const glm::vec2 &p);

		float getX();
		float getY();
		glm::vec2 getPos();
		float getRadius();

	private:

		glm::vec2 position;
		float radius;

	};
}