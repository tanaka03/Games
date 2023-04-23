#include "item.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "utility.h"
#include "model.h"
#include "number.h"

//��������������������������������������������������������������
// �A�C�e���̃R���X�g���N�^
//��������������������������������������������������������������
CItem::CItem()
{
}

//��������������������������������������������������������������
// �A�C�e���̃f�X�g���N�^
//��������������������������������������������������������������
CItem::~CItem()
{
}

//��������������������������������������������������������������
// �A�C�e���̐���
//��������������������������������������������������������������
CItem * CItem::Create(D3DXVECTOR3 pos, int priority)
{
	CItem *pItem = nullptr;
	pItem = new CItem;

	//�k���`�F�b�N
	if (pItem != nullptr)
	{
		pItem->m_objpos = pos;
		pItem->Init();
	}

	return pItem;
}

//��������������������������������������������������������������
// �A�C�e���̏�����
//��������������������������������������������������������������
HRESULT CItem::Init()
{
	LoadModel("GEM");

	return S_OK;
}

//��������������������������������������������������������������
// �A�C�e���̏I��
//��������������������������������������������������������������
void CItem::Uninit()
{
	//���f���f�[�^���󂶂�Ȃ��ꍇ
	if (!m_modelData.empty())
	{
		m_modelData.clear();
	}

	Destroy();
}

//��������������������������������������������������������������
// �A�C�e���̍X�V
//��������������������������������������������������������������
void CItem::Update()
{
	// �v���C���[�̃|�C���^���擾
	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

	if (CUtility::isCircleCollision(m_objpos, 450.0f, pPlayer->GetPos(), 5.0f))
	{
		D3DXVECTOR3 vec = pPlayer->GetPos() - m_objpos;

		D3DXVec3Normalize(&vec, &vec);

		//�A�C�e���̈ړ�
		m_objpos += vec * 13.5f;
	}

	if (CUtility::isCircleCollision(m_objpos, 40.0f, pPlayer->GetPos(), 5.0f))
	{
		CApplication::GetInstance()->GetMode()->GetGame()->GetScore()->AddValue(10);
		CItem::Destroy();
	}

	m_time++;
	if (m_time > 350)
	{
		CItem::Destroy();
	}
}

//��������������������������������������������������������������
// �A�C�e���̕`��
//��������������������������������������������������������������
void CItem::Draw()
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���f���`��
	for (size_t i = 0; i < m_modelData.size(); i++)
	{
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

		D3DMATERIAL9 matDef;								//���݂̃}�e���A����ۑ�
		D3DXMATERIAL *pMat;									//�}�e���A���f�[�^�ւ̃|�C���^

		//�e�N�X�`���̐ݒ��߂�
		pDevice->SetTexture(0, NULL);

		//Z�e�X�g
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//���݂̃}�e���A����ۑ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_modelData[i].buffMat->GetBufferPointer();

		for (DWORD j = 0; j < m_modelData[i].dwNum; j++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat->MatD3D);

			//���f���p�[�c�̕`��
			m_modelData[i].mesh->DrawSubset(j);
		}

		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//��������������������������������������������������������������
// �A�C�e���̃��f���f�[�^���擾
//��������������������������������������������������������������
void CItem::LoadModel(std::string path)
{
	// ���f���f�[�^�̃|�C���^���擾
	CModel *pModel = CApplication::GetInstance()->GetModel();

	SModelData data = {};

	data.mesh = pModel->GetMesh(path);
	data.buffMat = pModel->GetBuffMat(path);
	data.dwNum = pModel->GetModelNum(path);
	data.maxModel = pModel->GetMaxModel(path);
	data.minModel = pModel->GetMinModel(path);
	data.pVtxBuff = pModel->GetVtxBuff(path);
	data.pIdxBuff = pModel->GetIdxBuff(path);
	data.numVtx = pModel->GetVertexCount(path);
	data.numPrim = pModel->GetPrimitiveCount(path);

	m_modelData.push_back(data);
}