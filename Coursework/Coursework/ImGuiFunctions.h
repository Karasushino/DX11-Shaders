#pragma once
//Header file with Static functions for extra ImGui Functionality.
class ImGuiFunctions
{
public:
	//Simple functionality to toggle on and off a boolean using a button
	static void ToggleButton(bool button, bool* boolean)
	{
		if (button)
		{
			switch (*boolean)
			{
			case true:
				*boolean = false;
				break;
			case false:
				*boolean = true;
				break;
			}
		}

	}

	//From ImGui demo cpp
	//Shows a question mark in the UI that you can hover over and a tooltip pops.
	static void QuestionmarkTooltip(const char* text)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(450.0f);
			ImGui::TextUnformatted(text);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	//Shows a red exclamation mark in the UI that you can hover over and a tooltip pops.
	static void ExclamationmarkTooltip(const char* text)
	{
		ImGui::TextColored(ImVec4(1,0,0,1),"(!)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(450.0f);
			ImGui::TextUnformatted(text);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}
};