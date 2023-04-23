#include "application.h"
#include "renderer.h"
#include "objectX_group.h"
#include "file.h"

#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CObjectXGroup::CObjectXGroup()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObjectXGroup::~CObjectXGroup()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CObjectXGroup::LoadAll()
{
	nlohmann::json list = CFile::LoadJsonStage(L"Data/FILE/model.json");

	int size = (int)list["MODEL"].size();

	std::string test = list["MODEL"][0][0];
	for (int i = 0; i < size; ++i)
	{
		Load(list["MODEL"].at(i));
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CObjectXGroup::Load(std::string inKey, std::string inFileName)
{
	SModelData model = {};
	std::string fileName = inFileName;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(&fileName.front(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&model.pBuffMat,
		NULL,
		&model.NumMat,
		&model.pMesh);

	int nNumVtx;	// ���_���ۑ��p�ϐ�
	DWORD sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

					//���_���̎擾
	nNumVtx = model.pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(model.pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	model.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// ���f���̒[���i�[����ϐ��̃��Z�b�g
	model.MinVtx = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	model.MaxVtx = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X
		if (vtx.x < model.MinVtx.x)
		{//�ŏ��l
			model.MinVtx.x = vtx.x;
		}
		if (vtx.x > model.MaxVtx.x)
		{//�ő�l
			model.MaxVtx.x = vtx.x;
		}

		//Y
		if (vtx.y < model.MinVtx.y)
		{//�ŏ��l
			model.MinVtx.y = vtx.y;
		}
		if (vtx.y > model.MaxVtx.y)
		{//�ő�l
			model.MaxVtx.y = vtx.y;
		}

		//Z
		if (vtx.z < model.MinVtx.z)
		{//�ŏ��l
			model.MinVtx.z = vtx.z;
		}
		if (vtx.z > model.MaxVtx.z)
		{//�ő�l
			model.MaxVtx.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^�i�߂�
		pVtxBuff += sizeFVF;
	}

	// �T�C�Y�ݒ�
	model.size = D3DXVECTOR3((model.MaxVtx.x - model.MinVtx.x), (model.MaxVtx.y - model.MinVtx.y), (model.MaxVtx.z - model.MinVtx.z));

	//���_�o�b�t�@�̃A�����b�N
	model.pMesh->UnlockVertexBuffer();

	if (!ExistsKey(inKey))
	{
		m_model.insert(std::make_pair(inKey, model));
	}
	else
	{
		m_model[inKey] = model;
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CObjectXGroup::Load(std::vector<std::string> inModel)
{
	SModelData model = {};
	std::string fileName = inModel[1];

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(&fileName.front(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&model.pBuffMat,
		NULL,
		&model.NumMat,
		&model.pMesh);

	int nNumVtx;	// ���_���ۑ��p�ϐ�
	DWORD sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

					//���_���̎擾
	nNumVtx = model.pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(model.pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	model.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// ���f���̒[���i�[����ϐ��̃��Z�b�g
	model.MinVtx = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	model.MaxVtx = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X
		if (vtx.x < model.MinVtx.x)
		{//�ŏ��l
			model.MinVtx.x = vtx.x;
		}
		if (vtx.x > model.MaxVtx.x)
		{//�ő�l
			model.MaxVtx.x = vtx.x;
		}

		//Y
		if (vtx.y < model.MinVtx.y)
		{//�ŏ��l
			model.MinVtx.y = vtx.y;
		}
		if (vtx.y > model.MaxVtx.y)
		{//�ő�l
			model.MaxVtx.y = vtx.y;
		}

		//Z
		if (vtx.z < model.MinVtx.z)
		{//�ŏ��l
			model.MinVtx.z = vtx.z;
		}
		if (vtx.z > model.MaxVtx.z)
		{//�ő�l
			model.MaxVtx.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^�i�߂�
		pVtxBuff += sizeFVF;
	}

	// �T�C�Y�ݒ�
	model.size = D3DXVECTOR3((model.MaxVtx.x - model.MinVtx.x), (model.MaxVtx.y - model.MinVtx.y), (model.MaxVtx.z - model.MinVtx.z));

	//���_�o�b�t�@�̃A�����b�N
	model.pMesh->UnlockVertexBuffer();

	if (!ExistsKey(inModel[0]))
	{
		m_model.insert(std::make_pair(inModel[0], model));
	}
	else
	{
		m_model[inModel[0]] = model;
	}
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CObjectXGroup::UnloadAll()
{
	m_model.clear();
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CObjectXGroup::Unload(std::string inKey)
{
	m_model.erase(inKey);
}

LPD3DXMESH CObjectXGroup::GetMesh(std::string inKey)
{
	// Key�����݂��邩�ۂ��B
	if (!ExistsKey(inKey))
	{
		// Key���Ȃ������ꍇ
		return nullptr;
	}

	/* ��Key���������ꍇ�� */

	return m_model[inKey].pMesh;
}

LPD3DXBUFFER CObjectXGroup::GetBuffMat(std::string inKey)
{
	// Key�����݂��邩�ۂ��B
	if (!ExistsKey(inKey))
	{
		// Key���Ȃ������ꍇ
		return nullptr;
	}

	/* ��Key���������ꍇ�� */

	return m_model[inKey].pBuffMat;
}

DWORD CObjectXGroup::GetNumMat(std::string inKey)
{
	// Key�����݂��邩�ۂ��B
	if (!ExistsKey(inKey))
	{
		// Key���Ȃ������ꍇ
		return 0;
	}

	/* ��Key���������ꍇ�� */

	return m_model[inKey].NumMat;
}

D3DXVECTOR3 CObjectXGroup::GetMinVtx(std::string inKey)
{
	// Key�����݂��邩�ۂ��B
	if (!ExistsKey(inKey))
	{
		// Key���Ȃ������ꍇ
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/* ��Key���������ꍇ�� */

	return m_model[inKey].MinVtx;
}

D3DXVECTOR3 CObjectXGroup::GetMaxVtx(std::string inKey)
{
	// Key�����݂��邩�ۂ��B
	if (!ExistsKey(inKey))
	{
		// Key���Ȃ������ꍇ
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/* ��Key���������ꍇ�� */

	return m_model[inKey].MaxVtx;
}

D3DXVECTOR3 CObjectXGroup::GetSize(std::string inKey)
{
	// Key�����݂��邩�ۂ��B
	if (!ExistsKey(inKey))
	{
		// Key���Ȃ������ꍇ
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/* ��Key���������ꍇ�� */

	return m_model[inKey].size;
}
