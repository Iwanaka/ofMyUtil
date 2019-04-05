#pragma once
#include "ofThread.h"
#include "ofPixels.h"
#include "ofImage.h"
#include <queue>


namespace ofxMyUtil {

	typedef struct {
		std::string savePath = "/";
		ofPixels pix = ofPixels();
		ofImageQualityType qType = ofImageQualityType::OF_IMAGE_QUALITY_BEST;
	}ofSaveImageQueue;

	class ofThreadSaveImage : public ofThread
	{
	private:

		std::queue< ofSaveImageQueue> q;

	public:
		
		ofThreadSaveImage() {}
		~ofThreadSaveImage() { stop(); }

		void run() { startThread(); }
		void stop() { waitForThread(); }

		void threadedFunction() {
			while (isThreadRunning()) {
				if (!q.empty()) {
					ofSaveImageQueue i = q.front();
					ofSaveImage(i.pix, i.savePath, i.qType);
					q.pop();
				}
			}
		}

		void addQueue(const ofSaveImageQueue &queue) { q.push(queue); }
		void addQueue(const ofPixels &pix, const std::string &savePath, const ofImageQualityType type) {

			ofSaveImageQueue _q;
			_q.pix = pix;
			_q.savePath = savePath;
			_q.qType = type;
			addQueue(_q);

		}

	};
}

