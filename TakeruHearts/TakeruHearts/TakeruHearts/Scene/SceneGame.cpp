#include "SceneGame.h"


SceneGame::SceneGame()
	: deltaTime()
{
	DrawFormatString(0, 0, 0xffffff, "Gameデストラクタ");

	physics = new TKRLib::Physics;
	player = new Player;
	m_camera = new Camera;
	m_FirstMap = new FirstMap;
	m_Mischar = new Mischar;
	m_SkyDome = new SkyDome;
	m_Tree = new Tree;
	m_GrassLand = new GrassLand;
	m_Light = new Light::Light;
	m_UiCommand = new UI::UICommand;
}

SceneGame::~SceneGame()
{
	DrawFormatString(0, 20, 0xffffff, "Gameコンストラクタ");
	physics = nullptr;
	delete(physics);
	player = nullptr;
	delete(physics);
	m_camera = nullptr;
	delete(m_camera);
	m_FirstMap = nullptr;
	delete(m_FirstMap);
	m_Mischar = nullptr;
	delete(m_Mischar);
	m_SkyDome = nullptr;
	delete(m_SkyDome);
	m_Tree = nullptr;
	delete(m_Tree);
	m_GrassLand = nullptr;
	delete(m_GrassLand);
	m_Light = nullptr;
	delete(m_Light);
	m_UiCommand = nullptr;
	delete(m_UiCommand);
}

void SceneGame::Init()
{
	DrawFormatString(0, 40, 0xffffff, "Game初期化");

	deltaTime = 2.0f;

	idm->Init();
	player->Init(physics);
	m_camera->Init();
	m_SkyDome->Init();
	m_FirstMap->Init(physics);
	m_Mischar->Init(physics);
	m_Tree->Init();
	m_GrassLand->Init();
	m_Light->Init();
	m_UiCommand->Init();
}

void SceneGame::Update()
{
	DrawFormatString(0, 60, 0xffffff, "Game更新");

	physics->Update();

	m_SkyDome->Update();
	m_SkyDome->UpdateForcusPlayer(player->GetPos());

	idm->Update();
	player->Update(deltaTime);
	m_camera->Update(idm->joypad->GetRightStickX(), idm->joypad->GetRightStickY(), player->GetPos());
	m_FirstMap->Update();
	m_Mischar->Update();
	m_Tree->Update();
	m_GrassLand->Update();
	m_Light->Update();
	m_UiCommand->Update();
	TKRLib::DebugDraw::Clear();
}

void SceneGame::Draw()
{
	DrawFormatString(0, 80, 0xffffff, "Game描画");
	idm->Draw();

	player->Draw();
	m_FirstMap->Draw();
	m_Mischar->Draw();
	m_SkyDome->Draw();
	m_Tree->Draw();
	m_GrassLand->Draw();
	m_Light->Draw();
	m_UiCommand->Draw();
	TKRLib::DebugDraw::Draw();
}

void SceneGame::End()
{
	DrawFormatString(0, 100, 0xffffff, "Game解放");
	idm->End();
	m_SkyDome->Final();
	player->Final(physics);
	m_FirstMap->Final(physics);
	m_Mischar->Final(physics);
	m_Tree->Final();
	m_GrassLand->Final();
	m_Light->Final();
	m_UiCommand->Final();
}
