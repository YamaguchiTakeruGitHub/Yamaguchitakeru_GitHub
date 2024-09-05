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
	//���̓f�o�C�X�̍X�V
	idm->Update();

	//���X�e�B�b�N�̏���
	float leftSticX = idm->joypad->GetLeftStickX();
	float leftSticY = idm->joypad->GetLeftStickY();
		
	playerHorizontalAngle = leftSticX;
	playerVerticalAngle	  = leftSticY;

	//�����̐ݒ�
	VECTOR dir = VGet(0.0f, 0.0f, 0.0f);
	
	//��������ɂق��Ɍ����Ȃ��悤�ɐ^�񒆂ɖ߂�
	dir.x = 0.0f;
	dir.y = 0.0f;
	dir.z = 0.0f;

	//�ړ��t���O�����낷
	isMove = false;

	//���͂�����ǂ��Ȃ邩
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
	

	//�A�j���[�V�����̐ݒ�
	if (isMove == true)
	{
		currentAnimation = "Run";
	}

	animationManager.ChangeAnimation("Player", currentAnimation);
	animationManager.Update(deltaTime);


	//�������[����葽���ꍇ
	if (VSquareSize(dir) > 0)
	{
		//�������m�[�}���C�Y����
		dir = VNorm(dir);
	}

	//�����Ɨ�(speed)���X�P�[�����O�����x�ɕϊ�
	rigidbody.SetVelocity(VScale(dir, speed));
	/*
	VECTOR vectole = */

	//���݂̈ʒu�Ƒ��x�𑫂��Ď��̈ʒu�Ɉړ�
	VECTOR newPos = VAdd(rigidbody.GetPos(), rigidbody.GetVelocity());

	//�ʒu�̃Z�b�g
	rigidbody.SetPos(newPos);

	// ���f���̕`��ʒu���X�V
	MV1SetPosition(modelHandle, newPos);

	MV1SetRotationXYZ(modelHandle, VGet(0.0f, modelRot * DX_PI_F / 180.0f, 0.0f));

#if _DEBUG
	if (dir.x == 1)
	{
		DrawFormatString(750, 0, 0xffffff, "�����F�E");
	}
	if (dir.x == -1)
	{
		DrawFormatString(750, 0, 0xffffff, "�����F��");
	}
	if (dir.z == 1)
	{
		DrawFormatString(750, 0, 0xffffff, "�����F�O");
	}
	if (dir.z == -1)
	{
		DrawFormatString(750, 0, 0xffffff, "�����F��");
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
	std::string message = "�v���C���[��";
	if (colider.GetTag() == GameObjectTag::Player)
	{
		message += "�v���C���[";
	}
	else if (colider.GetTag() == GameObjectTag::Enemy)
	{
		message += "�G";
	}
	message += "�Ɠ��������I\n";
	printfDx(message.c_str());
}
