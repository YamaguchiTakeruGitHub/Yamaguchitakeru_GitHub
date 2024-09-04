#include "DxLib.h"
#include <cassert>
#include "../TKRLib/Physics.h"


//�����]���ɗ���
#define A_LITTLE_EXTRA_RELEASE 0.0001f

/// <summary>
/// �o�^
/// </summary>
/// <param name="collidable"></param>
void TKRLib::Physics::Entry(Collidable* collidable)
{
	//�o�^
	bool found = (std::find(collidables.begin(), collidables.end(), collidable) != collidables.end());
	if (!found)
	{
		collidables.emplace_back(collidable);
	}
	else//�o�^����Ă�����G���[��f��
	{
		assert(0 && "�w���collidable�͓o�^�ς݂���");
	}
}

/// <summary>
/// �o�^����
/// </summary>
/// <param name="collidable"></param>
void TKRLib::Physics::Exit(Collidable* collidable)
{

	//�o�^�̉���
	bool found = (std::find(collidables.begin(), collidables.end(), collidable) != collidables.end());
	if (found)
	{
		collidables.remove(collidable);
	}
	else//�o�^����ĂȂ�������G���[��f��
	{
		assert(0 && "�w���collidable�͓o�^�ς݂���Ȃ���");
	}
}

/// <summary>
/// �X�V�i�o�^���Ă���obj�̕���������A�Փ˒ʒm�j
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
		//�|�W�V�����̊m��
		//item->rigidbody.SetPos(nextPos);
		item->nextPos = nextPos;
	}

	//�����蔻��̃`�F�b�N
	std::vector<OnCollideInfo> onCollideInfo = CheckColide();

	//�ʒu�̊m��
	FixPosition();

	//�����蔻��̒ʒm
	for (auto& item : onCollideInfo)
	{
		//���L�҂���m�点��
		item.owner->OnCollide(*item.colider);
	}


}

std::vector<TKRLib::Physics::OnCollideInfo> TKRLib::Physics::CheckColide() const
{
	std::vector<TKRLib::Physics::OnCollideInfo> onCollideInfo;

	//�Փ˂����A�|�W�V�����␳
	bool doCheck = true;
	//�`�F�b�N��
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
					//���݂��̋��������a�����������̂�菬������΂�����
					if (IsCollide(objA, objB))
					{
						auto priorityA = objA->GetPriority();
						auto priorityB = objB->GetPriority();

						//�v���C�I���e�B�̍����ق����ړ�
						Collidable* primary = objA;
						Collidable* secondary = objB;
						if (priorityA < priorityB)
						{
							primary = objB;
							secondary = objA;
						}
						FixNextPosition(primary, secondary);

						//�Փ˒ʒm���̍X�V
						bool hasPrimaryInfo = false;
						bool hasSecondaryInfo = false;

						for (const auto& item : onCollideInfo)
						{
							//���łɒʒm���X�g�ɂ�������Ă΂Ȃ�
							if (item.owner == primary)
							{
								hasPrimaryInfo = true;
							}
							if (item.owner == secondary)
							{
								hasSecondaryInfo = true;
							}
						}
						//�ʒm���X�ƂɂȂ��ꍇ
						if (!hasPrimaryInfo)
						{
							//�ʒm�������o��
							onCollideInfo.push_back({ primary, secondary });
						}
						if (!hasSecondaryInfo)
						{
							//��L���l
							onCollideInfo.push_back({ secondary,primary });
						}

						//��x�ł��q�b�g�␳������Փ˔���ƕ␳�̂�蒼��
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
		//�������[�v��h��
		if (checkCount > 1000 && doCheck)
		{
#if _DEBUG
			printfDx("�����蔻��̌J��Ԃ��`�F�b�N���ݒ萔�𒴂��܂���\n");
#endif
			break;
		}

	}
	return onCollideInfo;
}

bool TKRLib::Physics::IsCollide(const Collidable* objA, const Collidable* objB) const
{
	bool isHit = false;

	//collidable�̎�ޕʂœ����蔻��𕪂���
	auto aKind = objA->colliderData->GetKind();
	auto bKind = objB->colliderData->GetKind();

	//���Ƌ��܂��ʂ̓����蔻��ŕ�����
	if (aKind == TKRLib::ColliderData::Kind::Sphere &&
		bKind == TKRLib::ColliderData::Kind::Sphere)
	{
		auto atob = VSub(objB->nextPos, objA->nextPos);
		auto atobLength = VSize(atob);

		//���݂��̋������A���ꂼ��̔��a�𑫂������̂�菬�����ꍇ
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
/// ���̈ʒu�̕␳
/// </summary>
/// <param name="primary"></param>
/// <param name="secondary"></param>
void TKRLib::Physics::FixNextPosition(Collidable* primary, Collidable* secondary) const
{
	auto primaryKind = primary->colliderData->GetKind();
	auto secondaryKind = secondary->colliderData->GetKind();


	//�����m�̈ʒu�␳
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
		assert(0 && "������Ă��Ȃ��l����̈ʒu�␳����");
	}
}

/// <summary>
/// �ʒu�̊m��
/// </summary>
void TKRLib::Physics::FixPosition()
{
	for (auto& item : collidables)
	{
#if _DEBUG
		//�␳��̈ʒu���f�o�b�N�\���I�I
		if (item->colliderData->GetKind() == ColliderData::Kind::Sphere)
		{
			auto itemSphereData = dynamic_cast<ColliderDataSphere*>(item->colliderData);
			DebugDraw::DrawSphere(item->nextPos, itemSphereData->radius, AfterFixInfoColor);
		}
#endif
		//Pos���X�V���邽�߁AVelocity�������Ɉړ�����
		VECTOR toFixedPos = VSub(item->nextPos, item->rigidbody.GetPos());
		item->rigidbody.SetVelocity(toFixedPos);

		//�ʒu�̊m��
		item->rigidbody.SetPos(item->nextPos);
	}
}
