//=============================================================================
//
// ���[�V�����L�����N�^�[3D�N���X(model3D.h)
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�������s��
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <assert.h>

#include "motion_model3D.h"
#include "motion.h"
#include "renderer.h"
#include "application.h"
#include "objectX.h"
#include "parts.h"

//=============================================================================
// �C���X�^���X����
// Author : �������l
// �T�v : ���[�V�����L�����N�^�[3D�𐶐�����
//=============================================================================
CMotionModel3D * CMotionModel3D::Create()
{
	// �I�u�W�F�N�g�C���X�^���X
	CMotionModel3D *pMotionModel3D = nullptr;

	// �������̉��
	pMotionModel3D = new CMotionModel3D;

	// �������̊m�ۂ��ł��Ȃ�����
	assert(pMotionModel3D != nullptr);

	// ���l�̏�����
	pMotionModel3D->Init();

	// �C���X�^���X��Ԃ�
	return pMotionModel3D;
}

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CMotionModel3D::CMotionModel3D() :
	m_pMotion(nullptr),		// ���[�V�������
	m_mtxWorld(D3DXMATRIX()),									// ���[���h�}�g���b�N�X
	m_pos(D3DXVECTOR3()),										// �ʒu
	m_rot(D3DXVECTOR3()),										// ����
	m_size(D3DXVECTOR3()),										// �傫��
	m_isUpdateStop(false)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CMotionModel3D::~CMotionModel3D()
{
	assert(m_pMotion == nullptr);
}

//=============================================================================
// ������
// Author : �������l
// �T�v : ���_�o�b�t�@�𐶐����A�����o�ϐ��̏����l��ݒ�
//=============================================================================
HRESULT CMotionModel3D::Init()
{
	// �ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����

	return E_NOTIMPL;
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �e�N�X�`���̃|�C���^�ƒ��_�o�b�t�@�̉��
//=============================================================================
void CMotionModel3D::Uninit()
{
	if (m_pMotion != nullptr)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// �I�u�W�F�N�g2D�̉��
	Destroy();
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : 2D�X�V���s��
//=============================================================================
void CMotionModel3D::Update()
{
	if (m_pMotion != nullptr)
	{// ���[�V�����ԍ��̐ݒ�
		if (!m_isUpdateStop)
		{
			m_pMotion->Update();
		}
	}
}

//=============================================================================
// ���[�V�����̐ݒ�
// Author : �������l
// �T�v : ���[�V�����̓ǂݍ��݂��s��
//=============================================================================
void CMotionModel3D::SetMotion(const char * pName)
{
	if (m_pMotion != nullptr)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// ���[�V�������
	m_pMotion = new CMotion(pName);
	assert(m_pMotion != nullptr);

	// ���[�V�����̏����ݒ�
	m_pMotion->SetMotion(0);

	// ���[�V�����ԍ��̐ݒ�
	m_pMotion->SetNumMotion(0);

	SetMaxMinVtx();
}

void CMotionModel3D::SetMaxMinVtx()
{

	D3DXVECTOR3 minVtx(FLT_MAX, FLT_MAX, FLT_MAX);
	D3DXVECTOR3 maxVtx(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int nCntParts = 0; nCntParts < m_pMotion->GetMaxParts(); nCntParts++)
	{
		D3DXVECTOR3 partsMinVtx = m_pMotion->GetParts(nCntParts)->GetMinVtx();
		D3DXVECTOR3 partsMaxVtx = m_pMotion->GetParts(nCntParts)->GetMaxVtx();

		//X
		if (partsMinVtx.x < minVtx.x)
		{//�ŏ��l
			minVtx.x = partsMinVtx.x;
		}
		if (partsMaxVtx.x > maxVtx.x)
		{//�ő�l
			maxVtx.x = partsMaxVtx.x;
		}

		//Y
		if (partsMinVtx.y < minVtx.y)
		{//�ŏ��l
			minVtx.y = partsMinVtx.y;
		}
		if (partsMaxVtx.y > maxVtx.y)
		{//�ő�l
			maxVtx.y = partsMaxVtx.y;
		}

		//Z
		if (partsMinVtx.z < minVtx.z)
		{//�ŏ��l
			minVtx.z = partsMinVtx.z;
		}
		if (partsMaxVtx.z > maxVtx.z)
		{//�ő�l
			maxVtx.z = partsMaxVtx.z;
		}
	}

	m_MinVtx = minVtx;
	m_MaxVtx = maxVtx;
}

float CMotionModel3D::LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	float r1 = fabs(D3DXVec3Dot(Sep, e1));
	float r2 = fabs(D3DXVec3Dot(Sep, e2));
	float r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
	return r1 + r2 + r3;
}
