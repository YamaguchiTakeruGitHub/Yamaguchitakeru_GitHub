#include "GreenGround.h"
#include "../TakeruHearts/TKRLib/TKRLib.h"
#include <string>

Ground::GreenGround::GreenGround()
	:Collidable(Collidable::Priority::Static, GameObjectTag::SystemGround, TKRLib::ColliderData::Kind::Box)
{

}

void Ground::GreenGround::Init(TKRLib::Physics* physics)
{
}

void Ground::GreenGround::Final(TKRLib::Physics* physics)
{
}

void Ground::GreenGround::Update()
{
}

void Ground::GreenGround::Draw()
{
}

void Ground::GreenGround::OnCollide(const Collidable& collider)
{
}
