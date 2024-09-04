#pragma once
#include <DxLib.h>
class GrassLand
{
public:
	GrassLand();
	~GrassLand();

	void Init();
	void Update();
	void Draw();
	void Final();

private:
	int modelHandle;
	VECTOR position;

};

