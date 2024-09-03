#include "../TakeruHearts/TKRLib/TKRLib.h"
#include <string>
#include "Mischar.h"


Mischar::Mischar()
	: Collidable(Collidable::Priority::Low, GameObjectTag::Enemy, TKRLib::ColliderData::Kind::Sphere)
	, modelHandle(-1)
{
	auto sphereColliderData = dynamic_cast<TKRLib::ColliderDataSphere*>(colliderData);
	sphereColliderData->radius = 1.0f;
}

void Mischar::Init(TKRLib::Physics* physics)
{
	physics->Entry(this);
	modelHandle = MV1LoadModel("../Data/Asset/model/Character/Enemy/Mischar.mv1");

	rigidbody.Init();
	rigidbody.SetPos(VGet(0.0f, 0.0f, 30.0f));
}

void Mischar::Final(TKRLib::Physics* physics)
{
	physics->Exit(this);
	MV1DeleteModel(modelHandle);
}

void Mischar::Update()
{
	MV1SetPosition(modelHandle, rigidbody.GetPos());
}

void Mischar::Draw()
{
	MV1DrawModel(modelHandle);
}

void Mischar::OnCollide(const Collidable& collidder)
{
}
