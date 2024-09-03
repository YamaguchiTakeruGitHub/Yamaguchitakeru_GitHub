#include "SceneBase.h"

SceneBase::SceneBase()
{
	idm = new InputDevice::InputDeviceManager();
}

SceneBase::~SceneBase()
{
	idm = nullptr;
	delete idm;
}