#include "model.h"
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "player.h"
#include "file.h"
#include "object3d.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CModel::CModel() :
	m_pParent(),
	m_scale(D3DXVECTOR3(1.0f, 1.0f, 1.0f)),
	m_pTexture(nullptr)
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CModel::~CModel()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルの読み込み
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CModel::Load(std::string str, std::string path)
{
	SModelData model = {};
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

	std::string fileName = path;
	std::string ext = std::strrchr(fileName.c_str(), '.');

	if (ext == ".x")
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(&path.front(),
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&model.buffMat,
			NULL,
			&model.dwNum,
			&model.mesh);

		int nNumVtx;		//頂点数
		DWORD sizeFVF;		//頂点フォーマットのサイズ
		BYTE *pVtxBuff;		//頂点バッファへのポインタ

		//頂点数の取得
		nNumVtx = model.mesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(model.mesh->GetFVF());

		//頂点バッファのロック
		model.mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int i = 0; i < nNumVtx; i++)
		{
			//頂点座標の代入
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
			//頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += sizeFVF;
		}

		//モデルサイズ
		m_modelSize = D3DXVECTOR3(model.maxModel.x - model.minModel.x, model.maxModel.y - model.minModel.y, model.maxModel.z - model.minModel.z);

		//頂点バッファのアンロック
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

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルの読み込み
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CModel::Load(std::vector<std::string> data)
{
	std::string ext = std::strrchr(data[1].c_str(), '.');

	if (ext == ".x")
	{
		Load_XFile(data);
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 全てのモデルを読み込み
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
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
	//デバイスの取得
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

	//Xファイルの読み込み
	D3DXLoadMeshFromX(&path.front(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&model.buffMat,
		NULL,
		&model.dwNum,
		&model.mesh);

	int nNumVtx;	// 頂点数保存用変数
	DWORD sizeFVF;	// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;	// 頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = model.mesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(model.mesh->GetFVF());

	//頂点バッファのロック
	model.mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	model.mesh->GetVertexBuffer(&model.vtxBuff);
	model.mesh->GetIndexBuffer(&model.idxBuff);

	for (int i = 0; i < nNumVtx; i++)
	{
		//頂点座標の代入
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
		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	//モデルサイズ
	m_modelSize = D3DXVECTOR3(model.maxModel.x - model.minModel.x, model.maxModel.y - model.minModel.y, model.maxModel.z - model.minModel.z);

	//頂点バッファのアンロック
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

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルのテクスチャをバインド
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CModel::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		//テクスチャのポインタ
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルの頂点バッファを取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
LPDIRECT3DVERTEXBUFFER9 CModel::GetVtxBuff(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].vtxBuff;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルのインデックスバッファを取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
LPDIRECT3DINDEXBUFFER9 CModel::GetIdxBuff(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].idxBuff;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルのマテリアル情報を取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
LPD3DXBUFFER CModel::GetBuffMat(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].buffMat;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルのメッシュ情報を取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
LPD3DXMESH CModel::GetMesh(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].mesh;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルのマテリアルの個数を取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
DWORD CModel::GetModelNum(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].dwNum;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルの大きさの最小値を取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
D3DXVECTOR3 CModel::GetMinModel(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	return m_model[model].minModel;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルの大きさの最大値を取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
D3DXVECTOR3 CModel::GetMaxModel(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	return m_model[model].maxModel;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルの頂点数を取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
int CModel::GetVertexCount(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].vtxCount;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルのポリゴン数を取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
int CModel::GetPrimitiveCount(std::string model)
{
	if (m_model.count(model) == 0)
	{	//モデルデータが入ってなかった場合
		return 0;
	}

	return m_model[model].primitiveCount;
}