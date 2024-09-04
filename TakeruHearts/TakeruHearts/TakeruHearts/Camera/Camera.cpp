#include "Camera.h"

Camera::Camera()
	: position				()
	, direction				()
	, velocity				()
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
	position			  = VGet(0.0f, 0.0f, 50.0f);
	direction			  = VGet(0.0f, 0.0f, 0.0f);
	velocity			  = VGet(0.0f, 0.0f, 0.0f);
	speed				  = 10.0f;
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

	//もしカメラが９０度を超えた場合
	if (cameraVerticalAngle > DX_PI_F / 2.0f)
	{
		//垂直角度を９０度にし続ける
		cameraVerticalAngle = DX_PI_F / 2.0f;
	}

	//もしカメラが-９０度を超えた場合
	if (cameraVerticalAngle < -DX_PI_F / 2.0f)
	{
		//垂直角度を-９０度にし続ける
		cameraVerticalAngle = -DX_PI_F / 2.0;
	}

	rotationMatrixX = MGetRotY(cameraHorizontalAngle);
	rotationMatrixY = MGetRotX(cameraVerticalAngle);

	combinedRotation = MultiplyMatrix(rotationMatrixY, rotationMatrixX);
	
	direction = VSub(targetPos, position);

	direction = VTransform(direction, combinedRotation);
	targetPos = VAdd(position, direction);
	SetCameraPositionAndTarget_UpVecY(position, targetPos);
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
