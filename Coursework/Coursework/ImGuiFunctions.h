#pragma once

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