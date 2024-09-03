#pragma once
#include <DxLib.h>
class GreenGround
{
public:
	GreenGround();
	~GreenGround();
	
	void Init();
	void Update();
	void Draw();
	void Final();
	
private:
	int modelHandle;
	VECTOR position;
};

