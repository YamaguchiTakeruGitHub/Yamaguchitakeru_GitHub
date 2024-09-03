#include "SoundManager.h"
#include <DxLib.h>

void SoundManager::InitChangeSound(const std::string& soundName, char* soundHandle)
{


	//BGM系
	int titleBGMHandle = LoadSoundMem(soundHandle, 3, -1);
	int gameBGMHandle = LoadSoundMem(soundHandle, 0, 0);

	//SE系
	int selectSEHandle = LoadSoundMem(soundHandle, 0, 0);
	int attackSEHandle = LoadSoundMem(soundHandle, 0, 0);

	sounds[soundName]["TitleBGM"] = SoundData{ titleBGMHandle, 0.0f, 1.0f, true };
	sounds[soundName]["GameBGM"] = SoundData{ gameBGMHandle, 0.0f, 1.0f, true };
	sounds[soundName]["SelectSE"] = SoundData{ selectSEHandle, 0.0f, 1.0f, true };
	sounds[soundName]["AttackSE"] = SoundData{ attackSEHandle, 0.0f, 1.0f, true };
}

void SoundManager::ChangeSound(const std::string attachName, const std::string& soundName)
{
	//アタッチするものごとのサウンド切り替え
	if (currrentSounds.find(attachName) != currrentSounds.end())//検索したキーの名前と、指定した物の要素が違えば
	{
		//現在のサウンドに別のサウンドを入れる
		currrentSounds[attachName] = sounds[attachName][soundName];
	}
	else
	{
		//何もしていない際、サウンドを流す場所

	}
}

void SoundManager::Update(float daltaTime)
{
	//pairをcurrentSoundsのユニットとして使用
	for (auto& pair : currrentSounds)
	{
		bool isLoopSound;		//繰り返し再生するか
		bool isNormalSound;		//ノーマル再生するか
		//bool isBackGroundSound;	//バックグラウンド再生するか

		const std::string& soundName = pair.first;//マップキー
		SoundData& soundData = pair.second;//マップの値

		//ノーマルサウンドの更新
		if (isNormalSound = true)
		{
			PlaySoundMem(soundData.soundHandle, DX_PLAYTYPE_NORMAL, true);
		}

		//ループサウンドの更新
		if (isLoopSound = true)
		{
			PlaySoundMem(soundData.soundHandle, DX_PLAYTYPE_LOOP, true);
		}

		//バックグラウンドサウンドの更新
		if (isNormalSound = true)
		{
			PlaySoundMem(soundData.soundHandle, DX_PLAYTYPE_BACK, true);
		}

		//現在の再生時間より終了時間が大きい場合
		if (soundData.currentTime > soundData.endTime)
		{
			//サウンドが繰り返し行われる場合
			if (soundData.isLoop)
			{
				//最初からサウンドを鳴らす
				soundData.currentTime = soundData.startTime;
				
				//サウンドを繰り返す
				isLoopSound = true;
			}
			else
			{
				//サウンドを終える
				soundData.currentTime = soundData.endTime;

				//フラグをたたむ
				isLoopSound = false;

			}
		}
		
	}
}
