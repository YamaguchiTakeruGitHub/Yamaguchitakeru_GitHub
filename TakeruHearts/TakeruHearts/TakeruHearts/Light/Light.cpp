#include "Light.h"

Light::Light::Light()
	: position()
{
}

Light::Light::~Light()
{
}

void Light::Light::Init()
{
	position = VGet(5.0f, -5.0f, -5.0f);
}

void Light::Light::Update()
{
	// �W�����C�g�̕������w���̃v���X�����ɂ���
	SetLightDirection(position);
}

void Light::Light::Draw()
{
}

void Light::Light::Final()
{
}
