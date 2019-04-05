#include "ofxMyUtilIO.h"
#include "ofJson.h"

//--------------------------------------------------------------
// ofxMyUtil IO
//--------------------------------------------------------------

using namespace ofxMyUtil;
using namespace std;

//--------------------------------------------------------------
bool IO::bufJsonToFile(const ofBuffer &buf, string savePath, bool pretty) {
	return jsonToFile(buf.getText(), savePath, pretty);
}

//--------------------------------------------------------------
bool IO::jsonToFile(const string &str, string savePath, bool pretty) {

	try
	{
		auto json = ofJson::parse(str);
		if (pretty) return ofSavePrettyJson(savePath, json);
		else return ofSaveJson(savePath, json);

	}
	catch (const std::exception&)
	{
		return 0;
	}


	return 1;
}

//--------------------------------------------------------------
bool IO::fboToFile(const ofFbo &fbo, string savePath, ofImageType type, ofImageQualityType quality) {

	ofPixels pix;
	pix.allocate(fbo.getWidth(), fbo.getHeight(), type);
	fbo.readToPixels(pix);
	
	return ofSaveImage(pix, savePath, quality);

}

//--------------------------------------------------------------
bool IO::textureToFile(const ofTexture &tex, std::string savePath, ofImageType type, ofImageQualityType quality) {

	ofPixels pix;
	pix.allocate(tex.getWidth(), tex.getHeight(), type);
	tex.readToPixels(pix);

	return ofSaveImage(pix, savePath, quality);

}

//--------------------------------------------------------------
bool IO::checkExitsFile(const string& path, const float& _retryTime) {

	ofFile file(path);

	float currentTime = ofGetElapsedTimef();
	float retryTime = _retryTime;
	float meusureTime = 0.0;

	while (file.exists() || meusureTime <= retryTime) {

		meusureTime = ofGetElapsedTimef() - currentTime;

		if (file.exists()) return true;
		if (meusureTime >= retryTime) return false;

	}

	return false;

}

//--------------------------------------------------------------
bool IO::createDirectory(const string& path) {

	//ofDirectory dir(path);
	//return ofDirectory::createDirectory(path);

	filesystem::path p(path);
	boost::system::error_code e;
	bool check = filesystem::exists(p, e);

	if (!check || !e) {
		bool create = filesystem::create_directory(path, e);
		if (create) return 1;
	}

	return 0;

}

//--------------------------------------------------------------
bool IO::createFile(const string& path, const stringstream& Args) {

	filebuf fb;
	fb.open(path, std::ios::out);

	bool result = fb.is_open();


	if (result) {

		std::ostream os(&fb);
		stringstream ss;
		ss << Args.rdbuf();

		while (!ss.fail()) {

			string temp;
			std::getline(ss, temp);
			if (!ss.eof()) os << temp << endl;
		}
	}

	fb.close();

	return result;
}

//--------------------------------------------------------------
bool IO::createFile(const string& path, const string& Args) { return IO::createFile(path, Args); }
