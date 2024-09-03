#include "SoundManager.h"
#include <DxLib.h>

void SoundManager::InitChangeSound(const std::string& soundName, char* soundHandle)
{


	//BGM�n
	int titleBGMHandle = LoadSoundMem(soundHandle, 3, -1);
	int gameBGMHandle = LoadSoundMem(soundHandle, 0, 0);

	//SE�n
	int selectSEHandle = LoadSoundMem(soundHandle, 0, 0);
	int attackSEHandle = LoadSoundMem(soundHandle, 0, 0);

	sounds[soundName]["TitleBGM"] = SoundData{ titleBGMHandle, 0.0f, 1.0f, true };
	sounds[soundName]["GameBGM"] = SoundData{ gameBGMHandle, 0.0f, 1.0f, true };
	sounds[soundName]["SelectSE"] = SoundData{ selectSEHandle, 0.0f, 1.0f, true };
	sounds[soundName]["AttackSE"] = SoundData{ attackSEHandle, 0.0f, 1.0f, true };
}

void SoundManager::ChangeSound(const std::string attachName, const std::string& soundName)
{
	//�A�^�b�`������̂��Ƃ̃T�E���h�؂�ւ�
	if (currrentSounds.find(attachName) != currrentSounds.end())//���������L�[�̖��O�ƁA�w�肵�����̗v�f���Ⴆ��
	{
		//���݂̃T�E���h�ɕʂ̃T�E���h������
		currrentSounds[attachName] = sounds[attachName][soundName];
	}
	else
	{
		//�������Ă��Ȃ��ہA�T�E���h�𗬂��ꏊ

	}
}

void SoundManager::Update(float daltaTime)
{
	//pair��currentSounds�̃��j�b�g�Ƃ��Ďg�p
	for (auto& pair : currrentSounds)
	{
		bool isLoopSound;		//�J��Ԃ��Đ����邩
		bool isNormalSound;		//�m�[�}���Đ����邩
		//bool isBackGroundSound;	//�o�b�N�O���E���h�Đ����邩

		const std::string& soundName = pair.first;//�}�b�v�L�[
		SoundData& soundData = pair.second;//�}�b�v�̒l

		//�m�[�}���T�E���h�̍X�V
		if (isNormalSound = true)
		{
			PlaySoundMem(soundData.soundHandle, DX_PLAYTYPE_NORMAL, true);
		}

		//���[�v�T�E���h�̍X�V
		if (isLoopSound = true)
		{
			PlaySoundMem(soundData.soundHandle, DX_PLAYTYPE_LOOP, true);
		}

		//�o�b�N�O���E���h�T�E���h�̍X�V
		if (isNormalSound = true)
		{
			PlaySoundMem(soundData.soundHandle, DX_PLAYTYPE_BACK, true);
		}

		//���݂̍Đ����Ԃ��I�����Ԃ��傫���ꍇ
		if (soundData.currentTime > soundData.endTime)
		{
			//�T�E���h���J��Ԃ��s����ꍇ
			if (soundData.isLoop)
			{
				//�ŏ�����T�E���h��炷
				soundData.currentTime = soundData.startTime;
				
				//�T�E���h���J��Ԃ�
				isLoopSound = true;
			}
			else
			{
				//�T�E���h���I����
				soundData.currentTime = soundData.endTime;

				//�t���O��������
				isLoopSound = false;

			}
		}
		
	}
}
