#pragma once
#include "SceneBase.h"

class SceneResult final
	:public SceneBase
{
public:
	SceneResult();
	~SceneResult() override;

	void Init();
	void Update();
	void Draw();
	void End();



};

