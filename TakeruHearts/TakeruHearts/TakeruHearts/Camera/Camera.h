#pragma once
#include "DxLib.h"

class Camera
{
public:
	Camera();
	
	void Init();
	void Update(float rightSticX, float rightStickY, VECTOR targetPos);

private:
	VECTOR position;//位置
	VECTOR direction;//向き
	VECTOR velocity;//速度

	VECTOR rotationAxisX;//X軸周りの回転
	VECTOR rotationAxisY;//Y軸周りの回転

	MATRIX rotationMatrixY;//水平カメラの回転行列
	MATRIX rotationMatrixX;//垂直カメラの回転行列
	MATRIX combinedRotation;//回転行列

	float speed;//カメラ速度
	float cameraHorizontalAngle;//水平回転(Y軸)
	float cameraVerticalAngle;//垂直回転(X軸)


	MATRIX MultiplyMatrix(const MATRIX& mat1, const MATRIX& mat2);

};
