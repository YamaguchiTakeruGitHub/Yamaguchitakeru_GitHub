#pragma once
struct AnimationData
{
	int animHandle;	//	アニメーションハンドル
	float startTime;//アニメーション開始時間
	float endTime;//アニメーション終了時間
	bool isLoop;//ループするかどうか
	float currentTime;
	float speed = 1.0f;
};