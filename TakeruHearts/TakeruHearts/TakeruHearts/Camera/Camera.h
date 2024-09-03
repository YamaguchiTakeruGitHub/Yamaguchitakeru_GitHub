#pragma once
#include "DxLib.h"


/// <summary>
/// ＜カメラクラス＞
/// カメラの設計図はここで作成する
/// </summary>
class Camera
{
public:
	Camera();
	~Camera();
	
	void Init(VECTOR playerPos);
	void Update(VECTOR playerPos, VECTOR playerDir);

	/// <summary>
	/// 注視する対象のセット
	/// </summary>
	/// <param name="target">注視する対象を入れてね☆</param>
	void SetTarget(const VECTOR& target);

	/// <summary>
	///		＜ユーザー定義関数＞ジョイステックによる視点回転
	/// </summary>
	/// <param name="rightStickX">ジョイステックX軸</param>
	/// <param name="rightStickY">ジョイステックY軸</param>
	void Rotate(float rightStickX, float rightStickY);

	/// <summary>
	/// 	＜ユーザー定義関数＞カメラの位置を移動する
	/// </summary>
	/// <param name="newPosition">新しい位置</param>
	/// <param name="duration">間隔</param>
	void MoveToPosition(const VECTOR& newPosition, float duration);

	
	float GetCameraHAngle() const { return cameraHAngle; }
	float GetCameraVAngle() const { return cameraVAngle; }

	const VECTOR& GetPos() const { return pos; }


private:
	float fov;			//視野角
	float fovRad;		//視野角ラジアン
	float posRad;		//場所ラジアン
	
	VECTOR pos;			//カメラ位置
	VECTOR offset;		//プレイヤーからのオフセット（位置を基準点からの距離で表した値のこと）
	VECTOR targetPos;	//注視する対象の位置

	//
	float cameraHAngle;//水平アングル(Y軸回転)
	float cameraVAngle;//垂直アングル(X軸回転)
	
	constexpr static float defaultFov		= 60.0f;
	constexpr static float fovRange			= 30.0f;
	constexpr static float fovChangeSpeed	= 0.01f;
	constexpr static float posRange			= 3.0f;
	constexpr static float posChangeSpeed	= 0.03f;
};

