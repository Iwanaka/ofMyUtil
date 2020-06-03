#pragma once
#include <string>
#include "ofThread.h"
#include "ofImGuiUtil.h"

namespace ofxMyUtil {
	class AbsCommunicationManager : public ofThread {

	public:

		//--------------------------------------------------------------
		void ImGui(std::string name) {

			if (!ImGui::Begin(name.c_str())) {
				ImGui::End();
				return;
			}
			ImGui::PushID(name.c_str());
			addPropertyImGui();
			ImGui::PopID();
			ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing(); ImGui::Spacing(); ImGui::Spacing();


			ImGui::End();
			mLogGui.ImGui(name);
		}

		//--------------------------------------------------------------
		ofEvent<const std::string> onReceiveNewMsg;
		ofEvent<const bool> onConnectResult;

	protected:
		virtual void addPropertyImGui() = 0;
		virtual void addProcessInThreadedFunction() = 0;

		ofxMyUtil::im::ImGuiLogWindow mLogGui;

	private:

		//--------------------------------------------------------------
		void threadedFunction() override 
		{
			while (isThreadRunning()) 
			{
				if (lock()) 
				{
					addProcessInThreadedFunction();

					sleep(10);
					unlock();
				}
			}
		}

	};
}