#pragma once
#include "DxLib.h"

namespace UI
{
	class SpeechBubble
	{
	public:
		SpeechBubble();
		~SpeechBubble();

		void Init();
		void Update(VECTOR pos);
		void Draw();
		void Final();

		const VECTOR& GetPos() const { return position; }
		void SetPos(const VECTOR& set) { position = set; }

	private:
		int speechBubbleGraphHandle;
		VECTOR position;

	};
}

