#include "SoundManager.h"
#include <DxLib.h>

void SoundManager::InitChangeSound(const std::string& soundName, char* soundHandle)
{
	//BGMŒn
	int titleBGMHandle = LoadSoundMem(soundHandle, 3, -1);
	int gameBGMHandle = LoadSoundMem(soundHandle, 0, 0);
	
	//SEŒn
	int selectSEHandle = LoadSoundMem(soundHandle, 0, 0);
	int attackSEHandle = LoadSoundMem(soundHandle, 0, 0);


}

void SoundManager::ChangeSound(const std::string sceneName, const std::string& soundName)
{
}

void SoundManager::Update(float daltaTime)
{
}
