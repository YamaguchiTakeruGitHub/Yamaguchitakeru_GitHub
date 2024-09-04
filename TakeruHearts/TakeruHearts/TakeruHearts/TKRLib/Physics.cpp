#include "DxLib.h"
#include <cassert>
#include "../TKRLib/Physics.h"


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
		auto nextPos = VAdd(pos, item->rigidbody.GetVelocity());
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
	else
	if (aKind == TKRLib::ColliderData::Kind::Box && bKind == TKRLib::ColliderData::Kind::Box)
	{
		auto objAColliderData = dynamic_cast<ColliderDataBox*>(objA->colliderData);
		auto objBColliderData = dynamic_cast<ColliderDataBox*>(objB->colliderData);
	
		//isHit = CheckOBBCollision3D()
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
	else
	if (primaryKind == ColliderData::Kind::Box && secondaryKind == ColliderData::Kind::Box)
	{
		
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
