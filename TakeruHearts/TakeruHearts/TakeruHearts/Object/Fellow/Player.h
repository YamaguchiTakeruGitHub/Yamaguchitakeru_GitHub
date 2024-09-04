#pragma once
#include "../TKRLib/Physics.h"
#include "../TKRLib/Collidable.h"
#include "../InputDevice/InputDeviceManager.h"

class Physics;
class Collidable;
class Player : public TKRLib::Collidable
{
public:
	Player();

	void Init(TKRLib::Physics* physics);
	void Final(TKRLib::Physics* physics);
	void Update();
	void Draw();

	//衝突したとき
	void OnCollide(const Collidable& colider) override;
	//プレイヤーのポジション
	const VECTOR& GetPos() const { return rigidbody.GetPos(); }

private:

	float speed;

	InputDevice::InputDeviceManager* idm;
};
