#pragma once

#include "ofxJSON.h"
#include <winsock2.h>

namespace ofxMyUtil {

	namespace File {

		bool checkExitsFile(const std::string& path,const float& _retryTime);

		void bufferToJsonFile(const ofBuffer &buf,const std::string& savePath, const bool& console);

		std::string adjustFileNo(const unsigned int& currentNo, const unsigned int& digit);

	}
	
	namespace console {
		void chengeConsollColor(unsigned short colorID);
	}

	namespace IO {
		std::string getIpAddress();
		int getIpHost();
	}
};
