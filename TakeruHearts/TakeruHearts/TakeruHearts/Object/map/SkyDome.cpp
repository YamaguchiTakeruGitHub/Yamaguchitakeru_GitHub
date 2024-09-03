#include "SkyDome.h"


SkyDome::SkyDome()
	: modelHandle(-1)
	, position()
	, scale()

	,testModelHandel(-1)
	, position2()
	, scale2()
{
}

SkyDome::~SkyDome()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(testModelHandel);
}

void SkyDome::Init()
{
	modelHandle = MV1LoadModel("../Data/Asset/model/mapSky/Skydome.mv1");
	
	position = VGet(50, 0, 0);
	scale = VGet(0.2f,0.2f,0.2f);
	


	//MEMO：サイズがでかすぎるのでマイナスする

}

void SkyDome::Update()
{
	MV1SetScale(modelHandle, scale);
	MV1SetPosition(modelHandle, position);

	
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
	MV1DeleteModel(testModelHandel);
}
