#pragma once
#include "DxLib.h"

class SkyDome
{
public:
	SkyDome();
	~SkyDome();
	void Init();
	void UpDate(const VECTOR& playerPosition);
	void Draw();
	void Final();

private:
	int modelHandle;
	VECTOR position;
	float scale;


};

