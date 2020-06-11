#include "ofxMyUtilIO.h"
#include "ofJson.h"

//--------------------------------------------------------------
// ofxMyUtil IO
//--------------------------------------------------------------
using namespace ofxMyUtil;
using namespace std;
//--------------------------------------------------------------
// *** Sample code ***
// stringstream ss;
// ss << "{\"One\":{\"a\":1,\"b\":\"test\"}}";
// ofBuffer buf(ss.str().c_str(), ss.str().size());
// ofxMyUtil::IO::jsonToFile(buf);
//--------------------------------------------------------------
bool IO::JsonToFile(const string &str, string savePath, bool pretty) 
{
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
bool IO::JsonToFile(const ofBuffer &buf, std::string savePath, bool pretty) {
	return JsonToFile(buf.getText(), savePath, pretty);
}

//--------------------------------------------------------------
bool IO::FboToFile(const ofFbo &fbo, string savePath, ofImageType type, ofImageQualityType quality) 
{
	ofPixels pix;
	pix.allocate(fbo.getWidth(), fbo.getHeight(), type);
	fbo.readToPixels(pix);

	return ofSaveImage(pix, savePath, quality);
}

//--------------------------------------------------------------
bool IO::TextureToFile(const ofTexture &tex, std::string savePath, ofImageType type, ofImageQualityType quality) 
{
	ofPixels pix;
	pix.allocate(tex.getWidth(), tex.getHeight(), type);
	tex.readToPixels(pix);

	return ofSaveImage(pix, savePath, quality);
}

//--------------------------------------------------------------
bool IO::CheckExitsFile(const string& path, const float& _retryTime) 
{
	ofFile file(path);

	float currentTime = ofGetElapsedTimef();
	float retryTime = _retryTime;
	float meusureTime = 0.0;

	while (file.exists() || meusureTime <= retryTime) 
	{
		meusureTime = ofGetElapsedTimef() - currentTime;

		if (file.exists()) return true;
		if (meusureTime >= retryTime) return false;
	}

	return false;
}

//--------------------------------------------------------------
bool IO::CreateDir(const string& path) 
{
	//ofDirectory dir(path);
	//return ofDirectory::createDirectory(path);

	filesystem::path p(path);
	boost::system::error_code e;
	bool check = filesystem::exists(p, e);

	if (!check || !e) 
	{
		bool create = filesystem::create_directory(path, e);
		if (create) return 1;
	}
	return 0;
}

//--------------------------------------------------------------
bool IO::TextToFile(const string& path, const stringstream& Args, bool append)
{
	//ofFile f(path, ofFile::ReadWrite);
	//if (!f.exists()) f.create();

	filebuf fb;
	if (append) fb.open(path, ios::app);
	else fb.open(path, std::ios::out);

	if (!fb.is_open()) return false;

	std::ostream os(&fb);
	stringstream ss(Args.str());

	if (ss.fail()) return false;

	string temp;
	while (std::getline(ss, temp)) 
	{
		if (temp != "") 
		{
			os << temp << endl;
		}
	}

	fb.close();
	return true;
}

//--------------------------------------------------------------
bool IO::TextToFile(const std::string& path, const char *Args, bool append) 
{
	std::stringstream ss;
	ss << Args;
	return TextToFile(path, ss, append);
}

bool IO::TextToFile(const std::string& path, std::string Args, bool append) 
{
	std::stringstream ss;
	ss << Args;
	return TextToFile(path, ss, append);
}