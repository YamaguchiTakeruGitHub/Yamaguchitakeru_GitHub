#pragma once
#include "DxLib.h"


/// <summary>
/// ���J�����N���X��
/// �J�����̐݌v�}�͂����ō쐬����
/// </summary>
class Camera
{
public:
	Camera();
	~Camera();
	
	void Init(VECTOR playerPos);
	void Update(VECTOR playerPos, VECTOR playerDir);

	/// <summary>
	/// ��������Ώۂ̃Z�b�g
	/// </summary>
	/// <param name="target">��������Ώۂ����Ăˁ�</param>
	void SetTarget(const VECTOR& target);

	/// <summary>
	///		�����[�U�[��`�֐����W���C�X�e�b�N�ɂ�鎋�_��]
	/// </summary>
	/// <param name="rightStickX">�W���C�X�e�b�NX��</param>
	/// <param name="rightStickY">�W���C�X�e�b�NY��</param>
	void Rotate(float rightStickX, float rightStickY);

	/// <summary>
	/// 	�����[�U�[��`�֐����J�����̈ʒu���ړ�����
	/// </summary>
	/// <param name="newPosition">�V�����ʒu</param>
	/// <param name="duration">�Ԋu</param>
	void MoveToPosition(const VECTOR& newPosition, float duration);

	
	float GetCameraHAngle() const { return cameraHAngle; }
	float GetCameraVAngle() const { return cameraVAngle; }

	const VECTOR& GetPos() const { return pos; }


private:
	float fov;			//����p
	float fovRad;		//����p���W�A��
	float posRad;		//�ꏊ���W�A��
	
	VECTOR pos;			//�J�����ʒu
	VECTOR offset;		//�v���C���[����̃I�t�Z�b�g�i�ʒu����_����̋����ŕ\�����l�̂��Ɓj
	VECTOR targetPos;	//��������Ώۂ̈ʒu

	//
	float cameraHAngle;//�����A���O��(Y����])
	float cameraVAngle;//�����A���O��(X����])
	
	constexpr static float defaultFov		= 60.0f;
	constexpr static float fovRange			= 30.0f;
	constexpr static float fovChangeSpeed	= 0.01f;
	constexpr static float posRange			= 3.0f;
	constexpr static float posChangeSpeed	= 0.03f;
};

