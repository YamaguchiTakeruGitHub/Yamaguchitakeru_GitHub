#include "DebugDraw.h"
#include <array>
#include <utility>


std::vector<TKRLib::DebugDraw::LineInfo> TKRLib::DebugDraw::lineInfo;
std::vector<TKRLib::DebugDraw::SphereInfo> TKRLib::DebugDraw::sphereInfo;
std::vector<TKRLib::DebugDraw::OBBInfo> TKRLib::DebugDraw::obbInfo;

void TKRLib::DebugDraw::Clear()
{
	lineInfo.clear();
	sphereInfo.clear();
	obbInfo.clear();
}

void TKRLib::DebugDraw::Draw()
{
	for (const auto& item : lineInfo)
	{
		DxLib::DrawLine(static_cast<int>(item.start.x),
			static_cast<int>(item.start.y),
			static_cast<int>(item.end.x),
			static_cast<int>(item.end.y),
			item.color);
	}

	for (const auto& item : sphereInfo)
	{
		DxLib::DrawSphere3D(item.center,
			item.radius,
			5,
			item.color,
			item.color, false);
	}

	for (const auto& item : obbInfo)
	{
		DrawOBB(item.center, item.halfSize, item.rotation, item.color);
	}

}
/// <summary>
/// ƒ‰ƒCƒ“•`‰æ
/// </summary>
/// <param name="start"></param>
/// <param name="end"></param>
/// <param name="color"></param>
void TKRLib::DebugDraw::DrawLine(const VECTOR& start, const VECTOR& end, int color)
{
	LineInfo newInfo{};
	newInfo.start = start;
	newInfo.end = end;
	newInfo.color = color;
	lineInfo.push_back(newInfo);
}

/// <summary>
/// ‹…•`‰æ
/// </summary>
/// <param name="center"></param>
/// <param name="radius"></param>
/// <param name="color"></param>
void TKRLib::DebugDraw::DrawSphere(const VECTOR& center, float radius, int color)
{
	SphereInfo newInfo;
	newInfo.center = center;
	newInfo.radius = radius;
	newInfo.color = color;
	sphereInfo.emplace_back(newInfo);
}

void TKRLib::DebugDraw::DrawOBB(const VECTOR& center, const std::array<float, 3>& halfSize, const MATRIX& rotation, int color)
{
	// OBB‚Ì8‚Â‚Ì’¸“_‚ðŒvŽZ
	std::array<VECTOR, 8> vertices;
	for (int i = 0; i < 8; ++i)
	{
		VECTOR offset = VGet(
			(i & 1 ? halfSize[0] : -halfSize[0]),
			(i & 2 ? halfSize[1] : -halfSize[1]),
			(i & 4 ? halfSize[2] : -halfSize[2])
		);

		vertices[i] = VAdd(center, VTransform(offset, rotation));
	}

	// OBB‚Ì12–{‚ÌƒGƒbƒW‚ð•`‰æ
	const std::array<std::pair<int, int>, 12> edges = { {
		{0, 1}, {1, 3}, {3, 2}, {2, 0},
		{4, 5}, {5, 7}, {7, 6}, {6, 4},
		{0, 4}, {1, 5}, {3, 7}, {2, 6}
	} };

	for (const auto& edge : edges)
	{
		DrawLine3D(vertices[edge.first], vertices[edge.second], color);
	}

}

