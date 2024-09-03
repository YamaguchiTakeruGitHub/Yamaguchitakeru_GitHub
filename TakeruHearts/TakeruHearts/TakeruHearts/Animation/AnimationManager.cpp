#include "AnimationManager.h"
#include "DxLib.h"

void AnimationManager::InitChangeAnimation(const std::string& characterName, int modelHandle)
{
	int runAnimHandle = MV1AttachAnim(modelHandle, 0, -1, false);
	int attackAnimHandle = MV1AttachAnim(modelHandle, 1, -1, false);
	int idleAnimHandle = MV1AttachAnim(modelHandle, 2, -1, false);

	animations[characterName]["Run"] = AnimationData{ runAnimHandle, 0.0f, 1.0f, true };
	animations[characterName]["Attack"] = AnimationData{ attackAnimHandle, 0.0f, 0.5f, false };
	animations[characterName]["Idle"] = AnimationData{ idleAnimHandle, 0.0f, 1.0f, true };
}

void AnimationManager::ChangeAnimation(const std::string& characterName, const std::string& animationName)
{
	//�L�����N�^�[���Ƃ̃A�j���[�V�������؊�
	if (currentAnimations.find(characterName) != currentAnimations.end())
	{
		currentAnimations[characterName] = animations[characterName][animationName];
	}
	else
	{
		//�f�t�H���g�A�j���[�V�����̏���
	}
}

void AnimationManager::Update(float daltaTime)
{
	//currentAnimations���P�̃��j�b�g�Ƃ��Ďg�p���邽��pair���g�p
	//�e�v�f�ɃA�N�Z�X����ɂ́@�ϐ�.first���@�ϐ�.second�@�ŃA�N�Z�X����
	for (auto& pair : currentAnimations)
	{
		const std::string& characterName = pair.first;//�}�b�v�L�[
		AnimationData& animData = pair.second;//�}�b�v�l

		//�A�j���[�V�����̍X�V
		MV1SetAttachAnimTime(animData.animHandle, 0, animData.currentTime);

		//���݂̎��Ԃ��I�����Ԃ��傫���ꍇ
		if (animData.currentTime > animData.endTime)
		{
			//�����J��Ԃ�����鏈���̏ꍇ
			if (animData.isLoop)
			{
				//�ŏ�����A�j���V�������n�߂�
				animData.currentTime = animData.startTime;
			}
			else
			{
				//�A�j���V�������I����
				animData.currentTime = animData.endTime;
			}
		}

	}
}
