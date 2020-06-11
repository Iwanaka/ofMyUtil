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

		bool JsonToFile(const std::string &buf, std::string savePath, bool pretty = true);
		bool JsonToFile(const ofBuffer &buf, std::string savePath, bool pretty = true);

		bool FboToFile(const ofFbo &fbo,  std::string savePath, 
			ofImageType type = ofImageType::OF_IMAGE_COLOR,
			ofImageQualityType quality = ofImageQualityType::OF_IMAGE_QUALITY_BEST);

		bool TextureToFile(const ofTexture &tex, std::string savePath, 
			ofImageType type = ofImageType::OF_IMAGE_COLOR,
			ofImageQualityType quallity = ofImageQualityType::OF_IMAGE_QUALITY_BEST);

		bool CheckExitsFile(const std::string& path, const float& retryTime);
		bool CreateDir(const std::string& path);

		bool TextToFile(const std::string& path, const std::stringstream& Args, bool append = false);
		bool TextToFile(const std::string& path, const char *Args, bool append = false);
		bool TextToFile(const std::string& path, std::string Args, bool append = false);

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