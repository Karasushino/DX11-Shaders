#pragma once

class ImGuiFunctions
{
public:

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
};