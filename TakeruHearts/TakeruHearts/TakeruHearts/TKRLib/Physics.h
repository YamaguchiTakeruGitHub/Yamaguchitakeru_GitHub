#pragma once
#include "../TKRLib/TKRLib.h"
#include <list>
#include <vector>
#include <cmath>
namespace TKRLib
{
	class Collidable;

	class Physics final
	{
	public:
		void Entry(Collidable* collidable);
		void Exit(Collidable* collidable);

		void Update();

		// èdóÕÇ∆ç≈ëÂèdóÕâ¡ë¨ìx
		static constexpr float Gravity = -0.01f;
		static constexpr float MaxGravityAccel = -0.15f;

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

		bool CheckOBBOverlap(const ColliderDataOBB* obbA, const ColliderDataOBB* obbB)const;

		bool IsAxisOverlap(const ColliderDataOBB* obbA, const ColliderDataOBB* obbB, const VECTOR& axis)const;

		bool CheckOBBSphereCollision(const ColliderDataOBB* obb, const VECTOR& obbPos, const ColliderDataSphere* sphere, const VECTOR& spherePos) const;

		VECTOR VAbs(const VECTOR& v) { return VGet(std::abs(v.x), std::abs(v.y), std::abs(v.z)); }
	};
}
