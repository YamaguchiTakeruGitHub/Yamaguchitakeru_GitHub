#pragma once
#include <unordered_map>
#include <string>
#include "AnimationData.h"

class AnimationManager
{
public:

private:
	/// <summary>
	/// ��keyType, ValueType���@KeyType�����@�AValueType���l
	/// </summary>
	std::unordered_map<std::string, std::unordered_map<std::string, AnimationData>> animations;

	/// <summary>
	/// ��keyType, ValueType���@KeyType�����@�AValueType���l
	/// </summary>
	std::unordered_map<std::string, AnimationData> currentAnimations;

public:

	void InitChangeAnimation(const std::string& characterName, int modelHandle);

	void ChangeAnimation(const std::string& characterName, const std::string& animationName);

	void Update(float daltaTime);
};


//MEMO(�����ł���������)
//�Ή�����n�b�V���l�ł��邩�Ȃ��������ʂ��邽�߂�unordered_map���g�p����

//MEMO�iunordered_map�ɂ��āj
//�����ɑ΂��Ă����Ƃ������֗��Ŏ��o�I�Ȏg������̂����^�A
//�d���L�[�͈�ӂłȂ���΂Ȃ�ȂȂ��A
//�����L�[���������̗v�f��ǉ����邱�Ƃ͂ł��Ȃ��B
//�����̓o���o���A�L�[�̑}�������͕ێ�����Ȃ��B
//�n�b�V���e�[�u�������悤���Ă��邽�߁A�L�[���g�����v�f�̃A�N�Z�X�����ɑ���
//�i���o�I�Ŏg�����肪�����Ƃ͂��ꂪ���R�j

//MEMO
//�n�b�V���e�[�u���Ƃ́u�L�[�v�Ɓu�l�v���y�A�ŊǗ�����f�[�^�\��
//�t�q�k[https://wa3.i-3-i.info/word11947.html]
