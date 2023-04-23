//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "objectX.h"
#include "renderer.h"
#include "application.h"
#include "main.h"
#include "objectX_group.h"
#include "texture.h"
#include "light.h"
#include "mode.h"
#include "game.h"
#include "object2d.h"

#include "depthbuffershadow.h"
#include "lambert.h"
#include "shadow.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObjectX::CObjectX(int nPriority) :
	CObject(nPriority),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f, 0.0f))
{
		SetObjState(CObject::OBJSTATE_3D);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectX::~CObjectX()
{
}

//=============================================================================
// �I�u�W�F�N�g�̏�����
//=============================================================================
HRESULT CObjectX::Init()
{
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�̏I��
//=============================================================================
void CObjectX::Uninit()
{
	//�C���X�^���X�̉������
	Destroy();
}

//=============================================================================
// �I�u�W�F�N�g�̍X�V
//=============================================================================
void CObjectX::Update()
{
}

//=============================================================================
// �I�u�W�F�N�g�̕`��
//=============================================================================
void CObjectX::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ���C�g�̃|�C���^���擾
	CLight* pLight = CApplication::GetInstance()->GetMode()->GetGame()->GetLight();

	CShadow *pShadow = CApplication::GetInstance()->GetMode()->GetGame()->GetShadow();
	CLambert *pLambert = CApplication::GetInstance()->GetMode()->GetGame()->GetLambert();
	CDepthBufferShadow *pDepthBuffShadow = CApplication::GetInstance()->GetMode()->GetGame()->GetDepthBuffShadow();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);	//(���s��ړ��֐�(��1������x,y,z�����̈ړ��s����쐬))
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMtxWorld();

		// �s��|���Z�֐�
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	}

	//���[���h�}�g���b�N�X�̐ݒ�i���[���h���W�s��̐ݒ�j
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �[�x�e�N�X�`���X�V
	//pShadow->StartViewfromLight();
	//D3DXMATRIX wvp = pShadow->GetWVP();

	//pLambert->Begin();
	////pLambert->SetMatrix(&wvp);

	//for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	//{
	//	pDevice->SetTexture(0, NULL);

	//	pLambert->BeginPass(0);

	//	pLambert->SetMatrix(&pShadow->GetWVP());

	//	//���f���p�[�c�̕`��
	//	m_pMesh->DrawSubset(nCntMat);

	//	pLambert->EndPass();
	//}

	//pLambert->End();
	//pShadow->EndViewfromLight();

	// �f�v�X�o�b�t�@�T�[�t�F�C�X���Q�Ƃ��A�I�u�W�F�N�g�Ɖe�������_�����O����
	// �f�v�X�o�b�t�@�T�[�t�F�C�X�̃e�N�X�`���[���T���v���ԍ�1�ɃZ�b�g����
	//pDevice->SetTexture(1, pShadow->GetZBufferTexture());

	//pDepthBuffShadow->SetBias(0.005f);
	//pDepthBuffShadow->SetShadowColor(0.3f);
	//pDepthBuffShadow->SetAmbient(0.3f);
	//pDepthBuffShadow->Begin();
	//pDepthBuffShadow->SetMatrix(&m_mtxWorld, &pShadow->GetWVP(), &pLight->GetVecDir());

	pDevice->SetTexture(0, NULL);

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		/*pDepthBuffShadow->SetDiffuse(D3DXVECTOR4(pMat[nCntMat].MatD3D.Diffuse.r, pMat[nCntMat].MatD3D.Diffuse.g, pMat[nCntMat].MatD3D.Diffuse.b, pMat[nCntMat].MatD3D.Diffuse.a));
		pDepthBuffShadow->BeginPass(0);*/

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);

		//pDepthBuffShadow->EndPass();
	}

	pDepthBuffShadow->End();

	// �ݒ肵�Ă����[�x�e�N�X�`����j��
	pDevice->SetTexture(1, NULL);

	//�ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

void CObjectX::Draw(D3DXMATRIX mtxParent)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ���C�g�̃|�C���^���擾
	CLight* pLight = CApplication::GetInstance()->GetMode()->GetGame()->GetLight();

	CShadow *pShadow = CApplication::GetInstance()->GetMode()->GetGame()->GetShadow();
	CLambert *pLambert = CApplication::GetInstance()->GetMode()->GetGame()->GetLambert();
	CDepthBufferShadow *pDepthBuffShadow = CApplication::GetInstance()->GetMode()->GetGame()->GetDepthBuffShadow();

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

	// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// �s���]�֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				// �s��|���Z�֐� 

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		// �s��ړ��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);			// �s��|���Z�֐�

	// �s��|���Z�֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture = CApplication::GetInstance()->GetTexture();

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �[�x�e�N�X�`���X�V
	//pShadow->StartViewfromLight();
	//D3DXMATRIX wvp = pShadow->GetWVP();

	//pLambert->Begin();
	//pLambert->SetMatrix(&wvp);

	//for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	//{
	//	pDevice->SetTexture(0, NULL);
	//	
	//	pLambert->BeginPass(0);

	//	pLambert->SetMatrix(&pShadow->GetWVP());

	//	//���f���p�[�c�̕`��
	//	m_pMesh->DrawSubset(nCntMat);

	//	pLambert->EndPass();
	//}

	//pLambert->End();
	//pShadow->EndViewfromLight();

	// �f�v�X�o�b�t�@�T�[�t�F�C�X���Q�Ƃ��A�I�u�W�F�N�g�Ɖe�������_�����O����
	// �f�v�X�o�b�t�@�T�[�t�F�C�X�̃e�N�X�`���[���T���v���ԍ�1�ɃZ�b�g����
	//pDevice->SetTexture(1, pShadow->GetZBufferTexture());

	//pDepthBuffShadow->SetBias(0.005f);
	//pDepthBuffShadow->SetShadowColor(0.3f);
	//pDepthBuffShadow->SetAmbient(0.3f);
	//pDepthBuffShadow->Begin();

	//pDepthBuffShadow->SetMatrix(&m_mtxWorld, &pShadow->GetWVP(), &pLight->GetVecDir());

	pDevice->SetTexture(0, NULL);

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//pDepthBuffShadow->SetDiffuse(D3DXVECTOR4(pMat[nCntMat].MatD3D.Diffuse.r, pMat[nCntMat].MatD3D.Diffuse.g, pMat[nCntMat].MatD3D.Diffuse.b, pMat[nCntMat].MatD3D.Diffuse.a));
		//pDepthBuffShadow->BeginPass(0);

		// ���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);

		//pDepthBuffShadow->EndPass();

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, nullptr);
	}

	//pDepthBuffShadow->End();

	// �ݒ肵�Ă����[�x�e�N�X�`����j��
	pDevice->SetTexture(1, NULL);

	// �ێ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// ���_�ő召�l�̌v�Z����
//=============================================================================
void CObjectX::CalculationVtx()
{
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;

	D3DXMatrixIdentity(&mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// �s���]�֐�
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);					// �s��|���Z�֐�

	D3DXVec3TransformCoord(&m_MaxVtx, &m_MaxVtx, &mtxWorld);
	D3DXVec3TransformCoord(&m_MinVtx, &m_MinVtx, &mtxWorld);


	if (m_MaxVtx.x < m_MinVtx.x)
	{
		float change = m_MaxVtx.x;
		m_MaxVtx.x = m_MinVtx.x;
		m_MinVtx.x = change;
	}

	if (m_MaxVtx.y < m_MinVtx.y)
	{
		float change = m_MaxVtx.y;
		m_MaxVtx.y = m_MinVtx.y;
		m_MinVtx.y = change;
	}

	if (m_MaxVtx.z < m_MinVtx.z)
	{
		float change = m_MaxVtx.z;
		m_MaxVtx.z = m_MinVtx.z;
		m_MinVtx.z = change;
	}
}

//=============================================================================
// ���W�ݒ�֐�
//=============================================================================
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �T�C�Y�ݒ�֐�
//=============================================================================
void CObjectX::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// �ړ��͐ݒ�֐�
//=============================================================================
void CObjectX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �F�ݒ�֐�
//=============================================================================
void CObjectX::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// �����ݒ�֐�
//=============================================================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// ��������
//=============================================================================
CObjectX * CObjectX::Create(D3DXVECTOR3 pos, int nPriority)
{
	//�|�C���^�錾
	CObjectX *pObjectX = nullptr;

	//�C���X�^���X����
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{//�|�C���^�����݂�������s
		pObjectX->Init();
		pObjectX->SetPos(pos);
		pObjectX->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{//�|�C���^����������������s
		assert(false);
	}

	//�|�C���^��Ԃ�
	return pObjectX;
}

//=============================================================================
// ���f���̓ǂݍ���
//=============================================================================
void CObjectX::LoadModel(const char *aFileName)
{
	CObjectXGroup *xGroup = CApplication::GetInstance()->GetObjectXGroup();
	m_pBuffMat = xGroup->GetBuffMat(aFileName);
	m_MaxVtx = xGroup->GetMaxVtx(aFileName);
	m_pMesh = xGroup->GetMesh(aFileName);
	m_MinVtx = xGroup->GetMinVtx(aFileName);
	m_NumMat = xGroup->GetNumMat(aFileName);
	m_size = xGroup->GetSize(aFileName);
}

//=============================================================================
// �����蔻�� (���E,��,��O)
//=============================================================================
bool CObjectX::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize)
{
	if (!m_isCollision)
	{
		return false;
	}

	// �ϐ��錾
	bool bIsLanding = false;

	// ���f���̍��������蔻��
	if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
		(pPosOld->x + pSize->x / 2.0f <= m_pos.x + m_MinVtx.x / 2.0f) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x / 2.0f) &&
		(pPos->y + pSize->y > m_pos.y - m_MaxVtx.y / 2.0f) &&
		(pPos->y < m_pos.y + m_MaxVtx.y / 2.0f))
	{
		bIsLanding = true;
		pPos->x = m_pos.x + m_MinVtx.x / 2.0f - pSize->x / 2.0f;
	}
	// ���f���̉E�������蔻��
	if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
		(pPosOld->x - pSize->x / 2.0f >= m_pos.x + m_MaxVtx.x / 2.0f) &&
		(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x / 2.0f) &&
		(pPos->y + pSize->y > m_pos.y - m_MaxVtx.y / 2.0f) &&
		(pPos->y < m_pos.y + m_MaxVtx.y / 2.0f))
	{
		bIsLanding = true;
		pPos->x = m_pos.x + m_MaxVtx.x / 2.0f + pSize->x / 2.0f;
	}
	// ���f���̉��������蔻��
	if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
		(pPosOld->z - pSize->z / 2.0f >= m_pos.z + m_MaxVtx.z / 2.0f) &&
		(pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z / 2.0f) &&
		(pPos->y + pSize->y > m_pos.y - m_MaxVtx.y / 2.0f) &&
		(pPos->y < m_pos.y + m_MaxVtx.y / 2.0f))
	{
		bIsLanding = true;
		pPos->z = m_pos.z + m_MaxVtx.z / 2.0f + pSize->z / 2.0f;
	}
	// ���f���̎�O�������蔻��
	if ((pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
		(pPosOld->z + pSize->z / 2.0f <= m_pos.z + m_MinVtx.z / 2.0f) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z / 2.0f) &&
		(pPos->y + pSize->y > m_pos.y - m_MaxVtx.y / 2.0f) &&
		(pPos->y < m_pos.y + m_MaxVtx.y / 2.0f))
	{
		bIsLanding = true;
		pPos->z = m_pos.z + m_MinVtx.z / 2.0f - pSize->z / 2.0f;
	}

	// �l��Ԃ�
	return bIsLanding;
}

//=============================================================================
// �����蔻�� (���E,��,��O)
//=============================================================================
bool CObjectX::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * inMaxVtx, D3DXVECTOR3 * inMinVtx)
{
	if (!m_isCollision)
	{
		return false;
	}

	// �ϐ��錾
	bool bIsLanding = false;

	// ���f���̏��グ����
	if ((pPos->y + 20.0f > m_pos.y + m_MaxVtx.y))
	{
		return bIsLanding;
	}

	// ���f���̍��������蔻��
	if ((pPos->z + inMinVtx->z < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + inMaxVtx->z > m_pos.z + m_MinVtx.z) &&
		(pPosOld->x + inMaxVtx->x <= m_pos.x + m_MinVtx.x) &&
		(pPos->x + inMaxVtx->x > m_pos.x + m_MinVtx.x) &&
		(pPos->y + inMaxVtx->y > m_pos.y + m_MinVtx.y) &&
		(pPos->y < m_pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->x = m_pos.x + m_MinVtx.x + inMinVtx->x - 5.0f;
	}

	// ���f���̉E�������蔻��
	if ((pPos->z + inMinVtx->z < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + inMaxVtx->z > m_pos.z + m_MinVtx.z) &&
		(pPosOld->x + inMinVtx->x >= m_pos.x + m_MaxVtx.x) &&
		(pPos->x + inMinVtx->x < m_pos.x + m_MaxVtx.x) &&
		(pPos->y + inMaxVtx->y > m_pos.y + m_MinVtx.y) &&
		(pPos->y < m_pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->x = m_pos.x + m_MaxVtx.x + inMaxVtx->x;
		pPos->x -= 0.1f;
	}

	// ���f���̉��������蔻��
	if ((pPos->x + inMinVtx->x < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + inMaxVtx->x > m_pos.x + m_MinVtx.x) &&
		(pPosOld->z + inMinVtx->z >= m_pos.z + m_MaxVtx.z) &&
		(pPos->z + inMinVtx->z < m_pos.z + m_MaxVtx.z) &&
		(pPos->y + inMaxVtx->y > m_pos.y + m_MinVtx.y) &&
		(pPos->y < m_pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->z = m_pos.z + m_MaxVtx.z + inMaxVtx->z;
	}

	// ���f���̎�O�������蔻��
	if ((pPos->x + inMinVtx->x < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + inMaxVtx->x > m_pos.x + m_MinVtx.x) &&
		(pPosOld->z + inMaxVtx->z <= m_pos.z + m_MinVtx.z) &&
		(pPos->z + inMaxVtx->z > m_pos.z + m_MinVtx.z) &&
		(pPos->y + inMaxVtx->y > m_pos.y + m_MinVtx.y) &&
		(pPos->y < m_pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->z = m_pos.z + m_MinVtx.z + inMinVtx->z - 5.0f;
		pPos->z -= 0.1f;
	}

	// �l��Ԃ�
	return bIsLanding;
}

//=============================================================================
// �����蔻�� (�㑤)
//=============================================================================
bool CObjectX::UpCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, D3DXVECTOR3 * pMove)
{
	if (!m_isCollision)
	{
		return false;
	}

	// �ϐ��錾
	bool bIsLanding = false;

	// ���f���̏㑤�����蔻��
	if ((pPos->z - pSize->z / 2.0f < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + pSize->z / 2.0f > m_pos.z + m_MinVtx.z) &&
		(pPos->x - pSize->x / 2.0f < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + pSize->x / 2.0f > m_pos.x + m_MinVtx.x) &&
		(pPos->y <= m_pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->y = m_pos.y + m_MaxVtx.y;
		if (pPos->y == pPosOld->y)
		{
			pMove->y = 0.0f;
		}
	}

	// �l��Ԃ�
	return bIsLanding;
}

bool CObjectX::UpCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * inMaxVtx, D3DXVECTOR3 * inMinVtx, D3DXVECTOR3 * pMove)
{
	if (!m_isCollision)
	{
		return false;
	}

	// �ϐ��錾
	bool bIsLanding = false;

	// ���f���̏㑤�����蔻��
	if ((pPos->z + inMinVtx->z < m_pos.z + m_MaxVtx.z) &&
		(pPos->z + inMaxVtx->z > m_pos.z + m_MinVtx.z) &&
		(pPos->x + inMinVtx->x < m_pos.x + m_MaxVtx.x) &&
		(pPos->x + inMaxVtx->x > m_pos.x + m_MinVtx.x) &&
		(pPos->y <= m_pos.y + m_MaxVtx.y))
	{
		bIsLanding = true;
		pPos->y = m_pos.y + m_MaxVtx.y;
		if (pPos->y == pPosOld->y)
		{
			pMove->y = 0.0f;
		}
	}

	// �l��Ԃ�
	return bIsLanding;
}

//=============================================================================
// ���_�ő�l�ݒ菈��
//=============================================================================
void CObjectX::SetMaxVtx(D3DXVECTOR3 Maxvtx)
{
	m_MaxVtx = Maxvtx;
}

//=============================================================================
// ���_�ŏ��l�ݒ菈��
//=============================================================================
void CObjectX::SetMinVtx(D3DXVECTOR3 Minvtx)
{
	m_MinVtx = Minvtx;
}
