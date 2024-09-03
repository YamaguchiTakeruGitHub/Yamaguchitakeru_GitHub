#include "Player.h"
#include "../TakeruHearts/TKRLib/TKRLib.h"
#include <string>



Player::Player()
	: Collidable(Collidable::Priority::High, GameObjectTag::Player, TKRLib::ColliderData::Kind::Sphere)
	, isMove()
{
	idm = new InputDevice::InputDeviceManager();
	m_camera = new Camera();
	auto sphereColliderData = dynamic_cast<TKRLib::ColliderDataSphere*>(colliderData);
	sphereColliderData->radius = 1.0f;
}

void Player::Init(TKRLib::Physics* physics)
{
	idm->Init();
	m_camera->Init(rigidbody.GetPos());
	physics->Entry(this);

	modelHandle = MV1LoadModel("../Data/Asset/model/Character/Player/Knight.mv1");
	
	rigidbody.Init();
	rigidbody.SetPos(VGet(0.0f, 0.0f, 100.0f));

	speed = 0.1f;

	isMove = false;

}

void Player::Final(TKRLib::Physics* physics)
{
	
	physics->Exit(this);
	MV1DeleteModel(modelHandle);
	idm->End();
	

	idm = nullptr;
	delete idm;

	m_camera = nullptr;
	delete m_camera;

}

void Player::Update()
{
	// 標準ライトの方向をＸ軸のプラス方向にする
	SetLightDirection(VGet(0.0f, 5.0f, 0.0f));

	idm->Update();

	float leftSticX = idm->joypad->GetLeftStickX();
	float leftSticY = idm->joypad->GetLeftStickY();


	VECTOR dir = VGet(0.0f, 0.0f, 0.0f);
	
	dir.x = 0;
	dir.y = 0;
	dir.z = 0;

	if (leftSticX != 0 && leftSticX <= 0.030519f && leftSticX >= 0.0f)
	{
		dir.x = 1;
	}
	if (leftSticX != 0 && leftSticX >= -0.030519f && leftSticX <= 0.0f)
	{
		dir.x = -1;
	}
	if (leftSticY != 0 && leftSticY <= 0.030519f && leftSticY >= 0.0f)
	{
		dir.z = -1;
	}
	if (leftSticY != 0 && leftSticY >= -0.030519f && leftSticY <= 0.0f)
	{
		dir.z = 1;
	}

	MATRIX cameraRotation = MGetRotY(m_camera->GetCameraHAngle());

	dir = VTransform(dir, cameraRotation);
	
	if (VSquareSize(dir) > 0)
	{
		VECTOR normalizedDir = VNorm(dir);
		float angle = atan2f(normalizedDir.x, normalizedDir.z);

		MV1SetRotationXYZ(modelHandle, VGet(0.0f, angle / 2.0f, 0.0f));
	}



	if (VSquareSize(dir) > 0)
	{
		dir = VNorm(dir);
	}

	rigidbody.SetVelocity(VScale(dir, speed));

	// 物理的な位置を取得
	VECTOR newPos = VAdd(rigidbody.GetPos(), rigidbody.GetVelocity());
	rigidbody.SetPos(newPos);

	// モデルの描画位置を更新
	MV1SetPosition(modelHandle, newPos);

#if _DEBUG
	DrawFormatString(100, 100, 0xffffff, "Left Stick X: %f, Y: %f", leftSticX, leftSticY);
	#endif

}
	

void Player::Draw()
{
	idm->Draw();
	MV1DrawModel(modelHandle);
	//DrawSphere3D(VGet(0.0f,0.0f,0.0f), 10.0f, 32, 0xffffff, 0xffffff, true);
	
#if _DEBUG
	DrawFormatString(400, 420, 0xffffff, "x%f y%f z%f", rigidbody.GetPos().x, rigidbody.GetPos().y, rigidbody.GetPos().z);
#endif

}

void Player::OnCollide(const Collidable& colider)
{
	std::string message = "プレイヤーが";
	if (colider.GetTag() == GameObjectTag::Player)
	{
		message += "プレイヤー";
	}
	else if (colider.GetTag() == GameObjectTag::Enemy)
	{
		message += "敵";
	}
	message += "と当たった！\n";
	printfDx(message.c_str());
}