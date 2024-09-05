#include "Camera.h"

Camera::Camera()
	: position				()
	, direction				()
	, velocity				()
	, targetPos				()
	, offset				()
	, speed					()
	, cameraHorizontalAngle	()
	, cameraVerticalAngle	()
	, rotationAxisX			()
	, rotationAxisY			()
	, rotationMatrixX		()
	, rotationMatrixY		()
	, combinedRotation		()
{
	SetCameraNearFar(0.1f, 1000.0f);
}

void Camera::Init()
{
	position			  = VGet(0.0f, 0.0f, 0.0f);
	direction			  = VGet(0.0f, 0.0f, 0.0f);
	velocity			  = VGet(0.0f, 0.0f, 0.0f);
	speed				  = 1.0f;
	offset				  = VGet(0.0f, 10.0f, 20.0f);
	cameraHorizontalAngle;
	cameraVerticalAngle;
	rotationAxisX;
	rotationAxisY;
	rotationMatrixX;
	rotationMatrixY;
	combinedRotation;
}

void Camera::Update(float rightStickX, float rightStickY, VECTOR targetPos)
{

	//回転角度を更新
	cameraHorizontalAngle += rightStickX * speed;
	cameraVerticalAngle	  -= rightStickY * speed;

	//アングルが永遠と加算されないように一周したら元の位置に戻してあげる
	if (cameraHorizontalAngle >= 6.29f)
	{
		cameraHorizontalAngle = 0.0f;
	}
	if (cameraHorizontalAngle <= -6.29f)
	{
		cameraHorizontalAngle = 0.0f;
	}



	VECTOR dir = VGet(0.0f, 0.0f, 0.0f);

	dir.x = 0;
	dir.y = 0;
	dir.z = 0;

	if (rightStickX != 0 && rightStickX <= 0.030519f && rightStickX >= 0.0f)
	{
		dir.x = 1;
	}
	if (rightStickX != 0 && rightStickX >= -0.030519f && rightStickX <= 0.0f)
	{
		dir.x = -1;
	}
	if (rightStickY != 0 && rightStickY <= 0.030519f && rightStickY >= 0.0f)
	{
		dir.y = -1;
	}
	if (rightStickY != 0 && rightStickY >= -0.030519f && rightStickY <= 0.0f)
	{
		dir.y = 1;
	}


	//もしカメラが8０度を超えた場合
	if (cameraVerticalAngle > DX_PI_F / 3.0f)
	{
		//垂直角度を8０度にし続ける
		cameraVerticalAngle = DX_PI_F / 3.0f;
	}

	//もしカメラが-8０度を超えた場合
	if (cameraVerticalAngle < -DX_PI_F / 3.0f)
	{
		//垂直角度を-8０度にし続ける
		cameraVerticalAngle = -DX_PI_F / 3.0f;
	}

	


	//カメラの水平方向回転
	rotationMatrixX = MGetRotY(cameraHorizontalAngle);
	//カメラの垂直方向かいてん
	rotationMatrixY = MGetRotX(cameraVerticalAngle);

	combinedRotation = MultiplyMatrix(rotationMatrixY, rotationMatrixX);
	


	/*
	//入力に基づいて移動方向を計算
	velocity = VTransform(position, combinedRotation);

	//カメラの位置を更新
	position = VAdd(position, velocity);

	//カメラからターゲットまでの距離を求める
	direction = VSub(targetPos, position);
	direction = VTransform(direction, combinedRotation);

	targetPos = VAdd(position, direction);
	*/
	
	position = VAdd(targetPos, VTransform(offset, combinedRotation));

	SetCameraPositionAndTarget_UpVecY(position, targetPos);



#if _DEBUG
	DrawFormatString(300, 0, 0xffffff, "camera : x%f, y%f, z%f", position.x, position.y, position.z);
	DrawFormatString(300, 20, 0xffffff, "cameraHAxis : %f",cameraHorizontalAngle);
	DrawFormatString(300, 40, 0xffffff, "camera dir : x%f, y%f, z%f", dir.x, dir.y, dir);

#endif
}


MATRIX Camera::MultiplyMatrix(const MATRIX& mat1, const MATRIX& mat2)
{
	MATRIX result;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.m[i][j] = mat1.m[i][0] * mat2.m[0][j] +
				mat1.m[i][1] * mat2.m[1][j] +
				mat1.m[i][2] * mat2.m[2][j] +
				mat1.m[i][3] * mat2.m[3][j];
		}
	}
	return result;
}
