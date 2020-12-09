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
};