#include "Rigidbody.h"

TKRLib::Rigidbody::Rigidbody()
	: position(VGet(0, 0, 0))
	, direction(VGet(0, 0, 0))
	, velocity(VGet(0, 0, 0))
{
}

void TKRLib::Rigidbody::Init()
{
	position = VGet(0, 0, 0);
	direction = VGet(0, 0, 0);
	velocity = VGet(0, 0, 0);
}

void TKRLib::Rigidbody::SetVelocity(const VECTOR& set)
{
	velocity = set;
	if (VSquareSize(velocity) > 0)
	{
		direction = VNorm(velocity);
	}

}
