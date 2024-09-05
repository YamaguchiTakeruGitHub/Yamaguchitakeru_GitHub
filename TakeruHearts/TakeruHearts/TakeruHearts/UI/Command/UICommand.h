#pragma once
#include "DxLib.h"
#include "../InputDevice/InputDeviceManager.h"

namespace UI
{
	class UICommand
	{
	public:
		UICommand();
		~UICommand();

		void Init();
		void Update();
		void Draw();
		void Final();

	private:
		InputDevice::InputDeviceManager* idm;

		//���ݑI�����Ă��鍀��
		int nowSelect;

		//��L�[�����Ă��邩
		bool isDUPButtonPressed;

		//���L�[�����Ă��邩
		bool isDDOWNButtonPressed;

		//���݉����Ă���
		int pushNow;

		//���݂̃o�b�t�@
		int pushBefore;

		int buttonPoint;

		VECTOR buttonPointPos;

		typedef enum
		{
			eMenu_Attack,
			eMenu_Magic,
			eMenu_Item,
			eMenu_Menu,

			eMenu_Num,

		}eMenu;

	private:
		
		int commandGraphHandle;
		int attackGraphHandle;
		int magicGraphHandle;
		int itemGraphHandle;
		int menuGraphHandle;

		int s_AttackGraphHandle;
		int s_MagicGraphHandle;
		int s_ItemGraphHandle;
		int s_MenuGraphHandle;

		VECTOR commandGPos;
		VECTOR attackGPos;
		VECTOR magicGPos;
		VECTOR itemGPos;
		VECTOR menuGPos;

		VECTOR s_AttackGPos;
		VECTOR s_MagicGPos;
		VECTOR s_ItemGPos;
		VECTOR s_MenuGPos;

	};
}

