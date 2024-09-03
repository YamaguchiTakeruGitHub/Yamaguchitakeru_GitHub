#pragma once
#include <DxLib.h>
#include "../InputDevice/InputDeviceManager.h"

	class SceneBase abstract
	{
	public:
		SceneBase() ;
		virtual ~SceneBase();

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void End() = 0;


	protected:
		InputDevice::InputDeviceManager* idm;


	};

