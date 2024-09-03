#pragma once
#include "SceneBase.h"
#include "../TKRLib\TKRLib.h"
#include "../Object/Fellow/Player.h"
#include "../Camera/Camera.h"
#include "../Object/map/FirstMap.h"
#include "../Object/Enemy/Mischar.h"
#include "../Object/map/SkyDome.h"
#include "../Object/map/Tree.h"


class SceneGame final
	: public SceneBase
{
public:
	SceneGame();
	~SceneGame()override;

	void Init();
	void Update();
	void Draw();
	void End();

private:
	TKRLib::Physics* physics;
	Player* player;
	Camera* m_camera;
	FirstMap* m_FirstMap;
	Mischar* m_Mischar;
	SkyDome* m_SkyDome;
	Tree* m_Tree;
};


