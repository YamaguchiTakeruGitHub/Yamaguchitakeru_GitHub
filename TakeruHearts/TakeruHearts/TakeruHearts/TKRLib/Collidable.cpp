#include "../TKRLib/Collidable.h"
#include <cassert>
#include "TKRLib.h"


TKRLib::Collidable::Collidable(Priority priority, GameObjectTag tag, ColliderData::Kind colliderKind)
	: priority(priority)
	, tag(tag)
	, colliderData(nullptr)
	, nextPos(VGet(0, 0, 0))
{
	CreateColliderData(colliderKind);
}

TKRLib::Collidable::~Collidable()
{
	if (colliderData != nullptr)
	{
		delete colliderData;
		colliderData = nullptr;
	}
}

void TKRLib::Collidable::Init(TKRLib::Physics* physics)
{
	physics->Entry(this);

}

void TKRLib::Collidable::Final(TKRLib::Physics* physics)
{
	physics->Exit(this);
}

TKRLib::ColliderData* TKRLib::Collidable::CreateColliderData(ColliderData::Kind kind)
{
	if (colliderData != nullptr)
	{
		assert(0 && "colliderData‚Íì‚ç‚ê‚Ä‚¢‚Ü‚·");
		return colliderData;
	}

	switch (kind)
	{
	case TKRLib::ColliderData::Kind::Sphere:
		colliderData = new ColliderDataSphere();
		break;
	case TKRLib::ColliderData::Kind::Box:
		colliderData = new ColliderDataOBB();
		break;

	default:
		break;
	}

	return colliderData;
}
