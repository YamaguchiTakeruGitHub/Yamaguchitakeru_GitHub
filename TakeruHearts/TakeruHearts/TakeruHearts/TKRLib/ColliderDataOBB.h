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

        VECTOR center;    // OBB�̒��S�ʒu
        std::array<float, 3> halfSize;  // OBB�̔��a (���E�����E���s��) �̔���
        MATRIX rotation;  // OBB�̉�]�s��i�����j

        // OBB�̊e���_���v�Z
        std::vector<VECTOR> GetVertices() const;
    };
}

