#pragma once
#include "Pad/JoyPad.h"
#include "KeyBoard/KeyBoard.h"

namespace InputDevice
{
	class InputDeviceManager
	{
	public:
		InputDeviceManager();
		~InputDeviceManager();

		void Init();
		void Update();
		void Draw();
		void End();
		
		JoyPad* joypad;
		//KeyBoard* keyboard;

	};
}
