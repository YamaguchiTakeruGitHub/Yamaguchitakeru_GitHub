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
	position = VGet(0.0f, 0.0f, 0.0f);
}

void Light::Light::Update()
{
}

void Light::Light::Draw()
{
}

void Light::Light::Final()
{
}
