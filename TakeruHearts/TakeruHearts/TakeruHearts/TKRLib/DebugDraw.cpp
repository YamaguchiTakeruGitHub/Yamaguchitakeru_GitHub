#include "DebugDraw.h"

std::vector<TKRLib::DebugDraw::LineInfo> TKRLib::DebugDraw::lineInfo;
std::vector<TKRLib::DebugDraw::SphereInfo> TKRLib::DebugDraw::sphereInfo;


void TKRLib::DebugDraw::Clear()
{
	lineInfo.clear();
	sphereInfo.clear();
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

