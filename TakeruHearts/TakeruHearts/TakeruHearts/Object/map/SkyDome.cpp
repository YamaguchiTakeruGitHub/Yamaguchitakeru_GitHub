#include "SkyDome.h"


SkyDome::SkyDome()
	: modelHandle(-1)
	, position()
	, scale()
	,rotate()
{
}

SkyDome::~SkyDome()
{
	MV1DeleteModel(modelHandle);
	
}

void SkyDome::Init()
{
	modelHandle = MV1LoadModel("../Data/Asset/model/mapSky/Skydome.mv1");
	
	position = VGet(50, 0, 0);
	scale = VGet(0.2f,0.2f,0.2f);
	rotate = 0.0f;
	//MEMO：サイズがでかすぎるのでマイナスする

}

void SkyDome::Update()
{

	rotate += 0.2f;
	if (rotate >= 359)
	{
		rotate = 0.0f;
	}

	MV1SetScale(modelHandle, scale);
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, rotate * DX_PI_F / 180.0f, 0.0f));
}

void SkyDome::UpdateForcusPlayer(VECTOR playerPos)
{
	rotate += 0.2f;
	if (rotate >= 359)
	{
		rotate = 0.0f;
	}

	MV1SetScale(modelHandle, scale);
	MV1SetPosition(modelHandle, playerPos);
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, rotate * DX_PI_F / 180.0f, 0.0f));
}

void SkyDome::Draw()
{
	SetUseZBuffer3D(false);
	MV1DrawModel(modelHandle);
	SetUseZBuffer3D(true);
}

void SkyDome::Final()
{
	MV1DeleteModel(modelHandle);
}
