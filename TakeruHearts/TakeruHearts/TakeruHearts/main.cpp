#include<DxLib.h>
#include <../nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <cassert>
#include <memory>

#include "CommonScene.h"




//�|�C���^�̓A�h���X���i�[���邽�߂̕ϐ��I

struct GameConfig
{
	std::uint16_t screenWidth;
	std::uint16_t screenHeight;
	int masterSound;
};


bool LoadConfig(const std::string& filename, GameConfig& config)
{
	std::ifstream padfile(filename,std::ios::binary);

	if (!padfile.is_open())
	{
		return false;
	}

	nlohmann::json jsonData;

	padfile >> jsonData;

	config.screenHeight = jsonData["screenHeight"];
	config.screenWidth = jsonData["screenWidth"];

	padfile.close();

	return true;
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetWindowText("TakeruHearts");

	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		return -1;
	}
	
	SetDrawScreen(DX_SCREEN_BACK);


	//�������i�J�n�j
	//�\���̂̃C���X�^���X�쐬
	GameConfig config;

	//LoadConfig�Ŏw��̃p�X���J���Ȃ������ꍇ�͂P��Ԃ�
	if (!LoadConfig("../Data/AllVariables/GameConfig.json", config))
	{
		return 1;
	}

	//�E�B���h�E��ʂ̒���
	SetGraphMode(config.screenWidth, config.screenHeight,16);
	SetWindowSize(config.screenWidth, config.screenHeight);
	
	//�\���̂̃C���X�^���X�쐬
	SceneManager sceneManager(std::make_unique<SceneTitle>());
	sceneManager.Init();

	//�������i�I���j

	SetUseZBuffer3D(true);

	while (ProcessMessage() != 1)
	{
		LONGLONG start = GetNowHiPerformanceCount();

		ClearDrawScreen();


		//�Q�[�������i�J�n�j

		
		sceneManager.Update();
		sceneManager.Draw();
		sceneManager.HondleInput();

		//�Q�[�������i�I���j


		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
		{
			break;
		}

		while (GetNowHiPerformanceCount() - start < 16667)
		{

		}
	}

	sceneManager.End();

	DxLib_End();

	return 0;
};