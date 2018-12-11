#pragma once

#include <winsock2.h>
#include "ofMain.h"

#include "ofxJSON.h"
#include "ofxImGui.h"

using namespace std;

namespace ofxMyUtil {

	namespace File {

		bool checkExitsFile(const string& path,const float& _retryTime);
		bool createDirectory(const string& path);
		bool createFile(const string& path, const stringstream& Args);
		void bufferToJsonFile(const ofBuffer &buf,const string& savePath, const bool& console);
		bool saveImageAs(const ofFbo &fbo, const string &savePath, ofImageType type);
		bool saveRandomText(const string &path, const unsigned int &length,const unsigned int &size);
	}

	namespace String {

		std::string adjustFileNo(const unsigned int& currentNo, const unsigned int& digit);
		std::string generateRandomText(const unsigned int &length);

	}

	namespace Event {
		bool rectButtonClickDetect(ofRectangle rect, int mouseX, int mouseY);
		bool rectButtonClickDetect(int x, int y, int w, int h, int mouseX, int mouseY);
		bool circleButtonClickDetect(int x, int y, float radius, int mouseX, int mouseY);

	}
	
	namespace Console {
		void chengeConsollColor(unsigned short colorID);
		void hideConsole();
	}

	namespace IO {
		std::string getIpAddress();
		int getIpHost();
	}

	namespace _ImGui {
		void BasicInfos(const std::string &name, const ImGuiWindowFlags &flags);

		class ImGuiWindowFlagsSettings {
		public:
			ImGuiWindowFlagsSettings() :
				no_titlebar(false),
				no_border(false),
				no_resize(false),
				no_move(false),
				no_scrollbar(false),
				no_collapse(false),
				no_menu(false),
				flags(0) {}
			~ImGuiWindowFlagsSettings() {}
			ImGuiWindowFlags getImGuiWindowFlags();
			void ImGui(const string &name);
		private:
			ImGuiWindowFlags flags;
			bool no_titlebar, no_border, no_resize, no_move, no_scrollbar, no_collapse, no_menu;
		};
		
	}
};
