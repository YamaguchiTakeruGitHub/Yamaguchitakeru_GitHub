#include "UICommand.h"


UI::UICommand::UICommand()

	: commandGraphHandle	()
	, attackGraphHandle		()
	, magicGraphHandle		()
	, itemGraphHandle		()
	, menuGraphHandle		()

	, s_AttackGraphHandle	()
	, s_MagicGraphHandle	()
	, s_ItemGraphHandle		()
	, s_MenuGraphHandle		()

	, commandGPos			()
	, attackGPos			()
	, magicGPos				()
	, itemGPos				()
	, menuGPos				()

	, s_AttackGPos			()
	, s_MagicGPos			()
	, s_ItemGPos			()
	, s_MenuGPos			()

	, buttonPoint			()
	, buttonPointPos		()
	, nowSelect				()
	, pushBefore			()
	, pushNow				()
	, isDDOWNButtonPressed	()
	, isDUPButtonPressed	()
{
	idm = new InputDevice::InputDeviceManager();
}

UI::UICommand::~UICommand()
{
	

	idm = nullptr;
	delete idm;

	MV1DeleteModel(commandGraphHandle);
	MV1DeleteModel(attackGraphHandle);
	MV1DeleteModel(magicGraphHandle);
	MV1DeleteModel(itemGraphHandle);
	MV1DeleteModel(menuGraphHandle);
	MV1DeleteModel(s_AttackGraphHandle);
	MV1DeleteModel(s_MagicGraphHandle);
	MV1DeleteModel(s_ItemGraphHandle);
	MV1DeleteModel(s_MenuGraphHandle);
}


void UI::UICommand::Init()
{
	idm->Init();

	commandGraphHandle = LoadGraph("../Data/Asset/img/UI_Comand.png");
	attackGraphHandle = LoadGraph("../Data/Asset/img/UI_Attack.png");
	magicGraphHandle = LoadGraph("../Data/Asset/img/UI_Majick.png");
	itemGraphHandle = LoadGraph("../Data/Asset/img/UI_Item.png");
	menuGraphHandle = LoadGraph("../Data/Asset/img/UI_Menu.png");

	
	s_AttackGraphHandle = LoadGraph("../Data/Asset/img/UI_S_Attack.png");
	s_MagicGraphHandle = LoadGraph("../Data/Asset/img/UI_S_Majick.png");
	s_ItemGraphHandle = LoadGraph("../Data/Asset/img/UI_S_Item.png");
	s_MenuGraphHandle = LoadGraph("../Data/Asset/img/UI_S_Menu.png");

	commandGPos = VGet(0.0f, 468.0f, 0.0f);
	attackGPos = VGet(0.0f, 514.0f, 0.0f);
	magicGPos = VGet(0.0f, 560.0f, 0.0f);
	itemGPos = VGet(0.0f, 607.0f, 0.0f);
	menuGPos = VGet(0.0f, 653.0f, 0.0f);

	s_AttackGPos = VGet(15.0f, 514.0f, 0.0f);
	s_MagicGPos = VGet(15.0f, 560.0f, 0.0f);
	s_ItemGPos = VGet(15.0f, 607.0f, 0.0f);
	s_MenuGPos = VGet(15.0f, 653.0f, 0.0f);

	buttonPoint;
	buttonPointPos;
	nowSelect;
	pushBefore;
	pushNow;

}

void UI::UICommand::Update()
{
	idm->Update();

	//ã‚ª‰Ÿ‚³‚ê‚½uŠÔ
	if (idm->joypad->isDUP == true && !isDUPButtonPressed)
	{
		isDUPButtonPressed = true;

		nowSelect = (nowSelect + (eMenu_Num - 1)) % eMenu_Num;
		pushNow = 1;
	}
	if (!idm->joypad->isDUP)
	{
		isDUPButtonPressed = false;
	}
	//‰º‚ª‰Ÿ‚³‚ê‚½uŠÔ
	if (idm->joypad->isDDOWN == true && !isDDOWNButtonPressed)
	{
		isDDOWNButtonPressed = true;

		nowSelect = (nowSelect + 1) % eMenu_Num;
		pushNow = 1;
	}
	if (!idm->joypad->isDDOWN)
	{
		isDDOWNButtonPressed = false;
	}

	//‘I‘ð‚µ‚½€–Ú‚ðAƒ{ƒ^ƒ“‚ÅŽÀs
	if (idm->joypad->isA == true)
	{
		switch (nowSelect)
		{
		case eMenu_Attack:
			
			break;

		case eMenu_Magic:
			break;

		case eMenu_Item:
			break;

		case eMenu_Menu:
			DxLib_End();
			break;

		}
	}



	//‘I‘ð‚³‚ê‚½€–Ú‚ÌÀ•W‚ðŠi”[
	switch (nowSelect)
	{
	case eMenu_Attack:
		buttonPointPos.y = attackGPos.y;
		break;
	case eMenu_Magic:
		buttonPointPos.y = magicGPos.y;
		break;
	case eMenu_Item:
		buttonPointPos.y = itemGPos.y;
		break;
	case eMenu_Menu:
		buttonPointPos.y = menuGPos.y;
		break;
	}

}

void UI::UICommand::Draw()
{
	idm->Draw();

	//‘I‘ð‚³‚ê‚½€–Ú‚ðŠi”[
	switch (nowSelect)
	{
	case eMenu_Attack:
		DrawGraph(s_AttackGPos.x, s_AttackGPos.y, s_AttackGraphHandle, true);
		break;
	case eMenu_Magic:
		DrawGraph(s_MagicGPos.x, s_MagicGPos.y, s_MagicGraphHandle, true);
		break;
	case eMenu_Item:
		DrawGraph(s_ItemGPos.x, s_ItemGPos.y, s_ItemGraphHandle, true);
		break;
	case eMenu_Menu:
		DrawGraph(s_MenuGPos.x, s_MenuGPos.y, s_MenuGraphHandle, true);
		break;
	}
	

	DrawGraph(commandGPos.x, commandGPos.y, commandGraphHandle, true);
	

	//‘I‘ð‚³‚ê‚½€–Ú‚ðŠi”[
	switch (nowSelect)
	{
	case eMenu_Attack:
		DrawGraph(magicGPos.x, magicGPos.y, magicGraphHandle, true);
		DrawGraph(itemGPos.x, itemGPos.y, itemGraphHandle, true);
		DrawGraph(menuGPos.x, menuGPos.y, menuGraphHandle, true);
		break;
	case eMenu_Magic:
		DrawGraph(attackGPos.x, attackGPos.y, attackGraphHandle, true);
		DrawGraph(itemGPos.x, itemGPos.y, itemGraphHandle, true);
		DrawGraph(menuGPos.x, menuGPos.y, menuGraphHandle, true);
		break;
	case eMenu_Item:
		DrawGraph(attackGPos.x, attackGPos.y, attackGraphHandle, true);
		DrawGraph(magicGPos.x, magicGPos.y, magicGraphHandle, true);
		DrawGraph(menuGPos.x, menuGPos.y, menuGraphHandle, true);
		break;
	case eMenu_Menu:
		DrawGraph(attackGPos.x, attackGPos.y, attackGraphHandle, true);
		DrawGraph(magicGPos.x, magicGPos.y, magicGraphHandle, true);
		DrawGraph(itemGPos.x, itemGPos.y, itemGraphHandle, true);
		break;
	}
	
	
	
	


}

void UI::UICommand::Final()
{
	idm->End();

	MV1DeleteModel(commandGraphHandle);
	MV1DeleteModel(attackGraphHandle);
	MV1DeleteModel(magicGraphHandle);
	MV1DeleteModel(itemGraphHandle);
	MV1DeleteModel(menuGraphHandle);
	MV1DeleteModel(s_AttackGraphHandle);
	MV1DeleteModel(s_MagicGraphHandle);
	MV1DeleteModel(s_ItemGraphHandle);
	MV1DeleteModel(s_MenuGraphHandle);
}
