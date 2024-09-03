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
//// 標準ライトの方向をＸ軸のプラス方向にする
//SetLightDirection(VGet(1.0f, 0.0f, 0.0f));

