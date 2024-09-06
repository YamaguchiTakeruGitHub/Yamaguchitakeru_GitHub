#pragma once
#include "../TKRLib/ColliderData.h"
#include "DxLib.h"
#include <array>
#include <vector>

namespace TKRLib
{
	class ColliderDataOBB : public TKRLib::ColliderData
	{
    public:
        ColliderDataOBB();

        VECTOR center;    // OBBの中心位置
        std::array<float, 3> halfSize;  // OBBの半径 (幅・高さ・奥行き) の半分
        MATRIX rotation;  // OBBの回転行列（方向）

        // OBBの各頂点を計算
        std::vector<VECTOR> GetVertices() const;
    };
}

