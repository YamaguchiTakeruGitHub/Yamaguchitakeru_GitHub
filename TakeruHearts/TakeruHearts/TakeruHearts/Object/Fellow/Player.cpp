#include "Player.h"
#include "../TKRLib/TKRLib.h"
#include <string>

Player::Player()
	: Collidable(Collidable::Priority::High, GameObjectTag::Player, TKRLib::ColliderData::Kind::Sphere)
	, speed()
{
	idm = new InputDevice::InputDeviceManager();
	auto sphereColliderData = dynamic_cast<TKRLib::ColliderDataSphere*>(colliderData);
	sphereColliderData->radius = 1.0f;
}

void Player::Init(TKRLib::Physics* physics)
{
	idm->Init();
	
	physics->Entry(this);

	modelHandle = MV1LoadModel("../Data/Asset/model/Character/Player/Knight.mv1");

	rigidbody.Init();
	rigidbody.SetPos(VGet(0.0f, 0.0f, 100.0f));
	speed = 2.0f;
}

void Player::Final(TKRLib::Physics* physics)
{
	physics->Exit(this);
	MV1DeleteModel(modelHandle);
	idm->End();


	idm = nullptr;
	delete idm;


}

void Player::Update()
{
	//入力デバイスの更新
	idm->Update();

	//左スティックの召喚
	float leftSticX = idm->joypad->GetLeftStickX();
	float leftSticY = idm->joypad->GetLeftStickY();
		
	//向きの設定
	VECTOR dir = VGet(0.0f, 0.0f, 0.0f);
	
	//方向が常にほかに向かないように真ん中に戻す
	dir.x = 0.0f;
	dir.y = 0.0f;
	dir.z = 0.0f;

	//入力したらどうなるか
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

	//方向がゼロより多い場合
	if (VSquareSize(dir) > 0)
	{
		//方向をノーマライズする
		dir = VNorm(dir);
	}

	//方向と量(speed)をスケーリングし速度に変換
	rigidbody.SetVelocity(VScale(dir, speed));
	
	//現在の位置と速度を足して次の位置に移動
	VECTOR newPos = VAdd(rigidbody.GetPos(), rigidbody.GetVelocity());

	//位置のセット
	rigidbody.SetPos(newPos);

	// モデルの描画位置を更新
	MV1SetPosition(modelHandle, newPos);

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
