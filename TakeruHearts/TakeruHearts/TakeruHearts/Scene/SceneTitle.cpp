#include "SceneTitle.h"


SceneTitle::SceneTitle()
	: imgBG					(LoadGraph("../Data/Asset/img/TitleButtonRogo.png"))
	, buttonPoint			(LoadGraph("../Data/Asset/img/buttonPoint.png"))
	, nowSelect				()
	, buttonPointPos		()
	, NewGamePos			()
	, LoadGamePos			()
	, BackPos				()
	, pushBefore			()
	, pushNow				()
	, isDUPButtonPressed	()
	,isDDOWNButtonPressed	()
{
	DrawFormatString(0, 0, 0xffffff, "title�f�X�g���N�^");
}

SceneTitle::~SceneTitle()
{
	DrawFormatString(0, 20, 0xffffff,"title�R���X�g���N�^");
	DeleteGraph(imgBG);
	DeleteGraph(buttonPoint);
}

void SceneTitle::Init()
{
	DrawFormatString(0, 40, 0xffffff, "title������");
	idm->Init();
	imgBG;
	buttonPoint;
	buttonPointPos	= VGet(124.0f, 486.0f, 0.0f);
	NewGamePos		= VGet(124.0f, 486.0f, 0.0f);
	LoadGamePos		= VGet(124.0f, 553.0f, 0.0f);
	BackPos			= VGet(124.0f, 621.0f, 0.0f);

	nowSelect = eMenu_LoadGame;

	pushBefore = 0;
	pushNow = 0;
	isDUPButtonPressed = false;
	isDDOWNButtonPressed = false;
}

void SceneTitle::Update()
{
	DrawFormatString(0, 60, 0xffffff, "title�X�V");
	idm->Update();

	

	//�オ�����ꂽ�u��
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
	//���������ꂽ�u��
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



	//�I���������ڂ�A�{�^���Ŏ��s
	if (idm->joypad->isA == true)
	{
		switch (nowSelect)
		{
		case eMenu_NewGame:
			
			break;

		case eMenu_LoadGame:
			break;
		
		case eMenu_Back:
			DxLib_End();
			break;
		}
	}
	
	//�I�����ꂽ���ڂ̍��W���i�[
	switch (nowSelect)
	{
	case eMenu_NewGame:
		buttonPointPos.y = NewGamePos.y;
		break;
	case eMenu_LoadGame:
		buttonPointPos.y = LoadGamePos.y;
		break;
	case eMenu_Back:
		buttonPointPos.y = BackPos.y;
		break;
	}

}

void SceneTitle::Draw()
{
	DrawFormatString(0, 80, 0xffffff, "title�`��");

	idm->Draw();
	DrawGraph(0,0,imgBG, true);



	DrawGraph(buttonPointPos.x, buttonPointPos.y, buttonPoint, true);




	DrawFormatString(100, 100, 0x000000, "x %f, y %f", buttonPointPos.x, buttonPointPos.y);

	switch (nowSelect)
	{
	case eMenu_NewGame:
		DrawFormatString(100, 120, 0x000000, "NewGame");
		break;
	case eMenu_LoadGame:
		DrawFormatString(100, 120, 0x000000, "LoadGame");
		break;
	case eMenu_Back:
		DrawFormatString(100, 120, 0x000000, "Back");
		break;
	}

	if (idm->joypad->isA == true)
	{
		switch (nowSelect)
		{
		case eMenu_NewGame:
			DrawFormatString(100, 120, 0x000000, "NewGame�������ꂽ��");
			break;
		case eMenu_LoadGame:
			DrawFormatString(100, 120, 0x000000, "LoadGame�������ꂽ��");
			break;
		case eMenu_Back:
			DrawFormatString(100, 120, 0x000000, "Back�������ꂽ��");
			break;
		}
	}

	
}

void SceneTitle::End()
{
	DrawFormatString(0, 100, 0xffffff, "title���");
	idm->End();
	DeleteGraph(imgBG);
	DeleteGraph(buttonPoint);
}


