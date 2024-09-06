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

		/// <summary>
		/// 2Dラインのデバッグ表示
		/// </summary>
		/// <param name="start"></param>
		/// <param name="end"></param>
		/// <param name="color"></param>
		static void DrawLine(const VECTOR& start, const VECTOR& end, int color);

		/// <summary>
		/// 3Dの球のデバッグ表示
		/// </summary>
		/// <param name="center"></param>
		/// <param name="radius"></param>
		/// <param name="color"></param>
		static void DrawSphere(const VECTOR& center, float radius, int color);

		/// <summary>
		/// ３Dボックスのデバッグ表示
		/// </summary>
		/// <param name="center">VECTOR型のポジション</param>
		/// <param name="halfSize">std::array,float、３型の半分のサイズ</param>
		/// <param name="rotation">MATRIX型の回転行列</param>
		/// <param name="color"></param>
		static void DrawOBB(const VECTOR& center, const std::array<float, 3>& halfSize, const MATRIX& rotation, int color);


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

		struct OBBInfo
		{
			VECTOR center;
			std::array<float, 3>& halfSize;
			MATRIX& rotation;
			int color;
		};

		static std::vector<LineInfo>lineInfo;
		static std::vector<SphereInfo> sphereInfo;
		static std::vector<OBBInfo> obbInfo;
	};
}


