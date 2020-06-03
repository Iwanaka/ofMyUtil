#pragma once
#include <string>
#include "ofFileUtils.h"
#include "ofFbo.h"
#include "ofTexture.h"
#include "ofImage.h"
#include "ofJson.h"

//--------------------------------------------------------------
// ofxMyUtil IO
//--------------------------------------------------------------

namespace ofxMyUtil {
	namespace IO {

		bool bufJsonToFile(const ofBuffer &buf, std::string savePath = "res.json", bool pretty = true);
		
		bool jsonToFile(const std::string &buf, std::string savePath = "res.json", bool pretty = true);
		
		bool fboToFile(
			const ofFbo &fbo, 
			std::string savePath = "res.jpg", 
			ofImageType type = ofImageType::OF_IMAGE_COLOR,
			ofImageQualityType quality = ofImageQualityType::OF_IMAGE_QUALITY_BEST);

		bool textureToFile(
			const ofTexture &tex, 
			std::string savePath = "res.jpg", 
			ofImageType type = ofImageType::OF_IMAGE_COLOR,
			ofImageQualityType quallity = ofImageQualityType::OF_IMAGE_QUALITY_BEST);

		bool checkExitsFile(const std::string& path, const float& _retryTime);

		bool createDirectory(const std::string& path);

		bool createFile(const std::string& path, const std::stringstream& Args);
		bool createFile(const std::string&path, const std::string& Args);

		//template <typename T>
		//bool loadJsonAsKey(const nlohmann::json::value_type &j, T& val, T initVal) {
		//	if (j.is_null()) { 
		//		val = initVal; return false; 
		//	}
		//	else { 
		//		val = j.get<T>(); return true; 
		//	}
		//}

	}
}