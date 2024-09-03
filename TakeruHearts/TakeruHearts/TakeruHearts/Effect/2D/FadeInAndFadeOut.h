#pragma once
namespace Effect
{
	class FadeInAndFadeOut
	{
	private:
		int fadeAlpha;
		const int fadeSpeed;

	public:
		void UpdateFadeEffect()
		{
			if (fadeAlpha < 255)
			{
				fadeAlpha += fadeSpeed;
				if (fadeAlpha > 255)
				{
					fadeAlpha = 255;
				}
			}
		}
	};
}

