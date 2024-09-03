#include "SkyDome.h"

SkyDome::SkyDome()
	: modelHandle(-1)
	, position	 ()
	, scale		 ()
{
	
}

SkyDome::~SkyDome()
{
	MV1DeleteModel(modelHandle);
}

void SkyDome::Init()
{
	modelHandle = MV1LoadModel("../Data/Asset/model/mapSky/Skydome.mv1");
	position = VGet(0, 0, 0);
	scale = 0.0f;
}

void SkyDome::UpDate(const VECTOR& playerPosition)
{
	position = playerPosition;
	MV1SetPosition(modelHandle, position);
}

void SkyDome::Draw()
{
	MV1SetScale(modelHandle, VGet(scale, scale, scale));
	MV1DrawModel(modelHandle);

#if _DEBUG
	DrawFormatString(300, 200, 0xffffff, "skyDome :x%f,y%f,z%f", position.x, position.y, position.z);
#endif
}

void SkyDome::Final()
{
	MV1DeleteModel(modelHandle);
}
