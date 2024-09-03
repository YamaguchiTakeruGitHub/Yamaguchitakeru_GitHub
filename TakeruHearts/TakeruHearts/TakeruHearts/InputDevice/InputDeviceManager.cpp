#include "InputDeviceManager.h"
#include "Pad/JoyPad.h"

using namespace InputDevice;

InputDeviceManager::InputDeviceManager()
{
	joypad = new JoyPad;
	//keyboard = new KeyBoard;
}

InputDeviceManager::~InputDeviceManager()
{
	joypad = nullptr;
	delete joypad;

	//keyboard = nullptr;
	//delete keyboard;
}

void InputDeviceManager::Init()
{
	joypad->Init();
	//keyboard->Init();
}

void InputDeviceManager::Update()
{
	joypad->Update();
	//keyboard->Update();
}

void InputDevice::InputDeviceManager::Draw()
{
	joypad->Draw();
}

void InputDeviceManager::End()
{
	joypad = nullptr;
	delete joypad;

	//keyboard = nullptr;
	//delete keyboard;
}
