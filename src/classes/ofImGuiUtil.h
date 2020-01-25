#pragma once
#include "ofxImGui.h"
#include <functional>

//--------------------------------------------------------------
// ofxMyUtil ImGui
//--------------------------------------------------------------

namespace ofxMyUtil {

	namespace im {

		//ImGui���Ɋ�{���\��
		void BasicInfos();
		void BasicInfos(const std::string &name, ImGuiWindowFlags flags = 0);

		//ImGui����Fbo��\��
		void drawFbo(
			const ofFbo &fbo,
			GLuint &sourceID,
			std::string name = "fbo",
			ImGuiWindowFlags flag = 0);

		//ImGui���ɉ摜��\��
		void drawImg(
			const ofImage &img,
			GLuint &sourceID,
			float scale = 1.0f,
			std::string name = "image",
			ImGuiWindowFlags flag = 0);

		//ImGui���Ƀ{�^���Ƃ��ĉ摜��\���A�֐��|�C���^�ŃR�[���o�b�N
		void drawImgAsButton(
			const ofImage &img,
			GLuint &sourceID,
			void(*fn)(),
			float scale = 1.0f,
			std::string name = "image button",
			ImGuiWindowFlags flag = 0);
		
		//ImGui���Ƀ{�^���Ƃ��ĉ摜��\���Afunction�ŃR�[���o�b�N
		void drawImgAsButton(
			const ofImage &img,
			GLuint &sourceID,
			std::function<void()> fn,
			float scale = 1.0f,
			std::string name = "image button",
			ImGuiWindowFlags flag = 0);


		//--------------------------------------------------------------
		//���O�\��
		class ImGuiLogWindow {
		public:
			ImGuiLogWindow() : 
				maxSize(1000),
				_log(std::vector<std::string>()) {}
			~ImGuiLogWindow() {}
			void addText(std::string str);
			void setMaxLogSize(unsigned long size);
			void ImGui(const std::string &name);
			void clear();
		private:
			unsigned long maxSize;
			std::vector<std::string> _log;
		};

		//--------------------------------------------------------------
		//Window�̏ڍאݒ�N���X
		class ImGuiWindowFlagsSettings {
		public:
			ImGuiWindowFlagsSettings() :
				no_titlebar(false),
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
			bool no_titlebar, no_resize, no_move, no_scrollbar, no_collapse, no_menu;
		};


		//--------------------------------------------------------------
		//Window�̈ʒu�̐U�镑���ݒ�N���X
		class ImGuiWindowSetCondSettings {
		public:
			ImGuiWindowSetCondSettings() :
				value((int)ImGuiSetCond_Appearing) {};
			~ImGuiWindowSetCondSettings() {};
			void changeState(const int &state);
			int getSetCondState();
			void ImGui(const std::string &name);
		private:
			int value;
		};
	}

}