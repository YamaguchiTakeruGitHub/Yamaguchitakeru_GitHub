#include "DxLib.h"
#include "../TKRLib/Physics.h"
#include <cassert>
#include <cmath>
#include <array>


//少し余分に離す
#define A_LITTLE_EXTRA_RELEASE 0.0001f

/// <summary>
/// 登録
/// </summary>
/// <param name="collidable"></param>
void TKRLib::Physics::Entry(Collidable* collidable)
{
	//登録
	bool found = (std::find(collidables.begin(), collidables.end(), collidable) != collidables.end());
	if (!found)
	{
		collidables.emplace_back(collidable);
	}
	else//登録されていたらエラーを吐く
	{
		assert(0 && "指定のcollidableは登録済みだお");
	}
}

/// <summary>
/// 登録解除
/// </summary>
/// <param name="collidable"></param>
void TKRLib::Physics::Exit(Collidable* collidable)
{

	//登録の解除
	bool found = (std::find(collidables.begin(), collidables.end(), collidable) != collidables.end());
	if (found)
	{
		collidables.remove(collidable);
	}
	else//登録されてなかったらエラーを吐く
	{
		assert(0 && "指定のcollidableは登録済みじゃないお");
	}
}

/// <summary>
/// 更新（登録しているobjの物理処理や、衝突通知）
/// </summary>
void TKRLib::Physics::Update()
{
	for (auto& item : collidables)
	{
		auto pos = item->rigidbody.GetPos();
		//auto velocity = item->rigidbody.GetVelocity();

		//// 重力を利用する設定なら、重力を追加する

		//if (item->rigidbody.UseGravity())
		//{
		//	velocity = VAdd(velocity, VGet(0, Gravity, 0));

		//	// 最大重力加速度より大きかったらクランプ
		//	if (velocity.y < MaxGravityAccel)
		//	{
		//		velocity = VGet(velocity.x, MaxGravityAccel, velocity.z);
		//	}
		//}
		
		auto nextPos = VAdd(pos, item->rigidbody.GetVelocity());
		//item->rigidbody.SetVelocity(velocity);

#if _DEBUG
		if (item->colliderData->GetKind() == TKRLib::ColliderData::Kind::Sphere)
		{
			ColliderDataSphere* sphereData;
			sphereData = dynamic_cast<ColliderDataSphere*>(item->colliderData);
			float radius = sphereData->radius;
			DebugDraw::DrawSphere(pos, radius, BeforeFixInfoColor);
			DebugDraw::DrawLine(pos, nextPos, AimInfoColor);
			DebugDraw::DrawSphere(nextPos, radius, AimInfoColor);
		}
		if (item->colliderData->GetKind() == TKRLib::ColliderData::Kind::Box)
		{
			ColliderDataOBB* obbData;
			obbData = dynamic_cast<ColliderDataOBB*>(item->colliderData);
			VECTOR center = obbData->center;
			std::array<float, 3> halfSize = obbData->halfSize;
			MATRIX rotation = obbData->rotation;
			DebugDraw::DrawOBB(center, halfSize, rotation, BeforeFixInfoColor);

		}

#endif
		//ポジションの確定
		//item->rigidbody.SetPos(nextPos);
		item->nextPos = nextPos;
	}

	//当たり判定のチェック
	std::vector<OnCollideInfo> onCollideInfo = CheckColide();

	//位置の確定
	FixPosition();

	//当たり判定の通知
	for (auto& item : onCollideInfo)
	{
		//所有者から知らせる
		item.owner->OnCollide(*item.colider);
	}


}

std::vector<TKRLib::Physics::OnCollideInfo> TKRLib::Physics::CheckColide() const
{
	std::vector<TKRLib::Physics::OnCollideInfo> onCollideInfo;

	//衝突つうち、ポジション補正
	bool doCheck = true;
	//チェック回数
	int checkCount = 0;

	while (doCheck)
	{
		doCheck = false;
		++checkCount;

		for (auto& objA : collidables)
		{
			for (auto& objB : collidables)
			{
				if (objA != objB)
				{
					//お互いの距離が半径をたしたものより小さければあたる
					if (IsCollide(objA, objB))
					{
						auto priorityA = objA->GetPriority();
						auto priorityB = objB->GetPriority();

						//プライオリティの高いほうを移動
						Collidable* primary = objA;
						Collidable* secondary = objB;
						if (priorityA < priorityB)
						{
							primary = objB;
							secondary = objA;
						}
						FixNextPosition(primary, secondary);

						//衝突通知情報の更新
						bool hasPrimaryInfo = false;
						bool hasSecondaryInfo = false;

						for (const auto& item : onCollideInfo)
						{
							//すでに通知リストにあったら呼ばない
							if (item.owner == primary)
							{
								hasPrimaryInfo = true;
							}
							if (item.owner == secondary)
							{
								hasSecondaryInfo = true;
							}
						}
						//通知リスとにない場合
						if (!hasPrimaryInfo)
						{
							//通知を押し出す
							onCollideInfo.push_back({ primary, secondary });
						}
						if (!hasSecondaryInfo)
						{
							//上記同様
							onCollideInfo.push_back({ secondary,primary });
						}

						//一度でもヒット補正したら衝突判定と補正のやり直し
						doCheck = true;
						break;

					}
				}
			}
			if (doCheck)
			{
				break;
			}
		}
		//無限ループを防ぐ
		if (checkCount > 1000 && doCheck)
		{
#if _DEBUG
			printfDx("当たり判定の繰り返しチェックが設定数を超えました\n");
#endif
			break;
		}

	}
	return onCollideInfo;
}

bool TKRLib::Physics::IsCollide(const Collidable* objA, const Collidable* objB) const
{
	bool isHit = false;

	//collidableの種類別で当たり判定を分ける
	auto aKind = objA->colliderData->GetKind();
	auto bKind = objB->colliderData->GetKind();

	//球と球また別の当たり判定で分ける
	if (aKind == TKRLib::ColliderData::Kind::Sphere &&
		bKind == TKRLib::ColliderData::Kind::Sphere)
	{
		auto atob = VSub(objB->nextPos, objA->nextPos);
		auto atobLength = VSize(atob);

		//お互いの距離が、それぞれの半径を足したものより小さい場合
		auto objAColliderData = dynamic_cast<ColliderDataSphere*>(objA->colliderData);
		auto objBColliderData = dynamic_cast<ColliderDataSphere*>(objB->colliderData);
		isHit = (atobLength < objAColliderData->radius + objBColliderData->radius);
	}
	else if (aKind == ColliderData::Kind::Box && bKind == ColliderData::Kind::Box)
	{
		// OBB同士の当たり判定 (Separating Axis Theorem, SAT を使う)
		auto obbA = dynamic_cast<ColliderDataOBB*>(objA->colliderData);
		auto obbB = dynamic_cast<ColliderDataOBB*>(objB->colliderData);
		isHit = CheckOBBOverlap(obbA, obbB);
	}
	else if (aKind == ColliderData::Kind::Box && bKind == ColliderData::Kind::Sphere)
	{
		// OBB vs Sphere 判定
		auto obb = dynamic_cast<ColliderDataOBB*>(objA->colliderData);
		auto sphere = dynamic_cast<ColliderDataSphere*>(objB->colliderData);
		isHit = CheckOBBSphereCollision(obb, objA->nextPos, sphere, objB->nextPos);
	}
	else if (aKind == ColliderData::Kind::Sphere && bKind == ColliderData::Kind::Box)
	{
		// Sphere vs OBB 判定（順序を逆にして処理）
		auto sphere = dynamic_cast<ColliderDataSphere*>(objA->colliderData);
		auto obb = dynamic_cast<ColliderDataOBB*>(objB->colliderData);
		isHit = CheckOBBSphereCollision(obb, objB->nextPos, sphere, objA->nextPos);
	}


	return isHit;
}

/// <summary>
/// 次の位置の補正
/// </summary>
/// <param name="primary"></param>
/// <param name="secondary"></param>
void TKRLib::Physics::FixNextPosition(Collidable* primary, Collidable* secondary) const
{
	auto primaryKind = primary->colliderData->GetKind();
	auto secondaryKind = secondary->colliderData->GetKind();


	//球同士の位置補正
	if (primaryKind == ColliderData::Kind::Sphere && secondaryKind == ColliderData::Kind::Sphere)
	{
		VECTOR primaryToSecondary = VSub(secondary->nextPos, primary->nextPos);
		VECTOR primaryToSecondaryN = VNorm(primaryToSecondary);

		auto primaryColliderData = dynamic_cast<ColliderDataSphere*> (primary->colliderData);
		auto SecondaryColliderData = dynamic_cast<ColliderDataSphere*>(secondary->colliderData);
		float awayDist = primaryColliderData->radius + SecondaryColliderData->radius + A_LITTLE_EXTRA_RELEASE;
		VECTOR primaryToNewSecondaryPos = VScale(primaryToSecondaryN, awayDist);
		VECTOR fixedPos = VAdd(primary->nextPos, primaryToNewSecondaryPos);
		secondary->nextPos = fixedPos;
	}
	else if (primaryKind == ColliderData::Kind::Box && secondaryKind == ColliderData::Kind::Sphere)
	{
		// OBB vs Sphere の位置補正
		auto obb = dynamic_cast<ColliderDataOBB*>(primary->colliderData);
		auto sphere = dynamic_cast<ColliderDataSphere*>(secondary->colliderData);

		VECTOR obbPos = primary->nextPos;
		VECTOR spherePos = secondary->nextPos;

		// OBBの最近接点を見つける
		VECTOR closestPoint = spherePos;
		for (int i = 0; i < 3; ++i)
		{
			VECTOR axis = VGet(obb->rotation.m[i][0], obb->rotation.m[i][1], obb->rotation.m[i][2]);
			VECTOR obbToSphere = VSub(spherePos, obbPos);
			float distance = VDot(obbToSphere, axis);
			if (distance > obb->halfSize[i]) distance = obb->halfSize[i];
			if (distance < -obb->halfSize[i]) distance = -obb->halfSize[i];
			closestPoint = VAdd(closestPoint, VScale(axis, distance));
		}

		// 球をOBBの外側に押し出す
		VECTOR closestToSphere = VSub(closestPoint, spherePos);
		VECTOR normalized = VNorm(closestToSphere);
		float overlap = sphere->radius - VSize(closestToSphere);
		if (overlap > 0.0f)
		{
			secondary->nextPos = VAdd(spherePos, VScale(normalized, overlap + A_LITTLE_EXTRA_RELEASE));
		}
	}
	else if (primaryKind == ColliderData::Kind::Box && secondaryKind == ColliderData::Kind::Box)
	{
		// OBB vs OBB の位置補正
		auto obb1 = dynamic_cast<ColliderDataOBB*>(primary->colliderData);
		auto obb2 = dynamic_cast<ColliderDataOBB*>(secondary->colliderData);

		// OBBの中心位置
		VECTOR obb1Pos = primary->nextPos;
		VECTOR obb2Pos = secondary->nextPos;

		// OBBのローカル空間における位置
		VECTOR obb1ToObb2 = VSub(obb2Pos, obb1Pos);

		// OBBのローカル軸の計算
		VECTOR axes[15];
		for (int i = 0; i < 3; ++i)
		{
			axes[i] = VGet(obb1->rotation.m[i][0], obb1->rotation.m[i][1], obb1->rotation.m[i][2]);
			axes[3 + i] = VGet(obb2->rotation.m[i][0], obb2->rotation.m[i][1], obb2->rotation.m[i][2]);
		}
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				axes[6 + i * 3 + j] = VCross(axes[i], axes[3 + j]);
			}
		}

		float minOverlap = FLT_MAX;
		VECTOR bestAxis;
		for (int i = 0; i < 15; ++i)
		{
			VECTOR axis = axes[i];
			VECTOR absAxis = VGet(std::abs(axis.x), std::abs(axis.y), std::abs(axis.z));

			float obb1Projection = obb1->halfSize[0] * absAxis.x + obb1->halfSize[1] * absAxis.y + obb1->halfSize[2] * absAxis.z;
			float obb2Projection = obb2->halfSize[0] * absAxis.x + obb2->halfSize[1] * absAxis.y + obb2->halfSize[2] * absAxis.z;
			float projection = VDot(obb1ToObb2, axis);

			float minProj1 = projection - obb1Projection;
			float maxProj1 = projection + obb1Projection;
			float minProj2 = -obb2Projection;
			float maxProj2 = obb2Projection;

			if (minProj1 > maxProj2 || minProj2 > maxProj1)
			{
				// 軸方向に重なりがない場合、衝突なし
				return;
			}

			float overlap = minProj1 - maxProj2;
			if (minProj2 > maxProj1)
			{
				overlap = minProj2 - maxProj1;
			}

			if (overlap < minOverlap)
			{
				minOverlap = overlap;
				bestAxis = axis;
			}
		}

		// OBBの中心を重なりの最小分離ベクトルに基づいて補正
		if (minOverlap < 0.0f)
		{
			VECTOR correction = VScale(bestAxis, minOverlap + A_LITTLE_EXTRA_RELEASE);
			primary->nextPos = VAdd(obb1Pos, VScale(correction, -0.5f));
			secondary->nextPos = VAdd(obb2Pos, VScale(correction, 0.5f));
		}
	}
	else
	{
		assert(0 && "許可されていない値判定の位置補正だお");
	}
}

/// <summary>
/// 位置の確定
/// </summary>
void TKRLib::Physics::FixPosition()
{
	for (auto& item : collidables)
	{
#if _DEBUG
		//補正後の位置をデバック表示！！
		if (item->colliderData->GetKind() == ColliderData::Kind::Sphere)
		{
			auto itemSphereData = dynamic_cast<ColliderDataSphere*>(item->colliderData);
			DebugDraw::DrawSphere(item->nextPos, itemSphereData->radius, AfterFixInfoColor);
		}
#endif
		//Posを更新するため、Velocityもそこに移動する
		VECTOR toFixedPos = VSub(item->nextPos, item->rigidbody.GetPos());
		item->rigidbody.SetVelocity(toFixedPos);

		//位置の確定
		item->rigidbody.SetPos(item->nextPos);
	}
}

bool TKRLib::Physics::CheckOBBOverlap(const ColliderDataOBB* obbA, const ColliderDataOBB* obbB) const
{
	// OBBの軸
	VECTOR axes[6] = {
		VGet(obbA->rotation.m[0][0], obbA->rotation.m[0][1], obbA->rotation.m[0][2]), // OBB A の x 軸
		VGet(obbA->rotation.m[1][0], obbA->rotation.m[1][1], obbA->rotation.m[1][2]), // OBB A の y 軸
		VGet(obbA->rotation.m[2][0], obbA->rotation.m[2][1], obbA->rotation.m[2][2]), // OBB A の z 軸
		VGet(obbB->rotation.m[0][0], obbB->rotation.m[0][1], obbB->rotation.m[0][2]), // OBB B の x 軸
		VGet(obbB->rotation.m[1][0], obbB->rotation.m[1][1], obbB->rotation.m[1][2]), // OBB B の y 軸
		VGet(obbB->rotation.m[2][0], obbB->rotation.m[2][1], obbB->rotation.m[2][2]), // OBB B の z 軸
	};

	// 各軸に対して分離軸を調べる
	for (int i = 0; i < 6; ++i)
	{
		if (!IsAxisOverlap(obbA, obbB, axes[i]))
		{
			return false; // 分離軸が見つかれば当たっていない
		}
	}

	return true; // すべての軸で分離していなければ当たり
}

bool TKRLib::Physics::IsAxisOverlap(const ColliderDataOBB* obbA, const ColliderDataOBB* obbB, const VECTOR& axis) const
{
	// 軸が無効な場合 (長さがゼロの軸)
	float axisLengthSquared = VDot(axis, axis);
	if (axisLengthSquared < 1e-6f)
	{
		return true; // 無効な軸に対しては重なっているとみなす
	}

	// 軸を正規化
	VECTOR normAxis = VNorm(axis);

	// OBB A の頂点を軸に投影し、最小と最大を取得
	std::vector<VECTOR> verticesA = obbA->GetVertices();
	float minA = VDot(verticesA[0], normAxis);
	float maxA = minA;
	for (const auto& vertex : verticesA)
	{
		float projection = VDot(vertex, normAxis);
		if (projection < minA) minA = projection;
		if (projection > maxA) maxA = projection;
	}

	// OBB B の頂点を軸に投影し、最小と最大を取得
	std::vector<VECTOR> verticesB = obbB->GetVertices();
	float minB = VDot(verticesB[0], normAxis);
	float maxB = minB;
	for (const auto& vertex : verticesB)
	{
		float projection = VDot(vertex, normAxis);
		if (projection < minB) minB = projection;
		if (projection > maxB) maxB = projection;
	}

	// 投影の範囲が重なっているか判定
	if (maxA < minB || maxB < minA)
	{
		return false; // 重なっていない
	}

	return true; // 重なっている
}

bool TKRLib::Physics::CheckOBBSphereCollision(const ColliderDataOBB* obb, const VECTOR& obbPos, const ColliderDataSphere* sphere, const VECTOR& spherePos) const
{
	// 球の中心とOBBの最近接点を見つける
	VECTOR closestPoint = spherePos;

	// OBBの各軸について
	for (int i = 0; i < 3; ++i)
	{
		// OBBの中心から球の中心までのベクトル
		VECTOR axis = VGet(obb->rotation.m[i][0], obb->rotation.m[i][1], obb->rotation.m[i][2]);
		VECTOR obbToSphere = VSub(spherePos, obbPos);
		float distance = VDot(obbToSphere, axis);

		// OBBの半分の長さを超えないように制限
		if (distance > obb->halfSize[i]) distance = obb->halfSize[i];
		if (distance < -obb->halfSize[i]) distance = -obb->halfSize[i];

		// その軸に沿った最近接点を更新
		closestPoint = VAdd(closestPoint, VScale(axis, distance));
	}

	// 球の中心と最近接点の距離を計算
	VECTOR closestToSphere = VSub(closestPoint, spherePos);
	float closestDistanceSq = VDot(closestToSphere, closestToSphere);

	// 衝突判定：距離が球の半径以内なら衝突
	return closestDistanceSq <= sphere->radius * sphere->radius;
}
