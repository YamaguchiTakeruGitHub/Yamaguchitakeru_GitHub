#include<DxLib.h>
#include <../nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <cassert>
#include <memory>

#include "CommonScene.h"




//ポインタはアドレスを格納するための変数！

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


	//初期化（開始）
	//構造体のインスタンス作成
	GameConfig config;

	//LoadConfigで指定のパスが開けなかった場合は１を返す
	if (!LoadConfig("../Data/AllVariables/GameConfig.json", config))
	{
		return 1;
	}

	//ウィンドウ画面の調整
	SetGraphMode(config.screenWidth, config.screenHeight,16);
	SetWindowSize(config.screenWidth, config.screenHeight);
	
	//構造体のインスタンス作成
	SceneManager sceneManager(std::make_unique<SceneTitle>());
	sceneManager.Init();

	//初期化（終了）

	SetUseZBuffer3D(true);

	while (ProcessMessage() != 1)
	{
		LONGLONG start = GetNowHiPerformanceCount();

		ClearDrawScreen();


		//ゲーム処理（開始）

		
		sceneManager.Update();
		sceneManager.Draw();
		sceneManager.HondleInput();

		//ゲーム処理（終了）


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