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
	m_Tree = new Tree;

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
}

void SceneGame::Init()
{
	DrawFormatString(0, 40, 0xffffff, "Game初期化");

	idm->Init();
	player->Init(physics);
	m_SkyDome->Init();
	m_FirstMap->Init(physics);
	m_Mischar->Init(physics);
	m_Tree->Init();
}

void SceneGame::Update()
{
	TKRLib::DebugDraw::Clear();
	DrawFormatString(0, 60, 0xffffff, "Game更新");

	physics->Update();

	m_SkyDome->Update();

	idm->Update();
	player->Update();
	//m_camera->Update();
	m_camera->SetTarget(player->GetPos());
	m_camera->Rotate(idm->joypad->GetRightStickX(), idm->joypad->GetRightStickY());
	m_FirstMap->Update();
	m_Mischar->Update();
	m_Tree->Update();
}

void SceneGame::Draw()
{
	DrawFormatString(0, 80, 0xffffff, "Game描画");
	TKRLib::DebugDraw::Draw();
	idm->Draw();

	player->Draw();
	m_FirstMap->Draw();
	m_Mischar->Draw();
	m_SkyDome->Draw();
	m_Tree->Draw();
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
}
