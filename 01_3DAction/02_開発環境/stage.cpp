#include "object3d.h"
#include "application.h"
#include "light.h"
#include "model.h"
#include "utility.h"
#include "game.h"
#include "stage.h"
#include "player.h"
#include "debugproc.h"
#include "enemy.h"
#include "camera.h"
#include "keyboard.h"

#include "parts.h"
#include "motion.h"
#include "object2d.h"
#include "meshfield.h"

#include "shadow.h"
#include "depthbuffershadow.h"
#include "lambert.h"

//��������������������������������������������������������������
// �X�e�[�W�̃R���X�g���N�^
//��������������������������������������������������������������
CStage::CStage() :
	m_bCollision(false)
{
	SetObjType(OBJTYPE_STAGE);
}

//��������������������������������������������������������������
// �X�e�[�W�̃f�X�g���N�^
//��������������������������������������������������������������
CStage::~CStage()
{
}

//��������������������������������������������������������������
// �X�e�[�W�̐���
//��������������������������������������������������������������
CStage * CStage::Create(D3DXVECTOR3 pos)
{
	CStage *pStage = nullptr;
	pStage = new CStage;

	//�k���`�F�b�N
	if (pStage != nullptr)
	{
		// �|���S���̏���������
		pStage->SetPos(pos);
		pStage->Init();
	}

	return pStage;
}

//��������������������������������������������������������������
// �X�e�[�W�̏�����
//��������������������������������������������������������������
HRESULT CStage::Init()
{
	LoadModel("STAGE_COASTLANDS");

	return S_OK;
}

//��������������������������������������������������������������
// �X�e�[�W�̏I��
//��������������������������������������������������������������
void CStage::Uninit()
{
	//���f���f�[�^���󂶂�Ȃ��ꍇ
	if (!m_modelData.empty())
	{
		m_modelData.clear();
	}

	Destroy();
}

//��������������������������������������������������������������
// �X�e�[�W�̍X�V
//��������������������������������������������������������������
void CStage::Update()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	D3DXVECTOR3 posOld = m_objpos;

	// �v���C���[�ƓG�̓����蔻��
	CObject *pObject = CObject::GetTop(PRIORITY_THIRD);
	while (pObject != nullptr)
	{
		if (pObject == this)
		{
			pObject = pObject->GetNext();
			continue;
		}

		// �I�u�W�F�N�g�̃^�C�v���擾
		CObject::EObjType objType = pObject->GetObjType();
		m_bPlayer = false;

		// �I�u�W�F�N�g�^�C�v���v���C���[�̏ꍇ
		if (objType == OBJTYPE_PLAYER)
		{
			m_bPlayer = true;
			CPlayer *pObj = (CPlayer*)pObject;
			CPlayer::SModelData playerModelData = *pObj->GetModelData(0);
			D3DXVECTOR3 pos = pObj->GetPos();

			for (size_t i = 0; i < m_modelData.size(); i++)
			{
				float hitDistance = 0;
				bool overRange = false;
				m_bCollision = false;

				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(0.0f, -1.0f, 0.0f), (playerModelData.m_maxModel.y + playerModelData.m_minModel.y) * 0.5f, hitDistance))
				{	// ���݂̃v���C���[�̈ʒu���牺�ւ̌�������
					m_collisionPos = D3DXVECTOR3(m_collisionPos.x, m_hitPos.y - hitDistance * 0.5f, m_collisionPos.z);
					m_bCollision = true;
				}

				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(0.0f, 1.0f, 0.0f), (playerModelData.m_maxModel.y - playerModelData.m_minModel.y) * 0.5f, hitDistance, &overRange))
				{	// ���݂̃v���C���[�̈ʒu�����ւ̌�������
					m_collisionPos = D3DXVECTOR3(m_collisionPos.x, m_hitPos.y + hitDistance * 0.5f, m_collisionPos.z);
					m_bCollision = true;

					if (isIntersect(m_modelData[i].m_mesh, pos + (playerModelData.m_maxModel - playerModelData.m_minModel), D3DXVECTOR3(0.0f, 1.0f, 0.0f), (playerModelData.m_maxModel.y - playerModelData.m_minModel.y) * 0.5f, hitDistance))
					{	// �΂߂���ςȌ��Ԃɓ���΍�
						pObj->SetPos(pObj->GetPosOld());
					}
				}
				if (overRange)
				{
					m_bCollision = true;
					//pObj->SetPos(pObj->GetPosOld());
				}

				// �Q�Ƃ���ʒu���v���C���[�̒��S�ɒ�������
				pos.y += (playerModelData.m_maxModel.y - playerModelData.m_minModel.y);

				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f), (playerModelData.m_maxModel.x - playerModelData.m_minModel.x) * 0.45f, hitDistance))
				{	// ���݂̃v���C���[�̈ʒu����E�ւ̌�������
					m_collisionPos = D3DXVECTOR3(m_hitPos.x - (hitDistance * 0.45f), m_collisionPos.y, m_hitPos.z);
					pObj->SetSpeed(0.0f);
					pObj->SetPos(m_collisionPos);
				}
				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), (playerModelData.m_maxModel.x - playerModelData.m_minModel.x) * 0.45f, hitDistance))
				{	// ���݂̃v���C���[�̈ʒu���獶�ւ̌�������
					m_collisionPos = D3DXVECTOR3(m_hitPos.x + (hitDistance * 0.45f), m_collisionPos.y, m_hitPos.z);
					pObj->SetSpeed(0.0f);
					pObj->SetPos(m_collisionPos);
				}
				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(0.0f, 0.0f, 1.0f), (playerModelData.m_maxModel.z - playerModelData.m_minModel.z) * 0.45f, hitDistance))
				{	// ���݂̃v���C���[�̈ʒu���牜�ւ̌�������
					m_collisionPos = D3DXVECTOR3(m_hitPos.x, m_hitPos.y - (playerModelData.m_maxModel.y - playerModelData.m_minModel.y), m_hitPos.z - (hitDistance * 0.45f));
					pObj->SetSpeed(0.0f);
					pObj->SetPos(m_collisionPos);
				}
				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(0.0f, 0.0f, -1.0f), (playerModelData.m_maxModel.z - playerModelData.m_minModel.z) * 0.45f, hitDistance))
				{	// ���݂̃v���C���[�̈ʒu�����O�ւ̌�������
					m_collisionPos = D3DXVECTOR3(m_hitPos.x, m_hitPos.y - (playerModelData.m_maxModel.y - playerModelData.m_minModel.y), m_hitPos.z + (hitDistance  * 0.45f));
					pObj->SetSpeed(0.0f);
					pObj->SetPos(m_collisionPos);
				}
			}
		}

		// �I�u�W�F�N�g�^�C�v���G�̏ꍇ
		if (objType == OBJTYPE_ENEMY)
		{
			CEnemy *pObj = (CEnemy*)pObject;
			CEnemy::SModelData enemyModelData = *pObj->GetModelData(0);
			D3DXVECTOR3 pos = pObj->GetPos();

			for (size_t i = 0; i < m_modelData.size(); i++)
			{
				float hitDistance = 0;
				bool overRange = false;
				pObj->SetCollision(false);

				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(0.0f, -1.0f, 0.0f), (enemyModelData.maxModel.y - enemyModelData.minModel.y) * 0.5f, hitDistance))
				{	// ���݂̓G�̈ʒu���牺�ւ̌�������
					m_enemyCollisionPos = D3DXVECTOR3(m_enemyCollisionPos.x, m_enemyHitPos.y - hitDistance * 0.5f, m_enemyCollisionPos.z);
					pObj->SetCollisionPos(m_enemyCollisionPos);
					pObj->SetCollision(true);
				}

				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(0.0f, 1.0f, 0.0f), (enemyModelData.maxModel.y - enemyModelData.minModel.y), hitDistance, &overRange))
				{	// ���݂̓G�̈ʒu�����ւ̌�������
					m_enemyCollisionPos = D3DXVECTOR3(m_enemyCollisionPos.x, m_enemyHitPos.y + hitDistance, m_enemyCollisionPos.z);
					pObj->SetCollisionPos(m_enemyCollisionPos);
					pObj->SetCollision(true);
				}
				else if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(0.0f, 1.0f, 0.0f), 800.0f, hitDistance))
				{
					if (pObj->GetCollisionOnce())
					{
						pObj->SetCollisionPos(D3DXVECTOR3(m_enemyCollisionPos.x, m_enemyHitPos.y + hitDistance, m_enemyCollisionPos.z));
						pObj->SetCollision(true);
						pObj->SetCollisionOnce(false);
					}
				}
			}
		}

		//�|�C���^�����ɐi�߂�
		pObject = pObject->GetNext();
		
	}
}

//��������������������������������������������������������������
// �X�e�[�W�̕`��
//��������������������������������������������������������������
void CStage::Draw()
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ���C�g�̃|�C���^���擾
	CLight* pLight = CApplication::GetInstance()->GetMode()->GetGame()->GetLight();

	// �e�N�X�`���̃|�C���^���擾
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	CShadow *pShadow = CApplication::GetInstance()->GetMode()->GetGame()->GetShadow();
	CLambert *pLambert = CApplication::GetInstance()->GetMode()->GetGame()->GetLambert();
	CDepthBufferShadow *pDepthBuffShadow = CApplication::GetInstance()->GetMode()->GetGame()->GetDepthBuffShadow();

	pShadow->StartViewfromLight();
	pLambert->Begin();

	for (size_t i = 0; i < m_modelData.size(); i++)
	{
		for (size_t j = 0; j < m_modelData[i].m_dwNum; j++)
		{
			pDevice->SetTexture(0, NULL);

			pLambert->SetMatrix(&pShadow->GetWVP());

			pLambert->BeginPass(0);

			m_modelData[i].m_mesh->DrawSubset(j);

			pLambert->EndPass();
		}
	}

	pLambert->End();

	pShadow->EndViewfromLight();

	// �f�v�X�o�b�t�@�T�[�t�F�C�X���Q�Ƃ��A�I�u�W�F�N�g�Ɖe�������_�����O����
	// �f�v�X�o�b�t�@�T�[�t�F�C�X�̃e�N�X�`���[���T���v���ԍ�1�ɃZ�b�g����
	pDevice->SetTexture(1, pShadow->GetZBufferTexture());

	pDepthBuffShadow->SetBias(0.0005f);
	pDepthBuffShadow->SetShadowColor(0.3f);
	pDepthBuffShadow->SetAmbient(0.3f);
	pDepthBuffShadow->Begin();
	pDepthBuffShadow->SetMatrix(&pShadow->GetMtxWorld(), &pShadow->GetWVP(), &pLight->GetVecDir());

	for (size_t i = 0; i < m_modelData.size(); i++)
	{
		D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
		D3DMATERIAL9 matDef;						// ���݂̃}�e���A����ۑ�
		D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

		// ���݂̃}�e���A����ۑ�
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_modelData[i].m_buffMat->GetBufferPointer();

		for (size_t j = 0; j < m_modelData[i].m_dwNum; j++)
		{
			// �e�N�X�`���̐ݒ��߂�
			pDevice->SetTexture(0, NULL);

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[j].MatD3D);

			if (pMat[j].pTextureFilename != nullptr)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, pTexture->ConfirmLoadedPath(pMat[j].pTextureFilename));
			}

			pDepthBuffShadow->BeginPass(0);

			//���f���p�[�c�̕`��
			m_modelData[i].m_mesh->DrawSubset(j);

			pDepthBuffShadow->EndPass();
		}

		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

	pDepthBuffShadow->End();

	pDevice->SetTexture(1, NULL);

	// �����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

//��������������������������������������������������������������
// ���C�̏Փ˔���
//��������������������������������������������������������������
bool CStage::isIntersect(const LPD3DXMESH& mesh, D3DXVECTOR3 pos, D3DXVECTOR3 vecDir, float distanceRange, float& hitDistance, bool* overRange)
{
	BOOL isHit = false;
	DWORD hitIndex = -1;
	D3DXVECTOR2 UVHit;
	float Distance = 0.0f;

	// �ړI�̕����փ��C���΂�
	D3DXIntersect(mesh,
		&pos,
		&vecDir,
		&isHit,
		&hitIndex,
		&UVHit.x,
		&UVHit.y,
		&Distance,
		NULL,
		NULL);

	if (!isHit)
	{	// ���C���������Ȃ������ꍇ
		return false;
	}
		
	if (Distance == 0.0f)
	{	// ���������������O�̏ꍇ
		return false;
	}

	if (Distance >= distanceRange)
	{	// ����������̋�����艓�������ꍇ
		if (overRange != nullptr)
		{
			*overRange = true;
		}
		return false;
	}
	if (overRange != nullptr)
	{
		*overRange = false;
	}

	if (isnan(pos.y))
	{	// ���l��nan�ɂȂ����ꍇ
		return false;
	}

	hitDistance = Distance;

	if (m_bPlayer)
	{
		m_hitPos = pos;
	}
	else
	{
		m_enemyHitPos = pos;
	}
	return true;
}

//��������������������������������������������������������������
// �X�e�[�W�̃��f���f�[�^���擾
//��������������������������������������������������������������
void CStage::LoadModel(std::string path)
{
	// ���f���f�[�^�̃|�C���^���擾
	CModel *pModel = CApplication::GetInstance()->GetModel();

	SModelData data = {};

	data.m_mesh = pModel->GetMesh(path);
	data.m_buffMat = pModel->GetBuffMat(path);
	data.m_dwNum = pModel->GetModelNum(path);
	data.m_maxModel = pModel->GetMaxModel(path);
	data.m_minModel = pModel->GetMinModel(path);
	data.m_pVtxBuff = pModel->GetVtxBuff(path);
	data.m_pIdxBuff = pModel->GetIdxBuff(path);
	data.m_numVtx = pModel->GetVertexCount(path);
	data.m_numPrim = pModel->GetPrimitiveCount(path);

	m_modelData.push_back(data);
}