#include "item.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "utility.h"
#include "model.h"
#include "number.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アイテムのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CItem::CItem()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アイテムのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CItem::~CItem()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アイテムの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CItem * CItem::Create(D3DXVECTOR3 pos, int priority)
{
	CItem *pItem = nullptr;
	pItem = new CItem;

	//ヌルチェック
	if (pItem != nullptr)
	{
		pItem->m_objpos = pos;
		pItem->Init();
	}

	return pItem;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アイテムの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CItem::Init()
{
	LoadModel("GEM");

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アイテムの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CItem::Uninit()
{
	//モデルデータが空じゃない場合
	if (!m_modelData.empty())
	{
		m_modelData.clear();
	}

	Destroy();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アイテムの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CItem::Update()
{
	// プレイヤーのポインタを取得
	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

	if (CUtility::isCircleCollision(m_objpos, 450.0f, pPlayer->GetPos(), 5.0f))
	{
		D3DXVECTOR3 vec = pPlayer->GetPos() - m_objpos;

		D3DXVec3Normalize(&vec, &vec);

		//アイテムの移動
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

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アイテムの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CItem::Draw()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// モデル描画
	for (size_t i = 0; i < m_modelData.size(); i++)
	{
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

		D3DMATERIAL9 matDef;								//現在のマテリアルを保存
		D3DXMATERIAL *pMat;									//マテリアルデータへのポインタ

		//テクスチャの設定を戻す
		pDevice->SetTexture(0, NULL);

		//Zテスト
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//現在のマテリアルを保存
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_modelData[i].buffMat->GetBufferPointer();

		for (DWORD j = 0; j < m_modelData[i].dwNum; j++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat->MatD3D);

			//モデルパーツの描画
			m_modelData[i].mesh->DrawSubset(j);
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アイテムのモデルデータを取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CItem::LoadModel(std::string path)
{
	// モデルデータのポインタを取得
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