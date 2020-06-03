#include "ofImGuiUtil.h"
#include "ofxMyUtilMedia.h"
#include "ofxMyUtilIO.h"
#include "ofxMyUtilGL.h"
#include "ofAppRunner.h"

//--------------------------------------------------------------
// ofxMyUtil ImGui
//--------------------------------------------------------------
using namespace ofxMyUtil;
using namespace std;

//--------------------------------------------------------------
void im::BasicInfos() {

	ImGui::Text("My IP Address : %s", Media::getIpAddress().c_str());
	ImGui::Text("FPS :  %s", ofToString(ofGetFrameRate(), 4).c_str());

}

//--------------------------------------------------------------
void im::BasicInfos(const std::string &name, ImGuiWindowFlags flags) {

	if (ImGui::Begin(name.c_str(), 0, flags)) {

		BasicInfos();
		ImGui::End();

	}
}

//--------------------------------------------------------------
void im::BasicInfosWindow() {

	ImGui::Text("this window size : x %f, y %f", ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
	ImGui::Text("this window position : x %f, y %f", ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
	
}

//�X�P�[�����k�ڂ���ꍇ�A�Ȃ���0.2�Ƃ�0.3�Ƃ��̏������ʂ܂ł����w��ł��Ȃ�
//--------------------------------------------------------------
void im::drawFbo(
	const ofFbo &fbo,
	GLuint &sourceID,
	string name,
	ImGuiWindowFlags flag
) {

	if (!fbo.isAllocated()) return;

	ofPixels pix;
	pix.clear();

	fbo.readToPixels(pix);
	pix.setImageType(OF_IMAGE_COLOR_ALPHA);
	glDeleteTextures(1, &sourceID);
	sourceID = ofxMyUtil::GL::loadTextureImage2D(pix.getData(), fbo.getWidth(), fbo.getHeight());

	ImGui::Begin(name.c_str(), 0, flag);
	//ImGui::Begin(name.c_str(), 0, ImVec2(fbo.getWidth() * 1.1, fbo.getHeight()* 1.1f), .5f, flag);
	{
		ImGui::Image((ImTextureID)(uintptr_t)sourceID, ImVec2(fbo.getWidth(), fbo.getHeight()));
	}
	ImGui::End();

}

//--------------------------------------------------------------
void im::drawImg(
	const ofImage &img,
	GLuint &sourceID,
	float scale,
	string name,
	ImGuiWindowFlags flag
) {

	if (!img.isAllocated()) return;

	glDeleteTextures(1, &sourceID);
	ofPixels pix = img.getPixels();
	pix.setImageType(OF_IMAGE_COLOR_ALPHA);
	sourceID = ofxMyUtil::GL::loadTextureImage2D(pix.getData(), img.getWidth(), img.getHeight());

	ImGui::Begin(name.c_str(), 0, flag);
	//ImGui::Begin(name.c_str(), 0, ImVec2(img.getWidth() * scale * 1.1f, img.getHeight() * scale * 1.3f), .0f, flag);
	{
		ImGui::Image((ImTextureID)(uintptr_t)sourceID, ImVec2(img.getWidth()* scale, img.getHeight()* scale));
	}
	ImGui::End();

}

//--------------------------------------------------------------
void im::drawImgAsButton(
	const ofImage &img,
	GLuint &sourceID,
	void(*fn)(),
	float scale,
	string name,
	ImGuiWindowFlags flag
) {
	glDeleteTextures(1, &sourceID);
	ofPixels pix = img.getPixels();
	pix.setImageType(OF_IMAGE_COLOR_ALPHA);
	sourceID = ofxMyUtil::GL::loadTextureImage2D(pix.getData(), img.getWidth(), img.getHeight());

	ImGui::Begin(name.c_str(), 0, flag);
	//ImGui::Begin(name.c_str(), 0, ImVec2(img.getWidth() *scale * 1.1f, img.getHeight() * scale * 1.3f), .0f, flag);
	{
		if (ImGui::ImageButton((ImTextureID)(uintptr_t)sourceID, ImVec2(img.getWidth()* scale, img.getHeight()* scale))) {
			fn();
		}
	}
	ImGui::End();

}

//--------------------------------------------------------------
void im::drawImgAsButton(
	const ofImage &img,
	GLuint &sourceID,
	function<void()> fn,
	float scale,
	string name,
	ImGuiWindowFlags flag
) {

	glDeleteTextures(1, &sourceID);
	ofPixels pix = img.getPixels();
	pix.setImageType(OF_IMAGE_COLOR_ALPHA);
	sourceID = ofxMyUtil::GL::loadTextureImage2D(pix.getData(), img.getWidth(), img.getHeight());

	ImGui::Begin(name.c_str(), 0, flag);
	//ImGui::Begin(name.c_str(), 0, ImVec2(img.getWidth() *scale * 1.1f, img.getHeight() * scale * 1.3f), .0f, flag);
	{
		if (ImGui::ImageButton((ImTextureID)(uintptr_t)sourceID, ImVec2(img.getWidth()* scale, img.getHeight()* scale))) {
			fn();
		}
	}
	ImGui::End();

}

//--------------------------------------------------------------
// ImGuiWindowSetCondSettings
//--------------------------------------------------------------
void im::ImGuiLogWindow::addText(std::string str) {
	
	_log.push_back(str);

	if (maxSize < _log.size()) {
		_log.erase(_log.begin());
	}
}

//--------------------------------------------------------------
void im::ImGuiLogWindow::setMaxLogSize(unsigned long size) {
	maxSize = size;
}

//--------------------------------------------------------------
void im::ImGuiLogWindow::ImGui(const std::string &name) {

	if (!ImGui::Begin(name.c_str())) { ImGui::End(); return; }

	ImGui::BeginChild("Logs");
	auto logs = _log;
	for each (string l in	logs) ImGui::TextWrapped("%s", l.c_str());
	ImGui::EndChild();

	ImGui::End();
}

//--------------------------------------------------------------
void im::ImGuiLogWindow::clear() {
	_log.clear();
}

//--------------------------------------------------------------
// ImGui Window Falgs Settings
//--------------------------------------------------------------
ImGuiWindowFlags im::ImGuiWindowFlagsSettings::getImGuiWindowFlags() {

	return flags;

}

//--------------------------------------------------------------
void im::ImGuiWindowFlagsSettings::ImGui(const string &name, bool showSettings) {
	
	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
	if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
	if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_menu)      window_flags |= ImGuiWindowFlags_MenuBar;
	flags = window_flags;

	ImGui::Begin(name.c_str(), 0, window_flags);
	if (showSettings) {
		ImGui::PushID(name.c_str());
		if (ImGui::CollapsingHeader("_ImGui window style settings", 0)) {
			ImGui::Checkbox("No titlebar", &no_titlebar);;
			ImGui::Checkbox("No resize", &no_resize);
			ImGui::Checkbox("No move", &no_move);;
			ImGui::Checkbox("No scrollbar", &no_scrollbar);;
			ImGui::Checkbox("No collapse", &no_collapse);
			ImGui::Checkbox("No menu", &no_menu);
		}
		ImGui::PopID();
	}
	ImGui::End();

}

//--------------------------------------------------------------
void im::ImGuiWindowFlagsSettings::loadSettings(const string &path) {

	ofFile file(path);
	if (!file.exists()) return;
	ofBuffer buf(file);

	for (ofBuffer::Line it = buf.getLines().begin(), end = buf.getLines().end(); it != end; it++) {

		string line = *it;
		if (line == "") continue;
		vector<string> temp = ofSplitString(line, ":");

		if (2 == temp.size()) {
			if ("no_titlebar" == temp[0]) no_titlebar = ofToBool(temp[1]);
			if ("no_resize" == temp[0]) no_resize = ofToBool(temp[1]);
			if ("no_move" == temp[0]) no_move = ofToBool(temp[1]);
			if ("no_scrollbar" == temp[0]) no_scrollbar = ofToBool(temp[1]);
			if ("no_collapse" == temp[0]) no_collapse = ofToBool(temp[1]);
			if ("no_menu" == temp[0]) no_menu = ofToBool(temp[1]);
		}
	}
}

//--------------------------------------------------------------
void im::ImGuiWindowFlagsSettings::saveSettings(const string &path) {

	stringstream ss;
	ss << "no_titlebar:" << no_titlebar << "\n";
	ss << "no_resize:" << no_resize << "\n";
	ss << "no_move:" << no_move << "\n";
	ss << "no_scrollbar:" << no_scrollbar << "\n";
	ss << "no_collapse:" << no_collapse << "\n";
	ss << "no_menu:" << no_menu << "\n";

	IO::createFile(path, ss);

}

//--------------------------------------------------------------
// ImGuiWindowSetCondSettings
//--------------------------------------------------------------
void im::ImGuiWindowSetCondSettings::changeState(const int &state) {
	value = state;
}

//--------------------------------------------------------------
int im::ImGuiWindowSetCondSettings::getSetCondState() {
	return value;
}

//--------------------------------------------------------------
void im::ImGuiWindowSetCondSettings::ImGui(const string &name) {

	ImGui::Begin(name.c_str());
	{
		if (ImGui::CollapsingHeader("_ImGui window setCond settings")) {

			ImGui::RadioButton("Always", &value, ImGuiCond_Always);
			ImGui::RadioButton("Appearing", &value, ImGuiCond_Appearing);
			ImGui::RadioButton("FirstUseEver", &value, ImGuiCond_FirstUseEver);
			ImGui::RadioButton("Once", &value, ImGuiCond_Once);
			
		}
	}
	ImGui::End();

}