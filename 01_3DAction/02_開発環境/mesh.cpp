#include "application.h"
#include "renderer.h"
#include "mesh.h"
#include "object3d.h"
#include "player.h"
#include "game.h"

#include "debugproc.h"

//��������������������������
//���b�V���̃R���X�g���N�^
//��������������������������
CMesh::CMesh() :
	m_pTexture(nullptr)
{
	SetObjState(CObject::OBJSTATE_3D);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_meshX = 5;
	m_meshZ = 5;
}


//��������������������������
//���b�V���̃f�X�g���N�^
//��������������������������
CMesh::~CMesh()
{
}

//��������������������������
//���b�V���̏�����
//��������������������������
HRESULT CMesh::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	m_MeshField_VertexNum = (m_meshX + 1) * (m_meshZ + 1);					//���_��
	m_MeshField_IndexNum = (m_meshX + 1) * 2 * m_meshX + (m_meshZ - 1) * 2;	//�C���f�b�N�X
	m_MeshField_PrimitiveNum = m_meshX * m_meshZ * 2 + (m_meshZ - 1) * 4;	//�|���S��

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_MeshField_VertexNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(VERTEX_3D) * m_MeshField_IndexNum,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//==========================
	//�C���f�b�N�X�o�b�t�@
	//==========================
	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;

	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nIdxCnt = 0;

	for (int nCntZ = 0; nCntZ < m_meshZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= m_meshX; nCntX++)
		{
			//�C���f�b�N�X�̐ݒ�
			pIdx[nIdxCnt] = nCntX + nCntZ * (m_meshZ + 1) + (m_meshZ + 1);
			pIdx[nIdxCnt + 1] = nCntX + nCntZ * (m_meshZ + 1);

			nIdxCnt += 2;

			//�k�ރ|���S��
			if (nCntX == m_meshX)
			{
				pIdx[nIdxCnt] = nCntX + nCntZ * (m_meshZ + 1);
				pIdx[nIdxCnt + 1] = (nCntX + nCntZ * (m_meshX + 1) + (m_meshZ + 1)) + 1;

				nIdxCnt += 2;
			}
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//��������������������������
//���b�V���̏I��
//��������������������������
void CMesh::Uninit()
{
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	Destroy();
}

//��������������������������
//���b�V���̍X�V
//��������������������������
void CMesh::Update()
{
}

//��������������������������
//���b�V���̕`��
//��������������������������
void CMesh::Draw()
{
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;				//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_objpos.y, m_objpos.x, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �s��g�k�֐�
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_MeshField_VertexNum,	//���_��
		0,
		m_MeshField_PrimitiveNum	/*�`�悷��v���~�e�B�u��*/);
}

//��������������������������������������������������������������
// ���b�V���̃e�N�X�`�����o�C���h
//��������������������������������������������������������������
void CMesh::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		//�e�N�X�`���̃|�C���^
}

//��������������������������������������������������������������
// ���b�V���̏Փ˔���
//��������������������������������������������������������������
bool CMesh::Collision(D3DXVECTOR3 pos)
{
	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�o�b�t�@�����b�N
	VERTEX_3D *pVtx = nullptr;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int cnt = 0; cnt < m_MeshField_VertexNum; cnt++)
	{
		pVtx[cnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	for (int i = 0; i < m_MeshField_PrimitiveNum; i++)
	{
		if (pIdx[i] == pIdx[i + 1] && pIdx[i] == pIdx[i + 2] && pIdx[i + 1] == pIdx[i + 2])
		{
			continue;
		}

		//���_�̈ʒu
		D3DXVECTOR3 posA = pVtx[pIdx[i]].pos;
		D3DXVECTOR3 posB = pVtx[pIdx[i + 1]].pos;
		D3DXVECTOR3 posC = pVtx[pIdx[i + 2]].pos;

		//���_�̃x�N�g��
		D3DXVECTOR3 vecA = posB - posA;
		D3DXVECTOR3 vecB = posC - posB;
		D3DXVECTOR3 vecC = posA - posC;

		//�|���S���̒��_�ƃv���C���[�̈ʒu�̃x�N�g��
		D3DXVECTOR3 DistanceA = pos - posA;
		D3DXVECTOR3 DistanceB = pos - posB;
		D3DXVECTOR3 DistanceC = pos - posC;

		//�|���S���̒��_�̃x�N�g���ƃv���C���[���璸�_�̃x�N�g���̌v�Z����
		float fResult1 = vecA.x * DistanceA.z - vecA.z * DistanceA.x;
		float fResult2 = vecB.x * DistanceB.z - vecB.z * DistanceB.x;
		float fResult3 = vecC.x * DistanceC.z - vecC.z * DistanceC.x;

		if (fResult1 * fResult2 >= 0 &&
			fResult2 * fResult3 >= 0 &&
			fResult3 * fResult1 >= 0)
		{//�|���S���͈͓̔��ɓ������ꍇ
		 //pVtx[pIdx[i]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		 //pVtx[pIdx[i + 1]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		 //pVtx[pIdx[i + 2]].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			m_meshPt = i;

			//���b�V���̔���
			D3DXVECTOR3 V1 = posB - posA;
			D3DXVECTOR3 V2 = posC - posA;
			D3DXVECTOR3 normal;

			D3DXVec3Cross(&normal, &V2, &V1);
			D3DXVec3Normalize(&normal, &normal);

			m_posOld = pos;
			pos.y = posA.y - ((pos.x - posA.x) * normal.x + (pos.z - posA.z) * normal.z) / normal.y;

			//���_�o�b�t�@�̃A�����b�N
			m_pVtxBuff->Unlock();

			//�C���f�b�N�X�o�b�t�@�̃A�����b�N
			m_pIdxBuff->Unlock();

			if (pos.y <= CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer()->GetPos().y)
			{	// �v���C���[��Y���W���v�Z���ʂ�Y���W��荂���ꍇ����͋U
				return false;
			}

			if (normal == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{	// �@����0�̎��Apos.y�̒l��-nan(ind)�ɂȂ�ׁA�q�b�g�����n�_����������O�ɏI��
				return true;
			}

			m_CollisionPos = pos;
			return true;
		}
	}

	return false;
}

//��������������������������������������������������������������
// ���b�V���̃C���f�b�N�X�o�b�t�@�̈ʒu��ݒ�
//��������������������������������������������������������������
void CMesh::SetIdxPos(D3DXVECTOR3 pos, int idx)
{
	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�o�b�t�@�����b�N
	VERTEX_3D *pVtx = nullptr;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[pIdx[idx]].pos = pos;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
}

//��������������������������������������������������������������
// ���b�V���̃C���f�b�N�X�o�b�t�@�̈ʒu���擾
//��������������������������������������������������������������
D3DXVECTOR3 CMesh::GetIdxPos(int idx)
{
	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�o�b�t�@�����b�N
	VERTEX_3D *pVtx = nullptr;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 pos;
	pos = pVtx[pIdx[idx]].pos;

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return pos;
}