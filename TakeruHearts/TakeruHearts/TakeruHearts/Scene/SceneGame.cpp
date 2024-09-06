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
	m_GreenGround = new GreenGround;
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
	m_GreenGround = nullptr;
	delete(m_GreenGround);
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
	m_GreenGround->Init(physics);
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
	m_GreenGround->Update();
	m_Light->Update();
	m_UiCommand->Update();
	TKRLib::DebugDraw::Clear();

	// プレイヤーのデバッグ描画
	TKRLib::DebugDraw::DrawSphere(player->GetPos(), 1.0f, GetColor(255, 0, 0)); // 赤い球を描画

	// GreenGroundのデバッグ描画
	auto boxColliderData = dynamic_cast<TKRLib::ColliderDataOBB*>(m_GreenGround->GetColliderData());
	if (boxColliderData)
	{
		TKRLib::DebugDraw::DrawOBB(boxColliderData->center, boxColliderData->halfSize, boxColliderData->rotation, GetColor(0, 255, 0)); // 緑のOBBを描画
	}

	TKRLib::DebugDraw::Draw();

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
	m_GreenGround->Draw();
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
	m_GreenGround->Final(physics);
	m_Light->Final();
	m_UiCommand->Final();
}
