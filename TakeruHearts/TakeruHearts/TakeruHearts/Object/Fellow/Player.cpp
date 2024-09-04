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
	//���̓f�o�C�X�̍X�V
	idm->Update();

	//���X�e�B�b�N�̏���
	float leftSticX = idm->joypad->GetLeftStickX();
	float leftSticY = idm->joypad->GetLeftStickY();
		
	//�����̐ݒ�
	VECTOR dir = VGet(0.0f, 0.0f, 0.0f);
	
	//��������ɂق��Ɍ����Ȃ��悤�ɐ^�񒆂ɖ߂�
	dir.x = 0.0f;
	dir.y = 0.0f;
	dir.z = 0.0f;

	//���͂�����ǂ��Ȃ邩
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

	//�������[����葽���ꍇ
	if (VSquareSize(dir) > 0)
	{
		//�������m�[�}���C�Y����
		dir = VNorm(dir);
	}

	//�����Ɨ�(speed)���X�P�[�����O�����x�ɕϊ�
	rigidbody.SetVelocity(VScale(dir, speed));
	
	//���݂̈ʒu�Ƒ��x�𑫂��Ď��̈ʒu�Ɉړ�
	VECTOR newPos = VAdd(rigidbody.GetPos(), rigidbody.GetVelocity());

	//�ʒu�̃Z�b�g
	rigidbody.SetPos(newPos);

	// ���f���̕`��ʒu���X�V
	MV1SetPosition(modelHandle, newPos);

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
