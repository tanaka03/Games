#include "utility.h"
#include "debugproc.h"
#include "application.h"

//��������������������������������������������������������������
// ���[�e�B���e�B�̃R���X�g���N�^
//��������������������������������������������������������������
CUtility::CUtility()
{
}

//��������������������������������������������������������������
// ���[�e�B���e�B�̃f�X�g���N�^
//��������������������������������������������������������������
CUtility::~CUtility()
{
}

//��������������������������������������������������������������
// ���������_�̃����_��
//��������������������������������������������������������������
float CUtility::floatRandam(float fMax, float fMin)
{
	return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
}

float CUtility::easeInOutSine(float anim)
{
	return (cosf(D3DX_PI * anim) - 1) / 2;
}

//��������������������������������������������������������������
// �Փ˔���i�ہj
//��������������������������������������������������������������
bool CUtility::isCircleCollision(const D3DXVECTOR3& pos, float radius, const D3DXVECTOR3& destPos, float destRadius)
{
	D3DXVECTOR3 vec = destPos - pos;
	float distance = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);

	if (distance < radius + destRadius)
	{
		return true;
	}
	return false;
}

//��������������������������������������������������������������
// �Փ˔���i�l�p�j
//��������������������������������������������������������������
bool CUtility::isRectCollision(	const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size, 
								const D3DXVECTOR3& destPos, const D3DXVECTOR3& destSize, const D3DXVECTOR3& destMin, const D3DXVECTOR3& destMax)
{
	const int squareVtxNum = 8;
	const int squareFaceNum = 6;
	const int squareEdgeNum = 12;

	D3DXVECTOR3 extents1 = size * 0.5f;
	D3DXVECTOR3 extents2 = destSize * 0.5f;

	// ���f���̍��������蔻��
	if ((pos.z - extents1.z / 2.0f < destPos.z + destMax.z) &&
		(pos.z + extents1.z > destPos.z + destMin.z) &&
		(posOld.x + extents1.x <= destPos.x + destMin.x / 2.0f) &&
		(pos.x + extents1.x > destPos.x + destMin.x / 2.0f) &&
		(pos.y + size.y > destPos.y - destMax.y / 2.0f) &&
		(pos.y < destPos.y + destMax.y / 2.0f))
	{
		return true;
	}
	// ���f���̉E�������蔻��
	if ((pos.z - extents1.z < destPos.z + destMax.z) &&
		(pos.z + extents1.z > destPos.z + destMin.z) &&
		(posOld.x - extents1.x >= destPos.x + destMax.x / 2.0f) &&
		(pos.x - extents1.x < destPos.x + destMax.x / 2.0f) &&
		(pos.y + size.y > destPos.y - destMax.y / 2.0f) &&
		(pos.y < destPos.y + destMax.y / 2.0f))
	{
		return true;
	}
	// ���f���̉��������蔻��
	if ((pos.x - extents1.x < destPos.x + destMax.x) &&
		(pos.x + extents1.x > destPos.x + destMin.x) &&
		(posOld.z - extents1.z >= destPos.z + destMax.z / 2.0f) &&
		(pos.z - extents1.z < destPos.z + destMax.z / 2.0f) &&
		(pos.y + size.y > destPos.y - destMax.y / 2.0f) &&
		(pos.y < destPos.y + destMax.y / 2.0f))
	{
		return true;
	}
	// ���f���̎�O�������蔻��
	if ((pos.x - extents1.x < destPos.x + destMax.x) &&
		(pos.x + extents1.x > destPos.x + destMin.x) &&
		(posOld.z + extents1.z <= destPos.z + destMin.z / 2.0f) &&
		(pos.z + extents1.z > destPos.z + destMin.z / 2.0f) &&
		(pos.y + size.y > destPos.y - destMax.y / 2.0f) &&
		(pos.y < destPos.y + destMax.y / 2.0f))
	{
		return true;
	}

	return false;
}

//��������������������������������������������������������������
// �Փ˔���i�O�ρj
//��������������������������������������������������������������
bool CUtility::isCrossCollision(const D3DXVECTOR3& pos, const D3DXVECTOR3& minSize, const D3DXVECTOR3& maxSize, const D3DXMATRIX& mtxWorld)
{
	D3DXVECTOR3 min = minSize;
	D3DXVECTOR3 max = maxSize;

	D3DXVECTOR3 worldPos[4];
	D3DXVECTOR3 vec[4];
	D3DXVECTOR3 edge[4];
	float cross[4];

	D3DXVECTOR3 pt[4] = {
		D3DXVECTOR3(min.x, min.y, min.z),
		D3DXVECTOR3(max.x, min.y, min.z),
		D3DXVECTOR3(max.x, min.y, max.z),
		D3DXVECTOR3(min.x, min.y, max.z)
	};

	for (int i = 0; i < 4; i++)
	{
		// ���[���h���W���v�Z
		D3DXVec3TransformCoord(&worldPos[i], &pt[i], &mtxWorld);

		// �^�[�Q�b�g�̈ʒu�Ƃ̃x�N�g��
		vec[i] = pos - worldPos[i];
	}

	// �e���_�̃x�N�g��
	edge[0] = worldPos[1] - worldPos[0];
	edge[1] = worldPos[2] - worldPos[1];
	edge[2] = worldPos[3] - worldPos[2];
	edge[3] = worldPos[0] - worldPos[3];

	// �񎟌��O��
	cross[0] = CUtility::Vec2Cross(&edge[0], &vec[0]);
	cross[1] = CUtility::Vec2Cross(&edge[1], &vec[1]);
	cross[2] = CUtility::Vec2Cross(&edge[2], &vec[2]);
	cross[3] = CUtility::Vec2Cross(&edge[3], &vec[3]);

	if (cross[0] * cross[1] >= 0 &&
		cross[1] * cross[2] >= 0 &&
		cross[2] * cross[3] >= 0 &&
		cross[3] * cross[0] >= 0)
	{
		return true;
	}

	return false;
}

//��������������������������������������������������������������
// �p�x�̐��K��
//��������������������������������������������������������������
void CUtility::angleNormalize(float& angle)
{
	if (angle > D3DX_PI)
	{
		angle = angle - D3DX_PI * 2;
	}
	else if (angle < -D3DX_PI)
	{
		angle = angle + D3DX_PI * 2;
	}
}

//��������������������������������������������������������������
// �񎟌��O�όv�Z
//��������������������������������������������������������������
float CUtility::Vec2Cross(D3DXVECTOR3* vec1, D3DXVECTOR3* vec2)
{
	return vec1->x * vec2->z - vec1->z * vec2->x;
}

//��������������������������������������������������������������
// ��s�ŕ����̕������v�b�V�������������̏���
//��������������������������������������������������������������
void CUtility::stringMultiPush(std::vector<std::string>& list, std::string prop)
{
	int cntProp = 0;
	list.resize(cntProp + 1);

	for (char &p : prop)
	{
		if (p == ',')
		{
			cntProp++;
			list.resize(cntProp + 1);
			continue;
		}

		if (p == ' ')
		{
			continue;
		}

		list[cntProp].push_back(p);
	}
}
