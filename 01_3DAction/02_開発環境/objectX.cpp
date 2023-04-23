//=============================================================================
// インクルードファイル
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
// コンストラクタ
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
// デストラクタ
//=============================================================================
CObjectX::~CObjectX()
{
}

//=============================================================================
// オブジェクトの初期化
//=============================================================================
HRESULT CObjectX::Init()
{
	return S_OK;
}

//=============================================================================
// オブジェクトの終了
//=============================================================================
void CObjectX::Uninit()
{
	//インスタンスの解放処理
	Destroy();
}

//=============================================================================
// オブジェクトの更新
//=============================================================================
void CObjectX::Update()
{
}

//=============================================================================
// オブジェクトの描画
//=============================================================================
void CObjectX::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ライトのポインタを取得
	CLight* pLight = CApplication::GetInstance()->GetMode()->GetGame()->GetLight();

	CShadow *pShadow = CApplication::GetInstance()->GetMode()->GetGame()->GetShadow();
	CLambert *pLambert = CApplication::GetInstance()->GetMode()->GetGame()->GetLambert();
	CDepthBufferShadow *pDepthBuffShadow = CApplication::GetInstance()->GetMode()->GetGame()->GetDepthBuffShadow();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;		// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);	//(※行列移動関数(第1引数にx,y,z方向の移動行列を作成))
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		mtxParent = m_pParent->GetMtxWorld();

		// 行列掛け算関数
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	}

	//ワールドマトリックスの設定（ワールド座標行列の設定）
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 深度テクスチャ更新
	//pShadow->StartViewfromLight();
	//D3DXMATRIX wvp = pShadow->GetWVP();

	//pLambert->Begin();
	////pLambert->SetMatrix(&wvp);

	//for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	//{
	//	pDevice->SetTexture(0, NULL);

	//	pLambert->BeginPass(0);

	//	pLambert->SetMatrix(&pShadow->GetWVP());

	//	//モデルパーツの描画
	//	m_pMesh->DrawSubset(nCntMat);

	//	pLambert->EndPass();
	//}

	//pLambert->End();
	//pShadow->EndViewfromLight();

	// デプスバッファサーフェイスを参照し、オブジェクトと影をレンダリングする
	// デプスバッファサーフェイスのテクスチャーをサンプラ番号1にセットする
	//pDevice->SetTexture(1, pShadow->GetZBufferTexture());

	//pDepthBuffShadow->SetBias(0.005f);
	//pDepthBuffShadow->SetShadowColor(0.3f);
	//pDepthBuffShadow->SetAmbient(0.3f);
	//pDepthBuffShadow->Begin();
	//pDepthBuffShadow->SetMatrix(&m_mtxWorld, &pShadow->GetWVP(), &pLight->GetVecDir());

	pDevice->SetTexture(0, NULL);

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		/*pDepthBuffShadow->SetDiffuse(D3DXVECTOR4(pMat[nCntMat].MatD3D.Diffuse.r, pMat[nCntMat].MatD3D.Diffuse.g, pMat[nCntMat].MatD3D.Diffuse.b, pMat[nCntMat].MatD3D.Diffuse.a));
		pDepthBuffShadow->BeginPass(0);*/

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);

		//pDepthBuffShadow->EndPass();
	}

	pDepthBuffShadow->End();

	// 設定していた深度テクスチャを破棄
	pDevice->SetTexture(1, NULL);

	//保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

void CObjectX::Draw(D3DXMATRIX mtxParent)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ライトのポインタを取得
	CLight* pLight = CApplication::GetInstance()->GetMode()->GetGame()->GetLight();

	CShadow *pShadow = CApplication::GetInstance()->GetMode()->GetGame()->GetShadow();
	CLambert *pLambert = CApplication::GetInstance()->GetMode()->GetGame()->GetLambert();
	CDepthBufferShadow *pDepthBuffShadow = CApplication::GetInstance()->GetMode()->GetGame()->GetDepthBuffShadow();

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxScaling;

	// 現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// 行列回転関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				// 行列掛け算関数 

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		// 行列移動関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);			// 行列掛け算関数

	// 行列掛け算関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	// テクスチャポインタの取得
	CTexture *pTexture = CApplication::GetInstance()->GetTexture();

	// マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// 深度テクスチャ更新
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

	//	//モデルパーツの描画
	//	m_pMesh->DrawSubset(nCntMat);

	//	pLambert->EndPass();
	//}

	//pLambert->End();
	//pShadow->EndViewfromLight();

	// デプスバッファサーフェイスを参照し、オブジェクトと影をレンダリングする
	// デプスバッファサーフェイスのテクスチャーをサンプラ番号1にセットする
	//pDevice->SetTexture(1, pShadow->GetZBufferTexture());

	//pDepthBuffShadow->SetBias(0.005f);
	//pDepthBuffShadow->SetShadowColor(0.3f);
	//pDepthBuffShadow->SetAmbient(0.3f);
	//pDepthBuffShadow->Begin();

	//pDepthBuffShadow->SetMatrix(&m_mtxWorld, &pShadow->GetWVP(), &pLight->GetVecDir());

	pDevice->SetTexture(0, NULL);

	for (int nCntMat = 0; nCntMat < (int)m_NumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//pDepthBuffShadow->SetDiffuse(D3DXVECTOR4(pMat[nCntMat].MatD3D.Diffuse.r, pMat[nCntMat].MatD3D.Diffuse.g, pMat[nCntMat].MatD3D.Diffuse.b, pMat[nCntMat].MatD3D.Diffuse.a));
		//pDepthBuffShadow->BeginPass(0);

		// モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);

		//pDepthBuffShadow->EndPass();

		// テクスチャの設定
		pDevice->SetTexture(0, nullptr);
	}

	//pDepthBuffShadow->End();

	// 設定していた深度テクスチャを破棄
	pDevice->SetTexture(1, NULL);

	// 保持していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 頂点最大小値の計算処理
//=============================================================================
void CObjectX::CalculationVtx()
{
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;

	D3DXMatrixIdentity(&mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// 行列回転関数
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);					// 行列掛け算関数

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
// 座標設定関数
//=============================================================================
void CObjectX::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// サイズ設定関数
//=============================================================================
void CObjectX::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
// 移動力設定関数
//=============================================================================
void CObjectX::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 色設定関数
//=============================================================================
void CObjectX::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
// 向き設定関数
//=============================================================================
void CObjectX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// 生成処理
//=============================================================================
CObjectX * CObjectX::Create(D3DXVECTOR3 pos, int nPriority)
{
	//ポインタ宣言
	CObjectX *pObjectX = nullptr;

	//インスタンス生成
	pObjectX = new CObjectX(nPriority);

	if (pObjectX != nullptr)
	{//ポインタが存在したら実行
		pObjectX->Init();
		pObjectX->SetPos(pos);
		pObjectX->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{//ポインタが虚無だったら実行
		assert(false);
	}

	//ポインタを返す
	return pObjectX;
}

//=============================================================================
// モデルの読み込み
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
// 当たり判定 (左右,奥,手前)
//=============================================================================
bool CObjectX::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize)
{
	if (!m_isCollision)
	{
		return false;
	}

	// 変数宣言
	bool bIsLanding = false;

	// モデルの左側当たり判定
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
	// モデルの右側当たり判定
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
	// モデルの奥側当たり判定
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
	// モデルの手前側当たり判定
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

	// 値を返す
	return bIsLanding;
}

//=============================================================================
// 当たり判定 (左右,奥,手前)
//=============================================================================
bool CObjectX::Collision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * inMaxVtx, D3DXVECTOR3 * inMinVtx)
{
	if (!m_isCollision)
	{
		return false;
	}

	// 変数宣言
	bool bIsLanding = false;

	// モデルの乗り上げ判定
	if ((pPos->y + 20.0f > m_pos.y + m_MaxVtx.y))
	{
		return bIsLanding;
	}

	// モデルの左側当たり判定
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

	// モデルの右側当たり判定
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

	// モデルの奥側当たり判定
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

	// モデルの手前側当たり判定
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

	// 値を返す
	return bIsLanding;
}

//=============================================================================
// 当たり判定 (上側)
//=============================================================================
bool CObjectX::UpCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pSize, D3DXVECTOR3 * pMove)
{
	if (!m_isCollision)
	{
		return false;
	}

	// 変数宣言
	bool bIsLanding = false;

	// モデルの上側当たり判定
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

	// 値を返す
	return bIsLanding;
}

bool CObjectX::UpCollision(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * inMaxVtx, D3DXVECTOR3 * inMinVtx, D3DXVECTOR3 * pMove)
{
	if (!m_isCollision)
	{
		return false;
	}

	// 変数宣言
	bool bIsLanding = false;

	// モデルの上側当たり判定
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

	// 値を返す
	return bIsLanding;
}

//=============================================================================
// 頂点最大値設定処理
//=============================================================================
void CObjectX::SetMaxVtx(D3DXVECTOR3 Maxvtx)
{
	m_MaxVtx = Maxvtx;
}

//=============================================================================
// 頂点最小値設定処理
//=============================================================================
void CObjectX::SetMinVtx(D3DXVECTOR3 Minvtx)
{
	m_MinVtx = Minvtx;
}
