#include "GrassLand.h"


GrassLand::GrassLand()
	: modelHandle(-1)
	, position()
{
}

GrassLand::~GrassLand()
{
	MV1DeleteModel(modelHandle);
}

void GrassLand::Init()
{
	modelHandle = MV1LoadModel("../Data/Asset/model/mapGrassLand/Test_1_GrassGround.mv1");
	position = VGet(0.0f, -20.0f, 0.0f);
}

void GrassLand::Update()
{
	MV1SetPosition(modelHandle, position);
}

void GrassLand::Draw()
{
	MV1DrawModel(modelHandle);
}

void GrassLand::Final()
{
	MV1DeleteModel(modelHandle);
}
