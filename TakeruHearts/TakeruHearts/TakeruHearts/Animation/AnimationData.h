#pragma once
struct AnimationData
{
	int animHandle;	//	�A�j���[�V�����n���h��
	float startTime;//�A�j���[�V�����J�n����
	float endTime;//�A�j���[�V�����I������
	bool isLoop;//���[�v���邩�ǂ���
	float currentTime;
	float speed = 1.0f;
};