#pragma once
#include "DxLib.h"
#include <vector>
namespace TKRLib
{
	class DebugDraw
	{
	public:
		static void Clear();
		static void Draw();

		static void DrawLine(const VECTOR& start, const VECTOR& end, int color);

		static void DrawSphere(const VECTOR& center, float radius, int color);

	private:
		struct LineInfo
		{
			VECTOR start;
			VECTOR end;
			int color;
		};

		struct SphereInfo
		{
			VECTOR center;
			float radius;
			int color;
		};

		static std::vector<LineInfo>lineInfo;
		static std::vector<SphereInfo> sphereInfo;
	};
}


