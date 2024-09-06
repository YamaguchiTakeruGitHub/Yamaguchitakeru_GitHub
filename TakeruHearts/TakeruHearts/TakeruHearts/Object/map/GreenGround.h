#pragma once
#include <DxLib.h>
#include "../TakeruHearts/TKRLib/Physics.h"
#include "../TakeruHearts/TKRLib/Collidable.h"


class Physics;
class Collidable;
class GreenGround : public TKRLib::Collidable
{
public:
	GreenGround();

	void Init(TKRLib::Physics* physics);
	void Final(TKRLib::Physics* physics);
	void Update();
	void Draw();

	//è’ìÀÇµÇΩÇ∆Ç´
	void OnCollide(const Collidable& colider) override;

	TKRLib::ColliderData* GetColliderData() const;
	VECTOR position;

private:
	
	MATRIX CreateIdentityMatrix();
	int modelHandle;
	
};


