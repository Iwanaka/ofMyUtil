#include "ofxMyUtil.h"

using namespace std;

//--------------------------------------------------------------
// File
//--------------------------------------------------------------

//--------------------------------------------------------------
void ofxMyUtil::File::bufferToJsonFile(const ofBuffer &buf, const string &savePath = "result.json", const bool& console = false) {

	ofxJSONElement json;
	//ofJson json;
	json.parse(buf.getText());

	if (console) cout << json << endl;

	//if (ofSaveJson(savePath, json)) cout << "save seccess \"" << savePath << "\"" << endl;
	if (json.save(savePath, true)) cout << "save seccess \"" << savePath << "\"" << endl;
	else cout << "save faild \"" << savePath << "\"" << endl;;

}

//--------------------------------------------------------------
bool ofxMyUtil::File::saveImageAs(const ofFbo &fbo, const string &savePath, ofImageType type = OF_IMAGE_COLOR) {

	ofPixels pix;
	pix.allocate(fbo.getWidth(), fbo.getHeight(), type);
	fbo.readToPixels(pix);

	return ofSaveImage(pix, savePath, OF_IMAGE_QUALITY_BEST);

}

//--------------------------------------------------------------
bool ofxMyUtil::File::checkExitsFile(const string& path,const float& _retryTime) {

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
bool ofxMyUtil::File::createDirectory(const string& path) {

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
bool ofxMyUtil::File::createFile(const string& path, const stringstream& Args) {

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
bool ofxMyUtil::File::saveRandomText(const string &path, const unsigned int &length, const unsigned int &size) {

	stringstream ss;
	for (int i = 0; i < size; i++) {
		ss << i << ":" << ofxMyUtil::String::generateRandomText(length) << "\n";
	}

	return ofxMyUtil::File::createFile(path, ss);

}



//--------------------------------------------------------------
// ThreadSaveImageQueue
//--------------------------------------------------------------
ofxMyUtil::File::ThreadSaveImageQueue::ThreadSaveImageQueue() {}

//--------------------------------------------------------------
ofxMyUtil::File::ThreadSaveImageQueue::~ThreadSaveImageQueue() {
	stop();
}

//--------------------------------------------------------------
void ofxMyUtil::File::ThreadSaveImageQueue::run() {
	startThread();
}

//--------------------------------------------------------------
void ofxMyUtil::File::ThreadSaveImageQueue::stop() {
	while (isThreadRunning()) {
		stopThread();
	}
}

//--------------------------------------------------------------
void ofxMyUtil::File::ThreadSaveImageQueue::threadedFunction() {
	while (isThreadRunning()) {
		if (!q.empty()) {
			QueuePix i = q.front();
			ofSaveImage(i.pix, i.savePath);
			q.pop();
		}
	}
}

//--------------------------------------------------------------
void ofxMyUtil::File::ThreadSaveImageQueue::addQueue(const ofPixels &pix, const string &savePath) {

	QueuePix qPix;
	qPix.pix = pix;
	qPix.savePath = savePath;
	q.push(qPix);

}


//--------------------------------------------------------------
// String
//--------------------------------------------------------------

//--------------------------------------------------------------
string ofxMyUtil::String::adjustFileNo(const unsigned int& currentNo,const unsigned int& digit) {

	string No = ofToString(currentNo);

	for (int i = No.length(); i < digit; i++) {
		No = "0" + No;
	}

	return No;
}

//--------------------------------------------------------------
std::string ofxMyUtil::String::generateRandomText(const unsigned int &length) {

	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);

		return charset[rand() % max_index];

	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);

	return str;

}

//--------------------------------------------------------------
// Event
//--------------------------------------------------------------

//--------------------------------------------------------------
bool ofxMyUtil::Event::rectButtonClickDetect(ofRectangle rect, int mouseX, int mouseY) {

	if (rect.x <= mouseX &&
		mouseX <= rect.x + rect.width &&
		rect.y <= mouseY &&
		mouseY <= rect.y + rect.height)
	{
		return 1;
	}
	else {
		return 0;
	}

}


//--------------------------------------------------------------
bool ofxMyUtil::Event::rectButtonClickDetect(int x, int y, int w, int h, int mouseX, int mouseY) {

	if (x <= mouseX &&
		mouseX <= x + w &&
		y <= mouseY &&
		mouseY <= y + h)
	{
		return 1;
	}
	else {
		return 0;
	}

}

//--------------------------------------------------------------
bool ofxMyUtil::Event::circleButtonClickDetect(int x, int y, float radius, int mouseX, int mouseY) {

	if (ofDist(x, y, mouseX, mouseY) < radius) return 1;
	else return 0;

}


//--------------------------------------------------------------
// Console
//--------------------------------------------------------------


//--------------------------------------------------------------
//7:normal 8:gray 9:blue 10:green 11:aqua 12:red 13:purple 14:yellow 15:white
void ofxMyUtil::Console::chengeConsollColor(unsigned short colorID) {

	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, colorID);

}

//--------------------------------------------------------------
void ofxMyUtil::Console::hideConsole() {
	
	HWND handle;
	AllocConsole();
	handle = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(handle, 0);
}

//--------------------------------------------------------------
// IO
//--------------------------------------------------------------

//--------------------------------------------------------------
string ofxMyUtil::IO::getIpAddress() {

	int i;
	HOSTENT *lpHost;
	IN_ADDR inaddr;
	char szBuf[256], szIP[16];
	
	gethostname(szBuf, (int)sizeof(szBuf));
	//printf("HOST Name : %s\n", szBuf);

	lpHost = gethostbyname(szBuf);
	
	for (i = 0; lpHost->h_addr_list[i]; i++) {

		memcpy(&inaddr, lpHost->h_addr_list[i], 4);
		
		strcpy(szIP, inet_ntoa(inaddr));
		
	}

	return string(szIP);

}

//--------------------------------------------------------------
int ofxMyUtil::IO::getIpHost() {

	int i;
	HOSTENT *lpHost;
	IN_ADDR inaddr;
	char szBuf[256], szIP[16];

	gethostname(szBuf, (int)sizeof(szBuf));
	printf("HOST Name : %s\n", szBuf);

	lpHost = gethostbyname(szBuf);

	for (i = 0; lpHost->h_addr_list[i]; i++) {
		memcpy(&inaddr, lpHost->h_addr_list[i], 4);
		strcpy(szIP, inet_ntoa(inaddr));
		printf("IP Adress : %s\n", szIP);
	}

	return 0;

}

//--------------------------------------------------------------
// ImGui
//--------------------------------------------------------------

//--------------------------------------------------------------
void ofxMyUtil::_ImGui::BasicInfos(const std::string &name, ImGuiWindowFlags flags) {

	ImGui::Begin(name.c_str(), 0, flags);
	if (ImGui::CollapsingHeader("_ImGui Basic Infos", 0)) {

		ImGui::Text("ip address : %s", ofxMyUtil::IO::getIpAddress().c_str());
		ImGui::Text("framerate :  %s", ofToString(ofGetFrameRate(), 4).c_str());
		
		ImGui::Text("position : x %.2f, y %.2f", ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
		ImGui::Text("size : x %.2f, y %.2f", ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);

	}
	ImGui::End();

}

//--------------------------------------------------------------
// ImGui Window Falgs Settings
//--------------------------------------------------------------
ImGuiWindowFlags ofxMyUtil::_ImGui::ImGuiWindowFlagsSettings::getImGuiWindowFlags() {

	return flags;

}

//--------------------------------------------------------------
void ofxMyUtil::_ImGui::ImGuiWindowFlagsSettings::ImGui(const string &name) {

	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_border)    window_flags |= ImGuiWindowFlags_ShowBorders;
	if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
	if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
	if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_menu)      window_flags |= ImGuiWindowFlags_MenuBar;
	flags = window_flags;

	ImGui::Begin(name.c_str(), 0, window_flags);
	ImGui::PushID(name.c_str());
	if (ImGui::CollapsingHeader("_ImGui window style settings", 0)) {
		ImGui::Checkbox("No titlebar", &no_titlebar);;
		ImGui::Checkbox("No border", &no_border);;
		ImGui::Checkbox("No resize", &no_resize);
		ImGui::Checkbox("No move", &no_move);;
		ImGui::Checkbox("No scrollbar", &no_scrollbar);;
		ImGui::Checkbox("No collapse", &no_collapse);
		ImGui::Checkbox("No menu", &no_menu);
	}
	ImGui::PopID();
	ImGui::End();

}

//--------------------------------------------------------------
void ofxMyUtil::_ImGui::ImGuiWindowFlagsSettings::loadSettings(const string &path) {

	ofFile file(path);
	if (!file.exists()) return;
	ofBuffer buf(file);

	for (ofBuffer::Line it = buf.getLines().begin(), end = buf.getLines().end(); it != end; it++) {
	
		string line = *it;
		if (line == "") continue;
		vector<string> temp = ofSplitString(line, ":");
		
		if (2 == temp.size()) {
			if ("no_titlebar" == temp[0]) no_titlebar = ofToBool(temp[1]);
			if ("no_border" == temp[0]) no_border = ofToBool(temp[1]);
			if ("no_resize" == temp[0]) no_resize = ofToBool(temp[1]);
			if ("no_move" == temp[0]) no_move = ofToBool(temp[1]);
			if ("no_scrollbar" == temp[0]) no_scrollbar = ofToBool(temp[1]);
			if ("no_collapse" == temp[0]) no_collapse = ofToBool(temp[1]);
			if ("no_menu" == temp[0]) no_menu = ofToBool(temp[1]);
		}
	}
}

//--------------------------------------------------------------
void ofxMyUtil::_ImGui::ImGuiWindowFlagsSettings::saveSettings(const string &path) {

	stringstream ss;
	ss << "no_titlebar:" << no_titlebar << "\n";
	ss << "no_border:" << no_border << "\n";
	ss << "no_resize:" << no_resize << "\n";
	ss << "no_move:" << no_move << "\n";
	ss << "no_scrollbar:" << no_scrollbar << "\n";
	ss << "no_collapse:" << no_collapse << "\n";
	ss << "no_menu:" << no_menu << "\n";

	ofxMyUtil::File::createFile(path, ss);

}

//--------------------------------------------------------------
// ImGuiWindowSetCondSettings
//--------------------------------------------------------------
void ofxMyUtil::_ImGui::ImGuiWindowSetCondSettings::changeState(const ImGuiSetCond_ &state) {
	value = state;
}

//--------------------------------------------------------------
ImGuiSetCond_ ofxMyUtil::_ImGui::ImGuiWindowSetCondSettings::getSetCondState() {
	return (ImGuiSetCond_)value;
}

//--------------------------------------------------------------
void ofxMyUtil::_ImGui::ImGuiWindowSetCondSettings::ImGui(const string &name) {

	ImGui::Begin(name.c_str());
	{
		if (ImGui::CollapsingHeader("_ImGui window setCond settings")) {

			ImGui::RadioButton("Always", &value, (int)ImGuiSetCond_::ImGuiSetCond_Always);
			ImGui::RadioButton("Appearing", &value, (int)ImGuiSetCond_::ImGuiSetCond_Appearing);
			ImGui::RadioButton("FirstUseEver", &value, (int)ImGuiSetCond_::ImGuiSetCond_FirstUseEver);
			ImGui::RadioButton("Once", &value, (int)ImGuiSetCond_::ImGuiSetCond_Once);

		}
	}
	ImGui::End();

}

//スケールを縮尺する場合、なぜか0.2とか0.3とかの少数第一位までしか指定できない
//--------------------------------------------------------------
void ofxMyUtil::_ImGui::drawFbo(const ofFbo &fbo, GLuint &sourceID, string name, ImGuiWindowFlags flag) {

	if (!fbo.isAllocated()) return;
	
	ofPixels pix;
	pix.clear();

	fbo.readToPixels(pix);
	pix.setImageType(OF_IMAGE_COLOR_ALPHA);
	glDeleteTextures(1, &sourceID);
	sourceID = ofxMyUtil::GL::loadTextureImage2D(pix.getData(), fbo.getWidth(), fbo.getHeight());
	
	ImGui::Begin(name.c_str(), 0, ImVec2(fbo.getWidth() * 1.1, fbo.getHeight()* 1.1f), .5f, flag);
	{
		ImGui::Image((ImTextureID)(uintptr_t)sourceID, ImVec2(fbo.getWidth(), fbo.getHeight()));
	}
	ImGui::End();

}

//--------------------------------------------------------------
void ofxMyUtil::_ImGui::drawImg(const ofImage &img, GLuint &sourceID, float scale, string name, ImGuiWindowFlags flag) {

	if (!img.isAllocated()) return;

	glDeleteTextures(1, &sourceID);
	ofPixels pix = img.getPixels();
	pix.setImageType(OF_IMAGE_COLOR_ALPHA);
	sourceID = ofxMyUtil::GL::loadTextureImage2D(pix.getData(), img.getWidth(), img.getHeight());
	
	ImGui::Begin(name.c_str(), 0, ImVec2(img.getWidth() * scale * 1.1f, img.getHeight() * scale * 1.3f), .0f, flag);
	{
		ImGui::Image((ImTextureID)(uintptr_t)sourceID, ImVec2(img.getWidth()* scale, img.getHeight()* scale));
	}
	ImGui::End();

}

//--------------------------------------------------------------
void ofxMyUtil::_ImGui::drawImgAsButton(const ofImage &img, GLuint &sourceID, void (*fn)(), float scale, string name, ImGuiWindowFlags flag) {

	glDeleteTextures(1, &sourceID);
	ofPixels pix = img.getPixels();
	pix.setImageType(OF_IMAGE_COLOR_ALPHA);
	sourceID = ofxMyUtil::GL::loadTextureImage2D(pix.getData(), img.getWidth(), img.getHeight());

	ImGui::Begin(name.c_str(), 0, ImVec2(img.getWidth() *scale * 1.1f, img.getHeight() * scale * 1.3f), .0f, flag);
	{
		if (ImGui::ImageButton((ImTextureID)(uintptr_t)sourceID, ImVec2(img.getWidth()* scale, img.getHeight()* scale))) {
			fn();
		}
	}
	ImGui::End();

}


//--------------------------------------------------------------
// GL
//--------------------------------------------------------------

//--------------------------------------------------------------
GLuint ofxMyUtil::GL::loadTextureImage2D(unsigned char * pix, int width, int height) {

	GLint last_texture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	GLuint new_texture;
	glGenTextures(1, &new_texture);
	glBindTexture(GL_TEXTURE_2D, new_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width, height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		pix
	);
	glBindTexture(GL_TEXTURE_2D, last_texture);
	return new_texture;

}

//--------------------------------------------------------------
// SP
//--------------------------------------------------------------

//--------------------------------------------------------------
bool ofxMyUtil::SP::loadArray2Float(const string &str, float *Array2) {
	
	vector<string> _temp = ofSplitString(str, ",");
	if (2 != _temp.size()) return 0;

	Array2[0] = ofToFloat(_temp[0]);
	Array2[1] = ofToFloat(_temp[1]);
	return 1;

}

//--------------------------------------------------------------
bool ofxMyUtil::SP::loadArray3Float(const string &str, float *Array3) {

	vector<string> _temp = ofSplitString(str, ",");
	if (3 != _temp.size())return 0;

	Array3[0] = ofToFloat(_temp[0]);
	Array3[1] = ofToFloat(_temp[1]);
	Array3[2] = ofToFloat(_temp[2]);
	return 1;
}
