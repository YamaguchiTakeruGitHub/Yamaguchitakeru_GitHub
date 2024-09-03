#include "Camera.h"
#include <math.h>

#define CAMERA_LENGTH 100.0f

#define CAMERA_ANGLE_SPEED 3.0f

#define CAMERA_LOOK_AT_HEIGHT 400.0f 

#define CAMERA_LOOK_AT_DISTANCE 2150.0f


Camera::Camera()
	: fov(60.0f)
	, fovRad(0.0f)
	, pos(VGet(0, 0, 0))
	, posRad(0.0f)
	, offset(VGet(0.0f, 5.0f, -20.0f))
	, targetPos(VGet(0.0f, 0.0f, 0.0f))
	, cameraHAngle(0.0f)
	, cameraVAngle(40.0f)
{
	SetCameraNearFar(0.1f, 1000.0f);
}

Camera::~Camera()
{
}

void Camera::Init(VECTOR playerPos)
{
	offset = VGet(0.0f, 10.0f, -20.0f);
	pos = VAdd(playerPos, offset);
	targetPos = playerPos;
	SetCameraPositionAndTarget_UpVecY(pos, targetPos);
}

void Camera::Update(VECTOR playerPos, VECTOR playerDir)
{
	VECTOR adjustedOffset = VTransform(offset, MGetRotY(atan2f(playerDir.x, playerDir.z)));
	pos = VAdd(playerPos, adjustedOffset);
	targetPos = playerPos;

	SetCameraPositionAndTarget_UpVecY(pos, targetPos);
}

void Camera::SetTarget(const VECTOR& target)
{
	targetPos = target;
}



void Camera::Rotate(float rightStickX, float rightStickY)
{
	cameraHAngle = rightStickX * 5.05f;
	cameraVAngle = rightStickY * 5.05f;

	MATRIX rotationX = MGetRotY(cameraHAngle);//���������̉�]�iY���̉�]�s��j
	MATRIX rotationY = MGetRotX(cameraVAngle);//���������̉�]�iX���̉�]�s��j
	offset = VTransform(offset, rotationX);//�x�N�g���ɍs���K�p���A�x�N�g���ϊ�
	offset = VTransform(offset, rotationY);

	pos = VAdd(targetPos, offset);
	SetCameraPositionAndTarget_UpVecY(pos, targetPos);

#if _DEBUG
	DrawFormatString(200, 300, 0xffffff, "x=%f, y=%f, z=%f", pos.x, pos.y, pos.z);
	DrawFormatString(200, 320, 0xffffff, "Angle X=%f, Angle Y=%f", cameraVAngle, cameraHAngle);

#endif

}

void Camera::MoveToPosition(const VECTOR& newPosition, float duration)
{
	//���`��Ԃŏ��X�ɃJ�������ړ�

	float elapsedTime = 0.0f;//�o�ߎ���

	//�o�ߎ��Ԃ��Ԋu��菬�����Ȃ����ꍇ
	while (elapsedTime < duration)
	{
		pos = VAdd(VScale(pos, 1.0f - elapsedTime / duration), VScale(newPosition, elapsedTime / duration));
		SetCameraPositionAndTarget_UpVecY(pos, targetPos);
		elapsedTime += 1.0f / 60.0f;//1�t���[�����ƂɍX�V
	}
}




//Rotate
//�X�e�b�N�������́A�J�����𐅕������ɉ�]������s��
//�X�e�b�N�̐������́B

//�J�����ʒu�ɑ΂��Đ��������Ɛ��������̉�]��K�p

//��]�������Ƃ̃J�����ʒu���v�Z���A���̈ʒu����v���C���[�ɂނ������߂���͂���

//�J������V���ʒu�ɐݒ肵�����_�Ɍ������ăJ������������
//�Q�l�ɂ����T�C�g
//URL�ihttps://www.bing.com/ck/a?!&&p=b245f06a81a1ea77JmltdHM9MTcyNDcxNjgwMCZpZ3VpZD0zY2VkYWQxZi02MmEwLTY1NjYtMjZmMy1iZWY0NjMxNzY0ZDcmaW5zaWQ9NTIzNw&ptn=3&ver=2&hsh=3&fclid=3cedad1f-62a0-6566-26f3-bef4631764d7&psq=Dxlib+VTransform&u=a1aHR0cHM6Ly9kaXhxLm5ldC9mb3J1bS92aWV3dG9waWMucGhwP3Q9MTg1NDk&ntb=1�j