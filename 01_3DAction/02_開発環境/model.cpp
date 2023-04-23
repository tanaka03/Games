#include "model.h"
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "player.h"
#include "file.h"
#include "object3d.h"

//��������������������������������������������������������������
// ���f���̃R���X�g���N�^
//��������������������������������������������������������������
CModel::CModel() :
	m_pParent(),
	m_scale(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),
	m_pTexture(nullptr)
{
}

//��������������������������������������������������������������
// ���f���̃f�X�g���N�^
//��������������������������������������������������������������
CModel::~CModel()
{
}

//��������������������������������������������������������������
// ���f���̓ǂݍ���
//��������������������������������������������������������������
void CModel::Load(std::string str, std::string path)
{
	SModelData model = {};
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	std::string fileName = path;
	std::string ext = std::strrchr(fileName.c_str(), '.');

	if (ext == ".x")
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(&path.front(),
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&model.buffMat,
			NULL,
			&model.dwNum,
			&model.mesh);

		int nNumVtx;		//���_��
		DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

		//���_���̎擾
		nNumVtx = model.mesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(model.mesh->GetFVF());

		//���_�o�b�t�@�̃��b�N
		model.mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int i = 0; i < nNumVtx; i++)
		{
			//���_���W�̑��
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

			//X
			if (vtx.x > model.maxModel.x)
			{
				model.maxModel.x = floorf(vtx.x);
			}

			if (vtx.x < model.minModel.x)
			{
				model.minModel.x = floorf(vtx.x);
			}

			//Y
			if (vtx.y > model.maxModel.y)
			{
				model.maxModel.y = floorf(vtx.y);
			}

			if (vtx.y < model.minModel.y)
			{
				model.minModel.y = floorf(vtx.y);
			}

			//Z
			if (vtx.z > model.maxModel.z)
			{
				model.maxModel.z = floorf(vtx.z);
			}

			if (vtx.z < model.minModel.z)
			{
				model.minModel.z = floorf(vtx.z);
			}
			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFVF;
		}

		//���f���T�C�Y
		m_modelSize = D3DXVECTOR3(model.maxModel.x - model.minModel.x, model.maxModel.y - model.minModel.y, model.maxModel.z - model.minModel.z);

		//���_�o�b�t�@�̃A�����b�N
		model.mesh->UnlockVertexBuffer();
	}

	if (m_model.count(str) == 0)
	{
		m_model.insert(std::make_pair(str, model));
	}
	else
	{
		m_model[str] = model;
	}
}

//��������������������������������������������������������������
// ���f���̓ǂݍ���
//��������������������������������������������������������������
void CModel::Load(std::vector<std::string> data)
{
	std::string ext = std::strrchr(data[1].c_str(), '.');

	if (ext == ".x")
	{
		Load_XFile(data);
	}
}

//��������������������������������������������������������������
// �S�Ẵ��f����ǂݍ���
//��������������������������������������������������������������
void CModel::LoadAll()
{
	nlohmann::json list = CFile::LoadJsonStage(L"Data/FILE/model.json");

	int size = (int)list["MODEL"].size();

	std::string test = list["MODEL"][0][0];
	for (int i = 0; i < size; i++)
	{
		Load(list["MODEL"].at(i));
	}
}

void CModel::Load_XFile(std::vector<std::string> data)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	SModelData model = {};

	if (m_model.count(data[0]) != 0)
	{
		model = m_model[data[0]];
		return;
	}

	std::string path = data[1];

	model.minModel = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	model.maxModel = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(&path.front(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&model.buffMat,
		NULL,
		&model.dwNum,
		&model.mesh);

	int nNumVtx;	// ���_���ۑ��p�ϐ�
	DWORD sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = model.mesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(model.mesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	model.mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	model.mesh->GetVertexBuffer(&model.vtxBuff);
	model.mesh->GetIndexBuffer(&model.idxBuff);

	for (int i = 0; i < nNumVtx; i++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X
		if (vtx.x > model.maxModel.x)
		{
			model.maxModel.x = floorf(vtx.x);
		}

		if (vtx.x < model.minModel.x)
		{
			model.minModel.x = floorf(vtx.x);
		}

		//Y
		if (vtx.y >model.maxModel.y)
		{
			model.maxModel.y = floorf(vtx.y);
		}

		if (vtx.y < model.minModel.y)
		{
			model.minModel.y = floorf(vtx.y);
		}

		//Z
		if (vtx.z > model.maxModel.z)
		{
			model.maxModel.z = floorf(vtx.z);
		}

		if (vtx.z < model.minModel.z)
		{
			model.minModel.z = floorf(vtx.z);
		}
		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	//���f���T�C�Y
	m_modelSize = D3DXVECTOR3(model.maxModel.x - model.minModel.x, model.maxModel.y - model.minModel.y, model.maxModel.z - model.minModel.z);

	//���_�o�b�t�@�̃A�����b�N
	model.mesh->UnlockVertexBuffer();

	if (m_model.count(data[0]) == 0)
	{
		m_model.insert(std::make_pair(data[0], model));
	}
	else
	{
		m_model[data[0]] = model;
	}
}

//��������������������������������������������������������������
// ���f���̃e�N�X�`�����o�C���h
//��������������������������������������������������������������
void CModel::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		//�e�N�X�`���̃|�C���^
}

//��������������������������������������������������������������
// ���f���̒��_�o�b�t�@���擾
//��������������������������������������������������������������
LPDIRECT3DVERTEXBUFFER9 CModel::GetVtxBuff(std::string model)
{
	if (m_model.count(model) == 0)
	{	//���f���f�[�^�������ĂȂ������ꍇ
		return 0;
	}

	return m_model[model].vtxBuff;
}

//��������������������������������������������������������������
// ���f���̃C���f�b�N�X�o�b�t�@���擾
//��������������������������������������������������������������
LPDIRECT3DINDEXBUFFER9 CModel::GetIdxBuff(std::string model)
{
	if (m_model.count(model) == 0)
	{	//���f���f�[�^�������ĂȂ������ꍇ
		return 0;
	}

	return m_model[model].idxBuff;
}

//��������������������������������������������������������������
// ���f���̃}�e���A�������擾
//��������������������������������������������������������������
LPD3DXBUFFER CModel::GetBuffMat(std::string model)
{
	if (m_model.count(model) == 0)
	{	//���f���f�[�^�������ĂȂ������ꍇ
		return 0;
	}

	return m_model[model].buffMat;
}

//��������������������������������������������������������������
// ���f���̃��b�V�������擾
//��������������������������������������������������������������
LPD3DXMESH CModel::GetMesh(std::string model)
{
	if (m_model.count(model) == 0)
	{	//���f���f�[�^�������ĂȂ������ꍇ
		return 0;
	}

	return m_model[model].mesh;
}

//��������������������������������������������������������������
// ���f���̃}�e���A���̌����擾
//��������������������������������������������������������������
DWORD CModel::GetModelNum(std::string model)
{
	if (m_model.count(model) == 0)
	{	//���f���f�[�^�������ĂȂ������ꍇ
		return 0;
	}

	return m_model[model].dwNum;
}

//��������������������������������������������������������������
// ���f���̑傫���̍ŏ��l���擾
//��������������������������������������������������������������
D3DXVECTOR3 CModel::GetMinModel(std::string model)
{
	if (m_model.count(model) == 0)
	{	//���f���f�[�^�������ĂȂ������ꍇ
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	return m_model[model].minModel;
}

//��������������������������������������������������������������
// ���f���̑傫���̍ő�l���擾
//��������������������������������������������������������������
D3DXVECTOR3 CModel::GetMaxModel(std::string model)
{
	if (m_model.count(model) == 0)
	{	//���f���f�[�^�������ĂȂ������ꍇ
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	return m_model[model].maxModel;
}

//��������������������������������������������������������������
// ���f���̒��_�����擾
//��������������������������������������������������������������
int CModel::GetVertexCount(std::string model)
{
	if (m_model.count(model) == 0)
	{	//���f���f�[�^�������ĂȂ������ꍇ
		return 0;
	}

	return m_model[model].vtxCount;
}

//��������������������������������������������������������������
// ���f���̃|���S�������擾
//��������������������������������������������������������������
int CModel::GetPrimitiveCount(std::string model)
{
	if (m_model.count(model) == 0)
	{	//���f���f�[�^�������ĂȂ������ꍇ
		return 0;
	}

	return m_model[model].primitiveCount;
}