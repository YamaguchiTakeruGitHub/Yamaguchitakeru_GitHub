#include "Camera.h"
#include <math.h>

#define CAMERA_LENGTH 100.0f

#define CAMERA_ANGLE_SPEED 3.0f

#define CAMERA_LOOK_AT_HEIGHT 400.0f 

#define CAMERA_LOOK_AT_DISTANCE 2150.0f


Camera::Camera()
	: fov(60.0f)
	, fovRad(0.0f)
	, pos(VGet(0, 0, 0))
	, posRad(0.0f)
	, offset(VGet(0.0f, 5.0f, -20.0f))
	, targetPos(VGet(0.0f, 0.0f, 0.0f))
	, cameraHAngle(0.0f)
	, cameraVAngle(40.0f)
{
	SetCameraNearFar(0.1f, 1000.0f);
}

Camera::~Camera()
{
}

void Camera::Init(VECTOR playerPos)
{
	offset = VGet(0.0f, 10.0f, -20.0f);
	pos = VAdd(playerPos, offset);
	targetPos = playerPos;
	SetCameraPositionAndTarget_UpVecY(pos, targetPos);
}

void Camera::Update(VECTOR playerPos, VECTOR playerDir)
{
	VECTOR adjustedOffset = VTransform(offset, MGetRotY(atan2f(playerDir.x, playerDir.z)));
	pos = VAdd(playerPos, adjustedOffset);
	targetPos = playerPos;

	SetCameraPositionAndTarget_UpVecY(pos, targetPos);
}

void Camera::SetTarget(const VECTOR& target)
{
	targetPos = target;
}



void Camera::Rotate(float rightStickX, float rightStickY)
{
	cameraHAngle = rightStickX * 5.05f;
	cameraVAngle = rightStickY * 5.05f;

	MATRIX rotationX = MGetRotY(cameraHAngle);//水平方向の回転（Y軸の回転行列）
	MATRIX rotationY = MGetRotX(cameraVAngle);//垂直方向の回転（X軸の回転行列）
	offset = VTransform(offset, rotationX);//ベクトルに行列を適用し、ベクトル変換
	offset = VTransform(offset, rotationY);

	pos = VAdd(targetPos, offset);
	SetCameraPositionAndTarget_UpVecY(pos, targetPos);

#if _DEBUG
	DrawFormatString(200, 300, 0xffffff, "x=%f, y=%f, z=%f", pos.x, pos.y, pos.z);
	DrawFormatString(200, 320, 0xffffff, "Angle X=%f, Angle Y=%f", cameraVAngle, cameraHAngle);

#endif

}

void Camera::MoveToPosition(const VECTOR& newPosition, float duration)
{
	//線形補間で徐々にカメラを移動

	float elapsedTime = 0.0f;//経過時間

	//経過時間が間隔より小さくなった場合
	while (elapsedTime < duration)
	{
		pos = VAdd(VScale(pos, 1.0f - elapsedTime / duration), VScale(newPosition, elapsedTime / duration));
		SetCameraPositionAndTarget_UpVecY(pos, targetPos);
		elapsedTime += 1.0f / 60.0f;//1フレームごとに更新
	}
}




//Rotate
//ステック水平入力、カメラを水平方向に回転させる行列
//ステックの垂直入力。

//カメラ位置に対して水平方向と垂直方向の回転を適用

//回転したあとのカメラ位置を計算し、その位置からプレイヤーにむかいかめらをはいち

//カメラを新し位置に設定し注視点に向かってカメラを向ける
//参考にしたサイト
//URL（https://www.bing.com/ck/a?!&&p=b245f06a81a1ea77JmltdHM9MTcyNDcxNjgwMCZpZ3VpZD0zY2VkYWQxZi02MmEwLTY1NjYtMjZmMy1iZWY0NjMxNzY0ZDcmaW5zaWQ9NTIzNw&ptn=3&ver=2&hsh=3&fclid=3cedad1f-62a0-6566-26f3-bef4631764d7&psq=Dxlib+VTransform&u=a1aHR0cHM6Ly9kaXhxLm5ldC9mb3J1bS92aWV3dG9waWMucGhwP3Q9MTg1NDk&ntb=1）