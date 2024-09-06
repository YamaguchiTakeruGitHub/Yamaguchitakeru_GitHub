#include "GreenGround.h"
#include "../TakeruHearts/TKRLib/TKRLib.h"
#include <string>

GreenGround::GreenGround()
	: Collidable(Collidable::Priority::Static, GameObjectTag::SystemGround, TKRLib::ColliderData::Kind::Box)
	, modelHandle(-1)
	, position(VGet(0.0f, -20.0f, 150.0f))
{

	auto boxColliderData = dynamic_cast<TKRLib::ColliderDataOBB*>(colliderData);
	if(boxColliderData)
	{ 
		boxColliderData->center = position;

		boxColliderData->halfSize = { 2.0f, 2.0f, 2.0f };
		boxColliderData->rotation = CreateIdentityMatrix();
	}
	else
	{
		// キャストに失敗した場合のエラーハンドリング
		printfDx("Error: colliderData is not of type ColliderDataOBB\n");
	}

}

void GreenGround::Init(TKRLib::Physics* physics)
{
	physics->Entry(this);
	rigidbody.Init();
	rigidbody.SetPos(position);

	modelHandle = MV1LoadModel("../Data/Asset/model/map/tutorial_model/FirstMap.mv1");
	if (modelHandle == -1)
	{
		// モデルのロードに失敗した場合のエラーハンドリング
		printfDx("Error: Failed to load model\n");
	}
}

void GreenGround::Final(TKRLib::Physics* physics)
{
	physics->Exit(this);
	MV1DeleteModel(modelHandle);
}

void GreenGround::Update()
{
	MV1SetPosition(modelHandle, rigidbody.GetPos());

	
}

void GreenGround::Draw()
{
	//MV1DrawModel(modelHandle);

}

void GreenGround::OnCollide(const Collidable& colider)
{
	std::string message = "システムグラウンドが";
	if (colider.GetTag() == GameObjectTag::SystemGround)
	{
		message += "システムグラウンド";
	}
	else
	if (colider.GetTag() == GameObjectTag::Player)
	{
		message += "プレイヤー";
	}
	else if (colider.GetTag() == GameObjectTag::Enemy)
	{
		message += "敵";
	}
	message += "と当たった！\n";
	printfDx(message.c_str());
}

TKRLib::ColliderData* GreenGround::GetColliderData() const
{
	return colliderData;
}

MATRIX GreenGround::CreateIdentityMatrix()
{
	MATRIX mat = {};
	mat.m[0][0] = 1.0f; mat.m[0][1] = 0.0f; mat.m[0][2] = 0.0f; mat.m[0][3] = 0.0f;
	mat.m[1][0] = 0.0f; mat.m[1][1] = 1.0f; mat.m[1][2] = 0.0f; mat.m[1][3] = 0.0f;
	mat.m[2][0] = 0.0f; mat.m[2][1] = 0.0f; mat.m[2][2] = 1.0f; mat.m[2][3] = 0.0f;
	mat.m[3][0] = 0.0f; mat.m[3][1] = 0.0f; mat.m[3][2] = 0.0f; mat.m[3][3] = 1.0f;
	return mat;
}

