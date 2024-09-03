#pragma once
#include "../TakeruHearts/TKRLib/Collidable.h"

class Physics;
class Collidable;
class Mischar : public TKRLib::Collidable
{
public:
	Mischar();


	void Init(TKRLib::Physics* physics);
	void Final(TKRLib::Physics* physics);
	void Update();
	void Draw();

	void OnCollide(const Collidable& collidder) override;

private:
	int modelHandle;

};

