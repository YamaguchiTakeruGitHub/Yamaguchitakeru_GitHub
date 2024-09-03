#pragma once
#include <unordered_map>
#include <string>
#include "AnimationData.h"

class AnimationManager
{
public:

private:
	/// <summary>
	/// ＜keyType, ValueType＞　KeyType＝箱　、ValueType＝値
	/// </summary>
	std::unordered_map<std::string, std::unordered_map<std::string, AnimationData>> animations;

	/// <summary>
	/// ＜keyType, ValueType＞　KeyType＝箱　、ValueType＝値
	/// </summary>
	std::unordered_map<std::string, AnimationData> currentAnimations;

public:

	void InitChangeAnimation(const std::string& characterName, int modelHandle);

	void ChangeAnimation(const std::string& characterName, const std::string& animationName);

	void Update(float daltaTime);
};


//MEMO(ここでしたいこと)
//対応するハッシュ値であるかないかを識別するためにunordered_mapを使用する

//MEMO（unordered_mapについて）
//自分に対していうとすごく便利で視覚的な使い勝手のいい型、
//重複キーは一意でなければならななく、
//同じキーを持つ複数の要素を追加することはできない。
//順序はバラバラ、キーの挿入順序は保持されない。
//ハッシュテーブルをしようしているため、キーを使った要素のアクセスが非常に早い
//（視覚的で使い勝手がいいとはこれが理由）

//MEMO
//ハッシュテーブルとは「キー」と「値」をペアで管理するデータ構造
//ＵＲＬ[https://wa3.i-3-i.info/word11947.html]
