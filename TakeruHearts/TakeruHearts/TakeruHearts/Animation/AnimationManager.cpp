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
	//キャラクターごとのアニメーション霧切換
	if (currentAnimations.find(characterName) != currentAnimations.end())
	{
		currentAnimations[characterName] = animations[characterName][animationName];
	}
	else
	{
		//デフォルトアニメーションの処理
	}
}

void AnimationManager::Update(float daltaTime)
{
	//currentAnimationsを１つのユニットとして使用するためpairを使用
	//各要素にアクセスするには　変数.firstか　変数.second　でアクセスする
	for (auto& pair : currentAnimations)
	{
		const std::string& characterName = pair.first;//マップキー
		AnimationData& animData = pair.second;//マップ値

		//アニメーションの更新
		MV1SetAttachAnimTime(animData.animHandle, 0, animData.currentTime);

		//現在の時間より終了時間が大きい場合
		if (animData.currentTime > animData.endTime)
		{
			//もし繰り返しされる処理の場合
			if (animData.isLoop)
			{
				//最初からアニメションを始める
				animData.currentTime = animData.startTime;
			}
			else
			{
				//アニメションを終える
				animData.currentTime = animData.endTime;
			}
		}

	}
}
