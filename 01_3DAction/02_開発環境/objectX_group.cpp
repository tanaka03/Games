#include "application.h"
#include "renderer.h"
#include "objectX_group.h"
#include "file.h"

#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CObjectXGroup::CObjectXGroup()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CObjectXGroup::~CObjectXGroup()
{
}

//--------------------------------------------------
// 全ての読み込み
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
// 読み込み
//--------------------------------------------------
void CObjectXGroup::Load(std::string inKey, std::string inFileName)
{
	SModelData model = {};
	std::string fileName = inFileName;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(&fileName.front(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&model.pBuffMat,
		NULL,
		&model.NumMat,
		&model.pMesh);

	int nNumVtx;	// 頂点数保存用変数
	DWORD sizeFVF;	// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;	// 頂点バッファへのポインタ

					//頂点数の取得
	nNumVtx = model.pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(model.pMesh->GetFVF());

	//頂点バッファのロック
	model.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// モデルの端を格納する変数のリセット
	model.MinVtx = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	model.MaxVtx = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X
		if (vtx.x < model.MinVtx.x)
		{//最小値
			model.MinVtx.x = vtx.x;
		}
		if (vtx.x > model.MaxVtx.x)
		{//最大値
			model.MaxVtx.x = vtx.x;
		}

		//Y
		if (vtx.y < model.MinVtx.y)
		{//最小値
			model.MinVtx.y = vtx.y;
		}
		if (vtx.y > model.MaxVtx.y)
		{//最大値
			model.MaxVtx.y = vtx.y;
		}

		//Z
		if (vtx.z < model.MinVtx.z)
		{//最小値
			model.MinVtx.z = vtx.z;
		}
		if (vtx.z > model.MaxVtx.z)
		{//最大値
			model.MaxVtx.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタ進める
		pVtxBuff += sizeFVF;
	}

	// サイズ設定
	model.size = D3DXVECTOR3((model.MaxVtx.x - model.MinVtx.x), (model.MaxVtx.y - model.MinVtx.y), (model.MaxVtx.z - model.MinVtx.z));

	//頂点バッファのアンロック
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
// 読み込み
//--------------------------------------------------
void CObjectXGroup::Load(std::vector<std::string> inModel)
{
	SModelData model = {};
	std::string fileName = inModel[1];

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(&fileName.front(),
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&model.pBuffMat,
		NULL,
		&model.NumMat,
		&model.pMesh);

	int nNumVtx;	// 頂点数保存用変数
	DWORD sizeFVF;	// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;	// 頂点バッファへのポインタ

					//頂点数の取得
	nNumVtx = model.pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(model.pMesh->GetFVF());

	//頂点バッファのロック
	model.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// モデルの端を格納する変数のリセット
	model.MinVtx = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);
	model.MaxVtx = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//X
		if (vtx.x < model.MinVtx.x)
		{//最小値
			model.MinVtx.x = vtx.x;
		}
		if (vtx.x > model.MaxVtx.x)
		{//最大値
			model.MaxVtx.x = vtx.x;
		}

		//Y
		if (vtx.y < model.MinVtx.y)
		{//最小値
			model.MinVtx.y = vtx.y;
		}
		if (vtx.y > model.MaxVtx.y)
		{//最大値
			model.MaxVtx.y = vtx.y;
		}

		//Z
		if (vtx.z < model.MinVtx.z)
		{//最小値
			model.MinVtx.z = vtx.z;
		}
		if (vtx.z > model.MaxVtx.z)
		{//最大値
			model.MaxVtx.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタ進める
		pVtxBuff += sizeFVF;
	}

	// サイズ設定
	model.size = D3DXVECTOR3((model.MaxVtx.x - model.MinVtx.x), (model.MaxVtx.y - model.MinVtx.y), (model.MaxVtx.z - model.MinVtx.z));

	//頂点バッファのアンロック
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
// 全ての解放
//--------------------------------------------------
void CObjectXGroup::UnloadAll()
{
	m_model.clear();
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CObjectXGroup::Unload(std::string inKey)
{
	m_model.erase(inKey);
}

LPD3DXMESH CObjectXGroup::GetMesh(std::string inKey)
{
	// Keyが存在するか否か。
	if (!ExistsKey(inKey))
	{
		// Keyがなかった場合
		return nullptr;
	}

	/* ↓Keyがあった場合↓ */

	return m_model[inKey].pMesh;
}

LPD3DXBUFFER CObjectXGroup::GetBuffMat(std::string inKey)
{
	// Keyが存在するか否か。
	if (!ExistsKey(inKey))
	{
		// Keyがなかった場合
		return nullptr;
	}

	/* ↓Keyがあった場合↓ */

	return m_model[inKey].pBuffMat;
}

DWORD CObjectXGroup::GetNumMat(std::string inKey)
{
	// Keyが存在するか否か。
	if (!ExistsKey(inKey))
	{
		// Keyがなかった場合
		return 0;
	}

	/* ↓Keyがあった場合↓ */

	return m_model[inKey].NumMat;
}

D3DXVECTOR3 CObjectXGroup::GetMinVtx(std::string inKey)
{
	// Keyが存在するか否か。
	if (!ExistsKey(inKey))
	{
		// Keyがなかった場合
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/* ↓Keyがあった場合↓ */

	return m_model[inKey].MinVtx;
}

D3DXVECTOR3 CObjectXGroup::GetMaxVtx(std::string inKey)
{
	// Keyが存在するか否か。
	if (!ExistsKey(inKey))
	{
		// Keyがなかった場合
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/* ↓Keyがあった場合↓ */

	return m_model[inKey].MaxVtx;
}

D3DXVECTOR3 CObjectXGroup::GetSize(std::string inKey)
{
	// Keyが存在するか否か。
	if (!ExistsKey(inKey))
	{
		// Keyがなかった場合
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	/* ↓Keyがあった場合↓ */

	return m_model[inKey].size;
}
