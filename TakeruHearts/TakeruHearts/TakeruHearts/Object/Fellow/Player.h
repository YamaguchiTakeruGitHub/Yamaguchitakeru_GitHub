#pragma once
#include "../TKRLib/Physics.h"
#include "../TKRLib/Collidable.h"
#include "../InputDevice/InputDeviceManager.h"
#include "../Animation/AnimationManager.h"


class AnimationManager;
class Physics;
class Collidable;
class Player : public TKRLib::Collidable
{
public:
	Player();

	void Init(TKRLib::Physics* physics);
	void Final(TKRLib::Physics* physics);
	void Update(float deltaTime);
	void Draw();

	//衝突したとき
	void OnCollide(const Collidable& colider) override;
	//プレイヤーのポジション
	const VECTOR& GetPos() const { return rigidbody.GetPos(); }

private:

	float playerHorizontalAngle;
	float playerVerticalAngle;

	float speed;
	float modelRot;

	bool isMove;

	InputDevice::InputDeviceManager* idm;

	AnimationManager animationManager;
	std::string currentAnimation;
};
