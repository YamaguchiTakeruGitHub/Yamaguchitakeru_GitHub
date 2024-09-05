#include "Player.h"
#include "../TKRLib/TKRLib.h"

#include <string>

Player::Player()
	: Collidable(Collidable::Priority::High, GameObjectTag::Player, TKRLib::ColliderData::Kind::Sphere)
	, speed()
	, modelRot()
	, playerHorizontalAngle()
	, playerVerticalAngle()
	, currentAnimation("Idle")
	, isMove()

{
	idm = new InputDevice::InputDeviceManager();
	auto sphereColliderData = dynamic_cast<TKRLib::ColliderDataSphere*>(colliderData);
	sphereColliderData->radius = 1.0f;
}

void Player::Init(TKRLib::Physics* physics)
{
	idm->Init();
	
	physics->Entry(this);
	
	animationManager.InitChangeAnimation("Player", modelHandle);

	modelHandle = MV1LoadModel("../Data/Asset/model/Character/Player/Knight.mv1");

	rigidbody.Init();
	rigidbody.SetPos(VGet(0.0f, 0.0f, -100.0f));
	
	speed = 0.2f;
	modelRot = 0.0f;

	playerHorizontalAngle;
	playerVerticalAngle;
}

void Player::Final(TKRLib::Physics* physics)
{
	physics->Exit(this);
	MV1DeleteModel(modelHandle);
	idm->End();


	idm = nullptr;
	delete idm;


}

void Player::Update(float deltaTime)
{
	//入力デバイスの更新
	idm->Update();

	//左スティックの召喚
	float leftSticX = idm->joypad->GetLeftStickX();
	float leftSticY = idm->joypad->GetLeftStickY();
		
	playerHorizontalAngle = leftSticX;
	playerVerticalAngle	  = leftSticY;

	//向きの設定
	VECTOR dir = VGet(0.0f, 0.0f, 0.0f);
	
	//方向が常にほかに向かないように真ん中に戻す
	dir.x = 0.0f;
	dir.y = 0.0f;
	dir.z = 0.0f;

	//移動フラグをおろす
	isMove = false;

	//入力したらどうなるか
	if (leftSticX != 0 && leftSticX <= 0.030519f && leftSticX >= 0.0f)
	{
		dir.x = -1;
		modelRot = 90.0f;
		isMove = true;
	}
	if (leftSticX != 0 && leftSticX >= -0.030519f && leftSticX <= 0.0f)
	{
		dir.x = 1;
		modelRot = 270.0f;
		isMove = true;
	}
	if (leftSticY != 0 && leftSticY <= 0.030519f && leftSticY >= 0.0f)
	{
		dir.z = 1;
		modelRot = 180.0f;
		isMove = true;
	}
	if (leftSticY != 0 && leftSticY >= -0.030519f && leftSticY <= 0.0f)
	{
		dir.z = -1;
		modelRot = 0.0f;
		isMove = true;
	}
	

	//アニメーションの設定
	if (isMove == true)
	{
		currentAnimation = "Run";
	}

	animationManager.ChangeAnimation("Player", currentAnimation);
	animationManager.Update(deltaTime);


	//方向がゼロより多い場合
	if (VSquareSize(dir) > 0)
	{
		//方向をノーマライズする
		dir = VNorm(dir);
	}

	//方向と量(speed)をスケーリングし速度に変換
	rigidbody.SetVelocity(VScale(dir, speed));
	/*
	VECTOR vectole = */

	//現在の位置と速度を足して次の位置に移動
	VECTOR newPos = VAdd(rigidbody.GetPos(), rigidbody.GetVelocity());

	//位置のセット
	rigidbody.SetPos(newPos);

	// モデルの描画位置を更新
	MV1SetPosition(modelHandle, newPos);

	MV1SetRotationXYZ(modelHandle, VGet(0.0f, modelRot * DX_PI_F / 180.0f, 0.0f));

#if _DEBUG
	if (dir.x == 1)
	{
		DrawFormatString(750, 0, 0xffffff, "向き：右");
	}
	if (dir.x == -1)
	{
		DrawFormatString(750, 0, 0xffffff, "向き：左");
	}
	if (dir.z == 1)
	{
		DrawFormatString(750, 0, 0xffffff, "向き：前");
	}
	if (dir.z == -1)
	{
		DrawFormatString(750, 0, 0xffffff, "向き：後");
	}
	DrawFormatString(750, 20, 0xffffff, "playerPos: x%f, y%f, z%f", rigidbody.GetPos().x, rigidbody.GetPos().y, rigidbody.GetPos().z);
	DrawFormatString(750, 40, 0xffffff, "pHAngle:%f, pVAngle:%f", playerHorizontalAngle, playerVerticalAngle);


#endif

}

void Player::Draw()
{
	idm->Draw();
	MV1DrawModel(modelHandle);

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
