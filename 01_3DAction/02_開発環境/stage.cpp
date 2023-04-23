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

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ステージのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CStage::CStage() :
	m_bCollision(false)
{
	SetObjType(OBJTYPE_STAGE);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ステージのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CStage::~CStage()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ステージの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CStage * CStage::Create(D3DXVECTOR3 pos)
{
	CStage *pStage = nullptr;
	pStage = new CStage;

	//ヌルチェック
	if (pStage != nullptr)
	{
		// ポリゴンの初期化処理
		pStage->SetPos(pos);
		pStage->Init();
	}

	return pStage;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ステージの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CStage::Init()
{
	LoadModel("STAGE_COASTLANDS");

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ステージの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CStage::Uninit()
{
	//モデルデータが空じゃない場合
	if (!m_modelData.empty())
	{
		m_modelData.clear();
	}

	Destroy();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ステージの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CStage::Update()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	D3DXVECTOR3 posOld = m_objpos;

	// プレイヤーと敵の当たり判定
	CObject *pObject = CObject::GetTop(PRIORITY_THIRD);
	while (pObject != nullptr)
	{
		if (pObject == this)
		{
			pObject = pObject->GetNext();
			continue;
		}

		// オブジェクトのタイプを取得
		CObject::EObjType objType = pObject->GetObjType();
		m_bPlayer = false;

		// オブジェクトタイプがプレイヤーの場合
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
				{	// 現在のプレイヤーの位置から下への交差判定
					m_collisionPos = D3DXVECTOR3(m_collisionPos.x, m_hitPos.y - hitDistance * 0.5f, m_collisionPos.z);
					m_bCollision = true;
				}

				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(0.0f, 1.0f, 0.0f), (playerModelData.m_maxModel.y - playerModelData.m_minModel.y) * 0.5f, hitDistance, &overRange))
				{	// 現在のプレイヤーの位置から上への交差判定
					m_collisionPos = D3DXVECTOR3(m_collisionPos.x, m_hitPos.y + hitDistance * 0.5f, m_collisionPos.z);
					m_bCollision = true;

					if (isIntersect(m_modelData[i].m_mesh, pos + (playerModelData.m_maxModel - playerModelData.m_minModel), D3DXVECTOR3(0.0f, 1.0f, 0.0f), (playerModelData.m_maxModel.y - playerModelData.m_minModel.y) * 0.5f, hitDistance))
					{	// 斜めから変な隙間に入る対策
						pObj->SetPos(pObj->GetPosOld());
					}
				}
				if (overRange)
				{
					m_bCollision = true;
					//pObj->SetPos(pObj->GetPosOld());
				}

				// 参照する位置をプレイヤーの中心に調整する
				pos.y += (playerModelData.m_maxModel.y - playerModelData.m_minModel.y);

				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(1.0f, 0.0f, 0.0f), (playerModelData.m_maxModel.x - playerModelData.m_minModel.x) * 0.45f, hitDistance))
				{	// 現在のプレイヤーの位置から右への交差判定
					m_collisionPos = D3DXVECTOR3(m_hitPos.x - (hitDistance * 0.45f), m_collisionPos.y, m_hitPos.z);
					pObj->SetSpeed(0.0f);
					pObj->SetPos(m_collisionPos);
				}
				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(-1.0f, 0.0f, 0.0f), (playerModelData.m_maxModel.x - playerModelData.m_minModel.x) * 0.45f, hitDistance))
				{	// 現在のプレイヤーの位置から左への交差判定
					m_collisionPos = D3DXVECTOR3(m_hitPos.x + (hitDistance * 0.45f), m_collisionPos.y, m_hitPos.z);
					pObj->SetSpeed(0.0f);
					pObj->SetPos(m_collisionPos);
				}
				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(0.0f, 0.0f, 1.0f), (playerModelData.m_maxModel.z - playerModelData.m_minModel.z) * 0.45f, hitDistance))
				{	// 現在のプレイヤーの位置から奥への交差判定
					m_collisionPos = D3DXVECTOR3(m_hitPos.x, m_hitPos.y - (playerModelData.m_maxModel.y - playerModelData.m_minModel.y), m_hitPos.z - (hitDistance * 0.45f));
					pObj->SetSpeed(0.0f);
					pObj->SetPos(m_collisionPos);
				}
				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(0.0f, 0.0f, -1.0f), (playerModelData.m_maxModel.z - playerModelData.m_minModel.z) * 0.45f, hitDistance))
				{	// 現在のプレイヤーの位置から手前への交差判定
					m_collisionPos = D3DXVECTOR3(m_hitPos.x, m_hitPos.y - (playerModelData.m_maxModel.y - playerModelData.m_minModel.y), m_hitPos.z + (hitDistance  * 0.45f));
					pObj->SetSpeed(0.0f);
					pObj->SetPos(m_collisionPos);
				}
			}
		}

		// オブジェクトタイプが敵の場合
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
				{	// 現在の敵の位置から下への交差判定
					m_enemyCollisionPos = D3DXVECTOR3(m_enemyCollisionPos.x, m_enemyHitPos.y - hitDistance * 0.5f, m_enemyCollisionPos.z);
					pObj->SetCollisionPos(m_enemyCollisionPos);
					pObj->SetCollision(true);
				}

				if (isIntersect(m_modelData[i].m_mesh, pos, D3DXVECTOR3(0.0f, 1.0f, 0.0f), (enemyModelData.maxModel.y - enemyModelData.minModel.y), hitDistance, &overRange))
				{	// 現在の敵の位置から上への交差判定
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

		//ポインタを次に進める
		pObject = pObject->GetNext();
		
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ステージの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CStage::Draw()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ライトのポインタを取得
	CLight* pLight = CApplication::GetInstance()->GetMode()->GetGame()->GetLight();

	// テクスチャのポインタを取得
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

	// デプスバッファサーフェイスを参照し、オブジェクトと影をレンダリングする
	// デプスバッファサーフェイスのテクスチャーをサンプラ番号1にセットする
	pDevice->SetTexture(1, pShadow->GetZBufferTexture());

	pDepthBuffShadow->SetBias(0.0005f);
	pDepthBuffShadow->SetShadowColor(0.3f);
	pDepthBuffShadow->SetAmbient(0.3f);
	pDepthBuffShadow->Begin();
	pDepthBuffShadow->SetMatrix(&pShadow->GetMtxWorld(), &pShadow->GetWVP(), &pLight->GetVecDir());

	for (size_t i = 0; i < m_modelData.size(); i++)
	{
		D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
		D3DMATERIAL9 matDef;						// 現在のマテリアルを保存
		D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

		// 現在のマテリアルを保存
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_modelData[i].m_buffMat->GetBufferPointer();

		for (size_t j = 0; j < m_modelData[i].m_dwNum; j++)
		{
			// テクスチャの設定を戻す
			pDevice->SetTexture(0, NULL);

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[j].MatD3D);

			if (pMat[j].pTextureFilename != nullptr)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, pTexture->ConfirmLoadedPath(pMat[j].pTextureFilename));
			}

			pDepthBuffShadow->BeginPass(0);

			//モデルパーツの描画
			m_modelData[i].m_mesh->DrawSubset(j);

			pDepthBuffShadow->EndPass();
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

	pDepthBuffShadow->End();

	pDevice->SetTexture(1, NULL);

	// レンダーステートの設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// レイの衝突判定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
bool CStage::isIntersect(const LPD3DXMESH& mesh, D3DXVECTOR3 pos, D3DXVECTOR3 vecDir, float distanceRange, float& hitDistance, bool* overRange)
{
	BOOL isHit = false;
	DWORD hitIndex = -1;
	D3DXVECTOR2 UVHit;
	float Distance = 0.0f;

	// 目的の方向へレイを飛ばす
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
	{	// レイが交差しなかった場合
		return false;
	}
		
	if (Distance == 0.0f)
	{	// 交差した距離が０の場合
		return false;
	}

	if (Distance >= distanceRange)
	{	// 距離が特定の距離より遠かった場合
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
	{	// 数値がnanになった場合
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

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ステージのモデルデータを取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CStage::LoadModel(std::string path)
{
	// モデルデータのポインタを取得
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