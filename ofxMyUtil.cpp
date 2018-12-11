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
void ofxMyUtil::_ImGui::BasicInfos(const std::string &name, const ImGuiWindowFlags &flags) {

	ImGui::Begin(name.c_str(), 0, flags);
	if (ImGui::CollapsingHeader("_ImGui Basic Infos", 0)) {

		ImGui::Text("ip address : %s", ofxMyUtil::IO::getIpAddress().c_str());
		ImGui::Text("framerate :  %s", ofToString(ofGetFrameRate(), 4).c_str());
		
	}
	ImGui::End();

}

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
	if (ImGui::CollapsingHeader("_ImGui window style settings", 0)) {
		ImGui::Checkbox("No titlebar", &no_titlebar);;
		ImGui::Checkbox("No border", &no_border);;
		ImGui::Checkbox("No resize", &no_resize);
		ImGui::Checkbox("No move", &no_move);;
		ImGui::Checkbox("No scrollbar", &no_scrollbar);;
		ImGui::Checkbox("No collapse", &no_collapse);
		ImGui::Checkbox("No menu", &no_menu);
	}
	
	ImGui::End();

}