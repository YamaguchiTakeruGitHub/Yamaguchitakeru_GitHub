#pragma once
#include <unordered_map>
#include <string>
#include "../Sound/SoundData.h"

class SoundManager
{
public:

private:
	std::unordered_map < std::string, std::unordered_map < std::string, SoundData >> sounds;
	std::unordered_map<std::string, SoundData> currrentSounds;



public:
	void InitChangeSound(const std::string& soundName, char* soundHandle);

	void ChangeSound(const std::string attachName, const std::string& soundName);
	void Update(float daltaTime);
};
