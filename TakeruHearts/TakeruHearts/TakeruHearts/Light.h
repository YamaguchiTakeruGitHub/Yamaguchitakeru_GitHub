#pragma once
#include <DxLib.h>

namespace Light
{
	class Light
	{
	public:
		Light();
		~Light();

		void Init();
		void Update();
		void Draw();
		void Final();

	private:
		VECTOR position;

	};
}

//MEMO:
//// �W�����C�g�̕������w���̃v���X�����ɂ���
//SetLightDirection(VGet(1.0f, 0.0f, 0.0f));

