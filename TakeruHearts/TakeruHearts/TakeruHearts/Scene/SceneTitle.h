#pragma once
#include "SceneManager.h"
#include "SceneBase.h"

class SceneTitle final
	: public SceneBase
{
public:
	SceneTitle();
	~SceneTitle() override;

	void Init() override;
	void Update() override;
	void Draw() override;
	void End() override;

private:


	int imgBG;

	int nowSelect;
	bool isDUPButtonPressed;
	bool isDDOWNButtonPressed;


	int buttonPoint;

	VECTOR buttonPointPos;

	VECTOR NewGamePos;
	VECTOR LoadGamePos;
	VECTOR BackPos;

	int pushNow;
	int pushBefore;



	typedef enum
	{
		eMenu_NewGame,
		eMenu_LoadGame,
		eMenu_Back,

		eMenu_Num,

	}eMenu;



};
