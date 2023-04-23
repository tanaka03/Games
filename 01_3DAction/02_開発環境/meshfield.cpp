#include "meshfield.h"
#include "object3d.h"

//��������������������������������������������������������������
// ���b�V���t�B�[���h�̃R���X�g���N�^
//��������������������������������������������������������������
CMeshField::CMeshField()
{
}

//��������������������������������������������������������������
// ���b�V���t�B�[���h�̃f�X�g���N�^
//��������������������������������������������������������������
CMeshField::~CMeshField()
{
}

//��������������������������������������������������������������
// ���b�V���t�B�[���h�̐���
//��������������������������������������������������������������
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int X, int Z)
{
	CMeshField *pMesh = nullptr;
	pMesh = new CMeshField;

	//�k���`�F�b�N
	if (pMesh != nullptr)
	{
		// �|���S���̏���������
		pMesh->SetX(X);
		pMesh->SetZ(Z);
		pMesh->SetPos(pos);
		pMesh->SetScale(scale);
		pMesh->Init();
	}

	return pMesh;
}

//��������������������������������������������������������������
// ���b�V���t�B�[���h�̏�����
//��������������������������������������������������������������
HRESULT CMeshField::Init()
{
	CMesh::Init();

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 scale = GetScale();
	int meshX = GetX();
	int meshZ = GetZ();
	m_MeshField_VertexNum = GetVtxNum();
	BindTexture("WATER");

	//���_�o�b�t�@�����b�N
	VERTEX_3D * pVtx = nullptr;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_MeshField_VertexNum; nCnt++)
	{
		// ���_���W�̐ݒ�
		pVtx[nCnt].pos = D3DXVECTOR3(pos.x + scale.x * (nCnt % (meshX + 1)), 0.0f, pos.z - scale.z * (nCnt / (meshZ + 1)));

		//�e���_�̖@���̐ݒ�@���@�x�N�g���̑傫����1�ɂ���K�v������
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//���_�J���[
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + 0.5f * (nCnt % (meshZ + 1)), 0.0f + 0.5f * (nCnt / (meshZ + 1)));
	}

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD * pIdx;

	D3DXVECTOR3 Vtx[3], edge[2], Normal;

	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int i = 0; i < GetIdxNum() - 2; i++)
	{
		Vtx[0] = pVtx[pIdx[i + 0]].pos;
		Vtx[1] = pVtx[pIdx[i + 1]].pos;
		Vtx[2] = pVtx[pIdx[i + 2]].pos;

		edge[0] = Vtx[1] - Vtx[0];
		edge[1] = Vtx[2] - Vtx[1];

		//�|���S���̖ʂ̖@�������߂�
		if (i % 2 == 0)
		{
			D3DXVec3Cross(&Normal, &edge[0], &edge[1]);
		}

		else
		{
			D3DXVec3Cross(&Normal, &edge[1], &edge[0]);
		}

		D3DXVec3Normalize(&Normal, &Normal);

		pVtx[pIdx[i]].nor += Normal;
		pVtx[pIdx[i + 1]].nor += Normal;
		pVtx[pIdx[i + 2]].nor += Normal;
	}

	for (int j = 0; j < m_MeshField_VertexNum; j++)
	{
		D3DXVec3Normalize(&pVtx[j].nor, &pVtx[j].nor);
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//��������������������������������������������������������������
// ���b�V���t�B�[���h�̏I��
//��������������������������������������������������������������
void CMeshField::Uninit()
{
	CMesh::Uninit();
}

//��������������������������������������������������������������
// ���b�V���t�B�[���h�̍X�V
//��������������������������������������������������������������
void CMeshField::Update()
{
	CMesh::Update();

	//���_�o�b�t�@�����b�N
	VERTEX_3D * pVtx = nullptr;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD * pIdx;

	D3DXVECTOR3 Vtx[3], edge[2], Normal;

	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int i = 0; i < GetIdxNum() - 2; i++)
	{
		Vtx[0] = pVtx[pIdx[i + 0]].pos;
		Vtx[1] = pVtx[pIdx[i + 1]].pos;
		Vtx[2] = pVtx[pIdx[i + 2]].pos;

		//pVtx[pIdx[i + 0]].tex.x += 0.005f;
		//pVtx[pIdx[i + 1]].tex.x += 0.005f;
		//pVtx[pIdx[i + 2]].tex.x += 0.005f;

		edge[0] = Vtx[1] - Vtx[0];
		edge[1] = Vtx[2] - Vtx[1];

		//�|���S���̖ʂ̖@�������߂�
		if (i % 2 == 0)
		{
			D3DXVec3Cross(&Normal, &edge[0], &edge[1]);
		}

		else
		{
			D3DXVec3Cross(&Normal, &edge[1], &edge[0]);
		}

		D3DXVec3Normalize(&Normal, &Normal);

		pVtx[pIdx[i]].nor += Normal;
		pVtx[pIdx[i + 1]].nor += Normal;
		pVtx[pIdx[i + 2]].nor += Normal;
	}

	for (int j = 0; j < m_MeshField_VertexNum; j++)
	{
		D3DXVec3Normalize(&pVtx[j].nor, &pVtx[j].nor);
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//��������������������������������������������������������������
// ���b�V���t�B�[���h�̕`��
//��������������������������������������������������������������
void CMeshField::Draw()
{
	CMesh::Draw();
}