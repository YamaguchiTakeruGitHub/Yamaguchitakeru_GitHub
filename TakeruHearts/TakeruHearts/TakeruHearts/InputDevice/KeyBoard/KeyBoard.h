#pragma once
#include <memory>
#include <DxLib.h>

namespace InputDevice
{

	class KeyBoard
	{
	public:
		KeyBoard();
		~KeyBoard();

		void Init();
		void Update();
	};
}
