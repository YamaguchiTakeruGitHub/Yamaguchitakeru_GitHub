#include "FirstMap.h"
#include "../TakeruHearts//TKRLib//TKRLib.h"

FirstMap::FirstMap()
	:Collidable(Collidable::Priority::Static, GameObjectTag::SystemMap, TKRLib::ColliderData::Kind::Sphere)
{
	auto sphereColliderData = dynamic_cast<TKRLib::ColliderDataSphere*>(colliderData);
	sphereColliderData->radius = 1.0f;
}

void FirstMap::Init(TKRLib::Physics* physics)
{
	physics->Entry(this);

	modelHandle = MV1LoadModel("../Data/Asset/model/map/tutorial_model/FirstMap.mv1");

	rigidbody.Init();
	rigidbody.SetPos(VGet(0.0f, 0.0f, 0.0f));

}

void FirstMap::Final(TKRLib::Physics* physics)
{
	physics->Exit(this);
	MV1DeleteModel(modelHandle);

}

void FirstMap::Update()
{
	rigidbody.SetVelocity(VGet(0, 0, 0));

}

void FirstMap::Draw()
{
	MV1DrawModel(modelHandle);
}

void FirstMap::OnCollide(const Collidable& colider)
{
}
