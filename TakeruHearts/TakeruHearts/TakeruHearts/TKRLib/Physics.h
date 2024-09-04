#pragma once
#include "../TKRLib/TKRLib.h"
#include <list>
#include <vector>

namespace TKRLib
{
	class Collidable;

	class Physics final
	{
	public:
		void Entry(Collidable* collidable);
		void Exit(Collidable* collidable);

		void Update();

	private:

		static const int BeforeFixInfoColor = 0x0000ff;
		static const int AimInfoColor = 0x0000aa;
		static const int AfterFixInfoColor = 0xff00ff;

		//float sibakyori;

		std::list<Collidable*> collidables;

		struct OnCollideInfo
		{
			Collidable* owner;
			Collidable* colider;
			void OnCollide() { owner->OnCollide(*colider); }
		};

		std::vector<OnCollideInfo> CheckColide() const;
		bool IsCollide(const Collidable* objA, const Collidable* objB)const;

		void FixNextPosition(Collidable* primary, Collidable* secondary)const;
		void FixPosition();

		//bool CheckOBBCollision3D(const Box& a, const )
		
	};
}
