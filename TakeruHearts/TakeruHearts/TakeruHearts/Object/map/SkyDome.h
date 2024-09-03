#pragma once
#include <DxLib.h>

class SkyDome
{
public:
	SkyDome();
	~SkyDome();

	void Init();
	void Update();
	void UpdateForcusPlayer(VECTOR playerPos);
	void Draw();
	void Final();

private:
	int modelHandle;

	VECTOR position;
	VECTOR scale;

	float rotate;

};
