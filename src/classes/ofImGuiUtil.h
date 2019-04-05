#pragma once
#include "ofxImGui.h"
#include <functional>

//--------------------------------------------------------------
// ofxMyUtil ImGui
//--------------------------------------------------------------

namespace ofxMyUtil {

	//--------------------------------------------------------------
	namespace SP {
		
		bool loadArray2Float(const std::string &str, float *Array2);
		bool loadArray3Float(const std::string &str, float *Array3);

	}


	namespace im {


		void BasicInfos();
		void BasicInfos(const std::string &name, ImGuiWindowFlags flags = 0);

		void drawFbo(
			const ofFbo &fbo,
			GLuint &sourceID,
			std::string name = "fbo",
			ImGuiWindowFlags flag = 0);

		void drawImg(
			const ofImage &img,
			GLuint &sourceID,
			float scale = 1.0f,
			std::string name = "image",
			ImGuiWindowFlags flag = 0);

		//ê√ìIÇ»ä÷êîÇ»ÇÁÇ±ÇÍÇ≈åƒÇ◊ÇÈÇØÇ«templateÇ©functionÇ≈Ç‚Ç¡ÇΩÇŸÇ§Ç™ó«Ç≥ÇªÇ§
		void drawImgAsButton(
			const ofImage &img,
			GLuint &sourceID,
			void(*fn)(),
			float scale = 1.0f,
			std::string name = "image button",
			ImGuiWindowFlags flag = 0);
		
		void drawImgAsButton(
			const ofImage &img,
			GLuint &sourceID,
			std::function<void()> fn,
			float scale = 1.0f,
			std::string name = "image button",
			ImGuiWindowFlags flag = 0);




		//--------------------------------------------------------------
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
			void loadSettings(const std::string &path);
			void saveSettings(const std::string &path);
			ImGuiWindowFlags getImGuiWindowFlags();
			void ImGui(const std::string &name);

		private:
			ImGuiWindowFlags flags;
			bool no_titlebar, no_border, no_resize, no_move, no_scrollbar, no_collapse, no_menu;
		};




		//--------------------------------------------------------------
		class ImGuiWindowSetCondSettings {
		public:
			ImGuiWindowSetCondSettings() :
				value((int)ImGuiSetCond_::ImGuiSetCond_Appearing) {};
			~ImGuiWindowSetCondSettings() {};
			void changeState(const ImGuiSetCond_ &state);
			ImGuiSetCond_ getSetCondState();
			void ImGui(const std::string &name);
		private:
			int value;
		};
	}

}