#include "ColliderDataOBB.h"

TKRLib::ColliderDataOBB::ColliderDataOBB()
	: ColliderData(ColliderData::Kind::Box)
	, center(VGet(0, 0, 0))
    , halfSize({1.0f, 1.0f, 1.0f})
	, rotation(MGetIdent())
{
}

std::vector<VECTOR> TKRLib::ColliderDataOBB::GetVertices() const
{
    std::vector<VECTOR> vertices(8);

    // 各頂点のローカル座標
    VECTOR offsets[8] = {
         VGet(-halfSize[0], -halfSize[1], -halfSize[2]),
        VGet(halfSize[0], -halfSize[1], -halfSize[2]),
        VGet(-halfSize[0],  halfSize[1], -halfSize[2]),
        VGet(halfSize[0],  halfSize[1], -halfSize[2]),
        VGet(-halfSize[0], -halfSize[1],  halfSize[2]),
        VGet(halfSize[0], -halfSize[1],  halfSize[2]),
        VGet(-halfSize[0],  halfSize[1],  halfSize[2]),
        VGet(halfSize[0],  halfSize[1],  halfSize[2]),
    };

    // 回転を適用してワールド座標で各頂点を計算
    for (int i = 0; i < 8; ++i)
    {
        vertices[i] = VTransform(offsets[i], rotation);
        vertices[i] = VAdd(vertices[i], center); // 中心を加える
    }

    return vertices;
}
