#pragma once
#include "../../LocalTag.h"

namespace UI
{
	class Image
	{
	public:
		Image();
		~Image();

		void Init();
		void Update();
		void Draw();
		void End();

		int imageHandelContainer;

	};
}
