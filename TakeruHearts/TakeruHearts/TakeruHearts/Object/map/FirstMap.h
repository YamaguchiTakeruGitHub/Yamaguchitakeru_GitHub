#pragma once
#include "../TakeruHearts/TKRLib/Physics.h"
#include "../TakeruHearts/TKRLib/Collidable.h"

class Physics;
class Collidable;
class FirstMap : public TKRLib::Collidable
{
public:
	FirstMap();

	void Init(TKRLib::Physics* physics);
	void Final(TKRLib::Physics* physics);
	void Update();
	void Draw();

	void OnCollide(const Collidable& colider);

	int modelHandle;

};

