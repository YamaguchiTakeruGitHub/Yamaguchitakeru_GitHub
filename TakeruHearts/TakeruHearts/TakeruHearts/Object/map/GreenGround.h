#pragma once
#include <DxLib.h>
#include "../TakeruHearts/TKRLib/Physics.h"
#include "../TakeruHearts/TKRLib/Collidable.h"

namespace Ground
{
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

		void OnCollide(const Collidable& collider) override;
		const VECTOR& GetPos() const { return rigidbody.GetPos(); }
		
	private:

	};
}

