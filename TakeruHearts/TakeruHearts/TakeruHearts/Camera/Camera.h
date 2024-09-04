#pragma once
#include "DxLib.h"

class Camera
{
public:
	Camera();
	
	void Init();
	void Update(float rightSticX, float rightStickY, VECTOR targetPos);

private:
	VECTOR position;//�ʒu
	VECTOR direction;//����
	VECTOR velocity;//���x

	VECTOR rotationAxisX;//X������̉�]
	VECTOR rotationAxisY;//Y������̉�]

	MATRIX rotationMatrixY;//�����J�����̉�]�s��
	MATRIX rotationMatrixX;//�����J�����̉�]�s��
	MATRIX combinedRotation;//��]�s��

	float speed;//�J�������x
	float cameraHorizontalAngle;//������](Y��)
	float cameraVerticalAngle;//������](X��)


	MATRIX MultiplyMatrix(const MATRIX& mat1, const MATRIX& mat2);

};
