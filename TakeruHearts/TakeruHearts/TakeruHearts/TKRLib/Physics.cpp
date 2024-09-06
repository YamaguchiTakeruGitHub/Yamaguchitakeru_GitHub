#include "DxLib.h"
#include "../TKRLib/Physics.h"
#include <cassert>
#include <cmath>
#include <array>


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
		//auto velocity = item->rigidbody.GetVelocity();

		//// �d�͂𗘗p����ݒ�Ȃ�A�d�͂�ǉ�����

		//if (item->rigidbody.UseGravity())
		//{
		//	velocity = VAdd(velocity, VGet(0, Gravity, 0));

		//	// �ő�d�͉����x���傫��������N�����v
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
	else if (aKind == ColliderData::Kind::Box && bKind == ColliderData::Kind::Box)
	{
		// OBB���m�̓����蔻�� (Separating Axis Theorem, SAT ���g��)
		auto obbA = dynamic_cast<ColliderDataOBB*>(objA->colliderData);
		auto obbB = dynamic_cast<ColliderDataOBB*>(objB->colliderData);
		isHit = CheckOBBOverlap(obbA, obbB);
	}
	else if (aKind == ColliderData::Kind::Box && bKind == ColliderData::Kind::Sphere)
	{
		// OBB vs Sphere ����
		auto obb = dynamic_cast<ColliderDataOBB*>(objA->colliderData);
		auto sphere = dynamic_cast<ColliderDataSphere*>(objB->colliderData);
		isHit = CheckOBBSphereCollision(obb, objA->nextPos, sphere, objB->nextPos);
	}
	else if (aKind == ColliderData::Kind::Sphere && bKind == ColliderData::Kind::Box)
	{
		// Sphere vs OBB ����i�������t�ɂ��ď����j
		auto sphere = dynamic_cast<ColliderDataSphere*>(objA->colliderData);
		auto obb = dynamic_cast<ColliderDataOBB*>(objB->colliderData);
		isHit = CheckOBBSphereCollision(obb, objB->nextPos, sphere, objA->nextPos);
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
	else if (primaryKind == ColliderData::Kind::Box && secondaryKind == ColliderData::Kind::Sphere)
	{
		// OBB vs Sphere �̈ʒu�␳
		auto obb = dynamic_cast<ColliderDataOBB*>(primary->colliderData);
		auto sphere = dynamic_cast<ColliderDataSphere*>(secondary->colliderData);

		VECTOR obbPos = primary->nextPos;
		VECTOR spherePos = secondary->nextPos;

		// OBB�̍ŋߐړ_��������
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

		// ����OBB�̊O���ɉ����o��
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
		// OBB vs OBB �̈ʒu�␳
		auto obb1 = dynamic_cast<ColliderDataOBB*>(primary->colliderData);
		auto obb2 = dynamic_cast<ColliderDataOBB*>(secondary->colliderData);

		// OBB�̒��S�ʒu
		VECTOR obb1Pos = primary->nextPos;
		VECTOR obb2Pos = secondary->nextPos;

		// OBB�̃��[�J����Ԃɂ�����ʒu
		VECTOR obb1ToObb2 = VSub(obb2Pos, obb1Pos);

		// OBB�̃��[�J�����̌v�Z
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
				// �������ɏd�Ȃ肪�Ȃ��ꍇ�A�Փ˂Ȃ�
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

		// OBB�̒��S���d�Ȃ�̍ŏ������x�N�g���Ɋ�Â��ĕ␳
		if (minOverlap < 0.0f)
		{
			VECTOR correction = VScale(bestAxis, minOverlap + A_LITTLE_EXTRA_RELEASE);
			primary->nextPos = VAdd(obb1Pos, VScale(correction, -0.5f));
			secondary->nextPos = VAdd(obb2Pos, VScale(correction, 0.5f));
		}
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

bool TKRLib::Physics::CheckOBBOverlap(const ColliderDataOBB* obbA, const ColliderDataOBB* obbB) const
{
	// OBB�̎�
	VECTOR axes[6] = {
		VGet(obbA->rotation.m[0][0], obbA->rotation.m[0][1], obbA->rotation.m[0][2]), // OBB A �� x ��
		VGet(obbA->rotation.m[1][0], obbA->rotation.m[1][1], obbA->rotation.m[1][2]), // OBB A �� y ��
		VGet(obbA->rotation.m[2][0], obbA->rotation.m[2][1], obbA->rotation.m[2][2]), // OBB A �� z ��
		VGet(obbB->rotation.m[0][0], obbB->rotation.m[0][1], obbB->rotation.m[0][2]), // OBB B �� x ��
		VGet(obbB->rotation.m[1][0], obbB->rotation.m[1][1], obbB->rotation.m[1][2]), // OBB B �� y ��
		VGet(obbB->rotation.m[2][0], obbB->rotation.m[2][1], obbB->rotation.m[2][2]), // OBB B �� z ��
	};

	// �e���ɑ΂��ĕ������𒲂ׂ�
	for (int i = 0; i < 6; ++i)
	{
		if (!IsAxisOverlap(obbA, obbB, axes[i]))
		{
			return false; // ��������������Γ������Ă��Ȃ�
		}
	}

	return true; // ���ׂĂ̎��ŕ������Ă��Ȃ���Γ�����
}

bool TKRLib::Physics::IsAxisOverlap(const ColliderDataOBB* obbA, const ColliderDataOBB* obbB, const VECTOR& axis) const
{
	// ���������ȏꍇ (�������[���̎�)
	float axisLengthSquared = VDot(axis, axis);
	if (axisLengthSquared < 1e-6f)
	{
		return true; // �����Ȏ��ɑ΂��Ă͏d�Ȃ��Ă���Ƃ݂Ȃ�
	}

	// ���𐳋K��
	VECTOR normAxis = VNorm(axis);

	// OBB A �̒��_�����ɓ��e���A�ŏ��ƍő���擾
	std::vector<VECTOR> verticesA = obbA->GetVertices();
	float minA = VDot(verticesA[0], normAxis);
	float maxA = minA;
	for (const auto& vertex : verticesA)
	{
		float projection = VDot(vertex, normAxis);
		if (projection < minA) minA = projection;
		if (projection > maxA) maxA = projection;
	}

	// OBB B �̒��_�����ɓ��e���A�ŏ��ƍő���擾
	std::vector<VECTOR> verticesB = obbB->GetVertices();
	float minB = VDot(verticesB[0], normAxis);
	float maxB = minB;
	for (const auto& vertex : verticesB)
	{
		float projection = VDot(vertex, normAxis);
		if (projection < minB) minB = projection;
		if (projection > maxB) maxB = projection;
	}

	// ���e�͈̔͂��d�Ȃ��Ă��邩����
	if (maxA < minB || maxB < minA)
	{
		return false; // �d�Ȃ��Ă��Ȃ�
	}

	return true; // �d�Ȃ��Ă���
}

bool TKRLib::Physics::CheckOBBSphereCollision(const ColliderDataOBB* obb, const VECTOR& obbPos, const ColliderDataSphere* sphere, const VECTOR& spherePos) const
{
	// ���̒��S��OBB�̍ŋߐړ_��������
	VECTOR closestPoint = spherePos;

	// OBB�̊e���ɂ���
	for (int i = 0; i < 3; ++i)
	{
		// OBB�̒��S���狅�̒��S�܂ł̃x�N�g��
		VECTOR axis = VGet(obb->rotation.m[i][0], obb->rotation.m[i][1], obb->rotation.m[i][2]);
		VECTOR obbToSphere = VSub(spherePos, obbPos);
		float distance = VDot(obbToSphere, axis);

		// OBB�̔����̒����𒴂��Ȃ��悤�ɐ���
		if (distance > obb->halfSize[i]) distance = obb->halfSize[i];
		if (distance < -obb->halfSize[i]) distance = -obb->halfSize[i];

		// ���̎��ɉ������ŋߐړ_���X�V
		closestPoint = VAdd(closestPoint, VScale(axis, distance));
	}

	// ���̒��S�ƍŋߐړ_�̋������v�Z
	VECTOR closestToSphere = VSub(closestPoint, spherePos);
	float closestDistanceSq = VDot(closestToSphere, closestToSphere);

	// �Փ˔���F���������̔��a�ȓ��Ȃ�Փ�
	return closestDistanceSq <= sphere->radius * sphere->radius;
}
