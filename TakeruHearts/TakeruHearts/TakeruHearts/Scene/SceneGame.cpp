#include "SceneGame.h"


SceneGame::SceneGame()
{
	DrawFormatString(0, 0, 0xffffff, "Gameデストラクタ");

	physics = new TKRLib::Physics;
	player = new Player;
	m_camera = new Camera;
	m_FirstMap = new FirstMap;
	m_Mischar = new Mischar;
	m_SkyDome = new SkyDome;

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
}

void SceneGame::Init()
{
	DrawFormatString(0, 40, 0xffffff, "Game初期化");
	idm->Init();
	player->Init(physics);
	m_FirstMap->Init(physics);
	m_Mischar->Init(physics);
	m_SkyDome->Init();
}

void SceneGame::Update()
{
	TKRLib::DebugDraw::Clear();
	DrawFormatString(0, 60, 0xffffff, "Game更新");

	physics->Update();
	idm->Update();
	player->Update();
	//m_camera->Update();
	m_camera->SetTarget(player->GetPos());
	m_camera->Rotate(idm->joypad->GetRightStickX(), idm->joypad->GetRightStickY());
	m_FirstMap->Update();
	m_Mischar->Update();
	m_SkyDome->UpDate(player->GetPos());
}

void SceneGame::Draw()
{
	DrawFormatString(0, 80, 0xffffff, "Game描画");
	idm->Draw();
	player->Draw();
	m_FirstMap->Draw();
	m_Mischar->Draw();
	m_SkyDome->Draw();
	TKRLib::DebugDraw::Draw();
}

void SceneGame::End()
{
	DrawFormatString(0, 100, 0xffffff, "Game解放");
	idm->End();
	player->Final(physics);
	m_FirstMap->Final(physics);
	m_Mischar->Final(physics);
	m_SkyDome->Final();
}
