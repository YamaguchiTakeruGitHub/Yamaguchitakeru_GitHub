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
		/// 2D���C���̃f�o�b�O�\��
		/// </summary>
		/// <param name="start"></param>
		/// <param name="end"></param>
		/// <param name="color"></param>
		static void DrawLine(const VECTOR& start, const VECTOR& end, int color);

		/// <summary>
		/// 3D�̋��̃f�o�b�O�\��
		/// </summary>
		/// <param name="center"></param>
		/// <param name="radius"></param>
		/// <param name="color"></param>
		static void DrawSphere(const VECTOR& center, float radius, int color);

		/// <summary>
		/// �RD�{�b�N�X�̃f�o�b�O�\��
		/// </summary>
		/// <param name="center">VECTOR�^�̃|�W�V����</param>
		/// <param name="halfSize">std::array,float�A�R�^�̔����̃T�C�Y</param>
		/// <param name="rotation">MATRIX�^�̉�]�s��</param>
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


