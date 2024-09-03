#pragma once
#include "../TakeruHearts/TKRLib/Physics.h"
#include "../TakeruHearts/TKRLib/Collidable.h"
#include "../TakeruHearts/InputDevice/InputDeviceManager.h"
#include "../../Camera/Camera.h"

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
	bool isMove;
	float modelHandle;
	float speed;

	InputDevice::InputDeviceManager* idm;
	Camera* m_camera;


};

