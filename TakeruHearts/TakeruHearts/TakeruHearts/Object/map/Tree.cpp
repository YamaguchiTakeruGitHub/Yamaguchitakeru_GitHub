#include "Tree.h"

Tree::Tree()
	: modelHandle(-1)
	, position()
	, scale()
{
}

Tree::~Tree()
{
	MV1DeleteModel(modelHandle);
}

void Tree::Init()
{
	modelHandle = MV1LoadModel("../Data/Asset/model/mapTree/treeMap.mv1");
	position = VGet(0.0f, 0.0f, 0.0f);
	//scale = VGet(-20.0f, -20.0f, -20.0f);
}

void Tree::Update()
{
	MV1SetPosition(modelHandle, position);
	//MV1SetScale(modelHandle, scale);
}

void Tree::Draw()
{
	MV1DrawModel(modelHandle);
}

void Tree::Final()
{
	MV1DeleteModel(modelHandle);
}
