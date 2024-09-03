#pragma once
#include <DxLib.h>
class Tree
{
public:
	Tree();
	~Tree();

	void Init();
	void Update();
	void Draw();
	void Final();

private:
	int modelHandle;
	VECTOR position;
	VECTOR scale;

};

