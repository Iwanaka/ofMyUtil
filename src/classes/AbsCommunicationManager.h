#pragma once
#include <string>
#include "ofThread.h"
#include "ofImGuiUtil.h"

namespace ofxMyUtil {
	class AbsCommunicationManager : public ofThread {

	public:

		//--------------------------------------------------------------
		void ImGui(std::string name) {

			ImGui::Begin(name.c_str());
			addPropertyImGui();
			ImGui::End();
			_log.ImGui(name);
		}

		//--------------------------------------------------------------
		ofEvent<const std::string> onReceiveNewMsg;
		ofEvent<const bool> onConnectResult;

	protected:
		virtual void addPropertyImGui() = 0;
		virtual void addProcessInThreadedFunction() = 0;

		ofxMyUtil::im::ImGuiLogWindow _log;

	private:

		//--------------------------------------------------------------
		void threadedFunction() override {
			while (isThreadRunning()) {

				if (lock()) {

					addProcessInThreadedFunction();

					sleep(10);
					unlock();
				}
			}
		}

	};
}