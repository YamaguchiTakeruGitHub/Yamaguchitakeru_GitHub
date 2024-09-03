#pragma once
#include "DxLib.h"
#include "../TKRLib/GameObjectTag.h"
#include "../TKRLib/ColliderData.h"
#include "../TKRLib/Rigidbody.h"


namespace TKRLib
{
	class Rigidbody;
	class Physics;
	class ColliderData;

	class Collidable abstract
	{
	public:
		enum class Priority : int
		{
			Low,
			Middle,
			High,
			Static,

		};

		Collidable(Priority priority, GameObjectTag tag, ColliderData::Kind colliderKind);
		virtual ~Collidable();
		virtual void Init(TKRLib::Physics* physics);
		virtual void Final(TKRLib::Physics* physics);

		virtual void OnCollide(const Collidable& colider) abstract;
		
		GameObjectTag GetTag() const { return tag; }
		Priority GetPriority() const { return priority; }

	protected:

		int modelHandle;
		Rigidbody rigidbody;
		ColliderData* colliderData;

	private:
		ColliderData* CreateColliderData(ColliderData::Kind kind);
		GameObjectTag tag;
		Priority priority;


		friend Physics;

		VECTOR nextPos;

	};
}

