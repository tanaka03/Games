#include "application.h"
#include "object3d.h"
#include "texture.h"
#include "3deffect.h"
#include "model.h"
#include "game.h"
#include "player.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
C3DEffect::C3DEffect(int nPriority)
{
	SetObjState(CObject::OBJSTATE_3D);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
C3DEffect::~C3DEffect()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
C3DEffect * C3DEffect::Create(C3DEffect::SInfo& info, int priority)
{
	C3DEffect *pObj = nullptr;
	pObj = new C3DEffect(priority);

	//ヌルチェック
	if (pObj != nullptr)
	{
		pObj->m_info = info;
		pObj->BindTexture(info.texTag);
		pObj->LoadModel(info.modelShape);
		pObj->Init();
	}

	return pObj;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT C3DEffect::Init()
{
	for (size_t i = 0; i < m_modelData.size(); i++)
	{
		m_modelData[i].posOffset = m_info.posOffset;
		m_modelData[i].rotOffset = m_info.rotOffset;
	}

	m_beginCol = m_info.col;
	m_rot = m_info.beginRot;
	m_scale = m_info.beginScale;

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C3DEffect::Uninit()
{
	//モデルデータが空じゃない場合
	if (!m_modelData.empty())
	{
		m_modelData.clear();
	}

	Destroy();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C3DEffect::Update()
{
	{
		// 移動の減衰量
		m_info.moveValue *= m_info.moveAttenuation;

		// 移動量
		m_pos.x += m_info.moveValue.x;
		m_pos.y += m_info.moveValue.y;
		m_pos.z += m_info.moveValue.z;

		// 回転量
		m_rot.x += m_info.rotateValue.x;
		m_rot.y += m_info.rotateValue.y;
		m_rot.z += m_info.rotateValue.z;

		// 拡縮量
		m_scale.x += m_info.scalingValue.x;
		m_scale.y += m_info.scalingValue.y;
		m_scale.z += m_info.scalingValue.z;

		// 色の遷移
		if (m_info.transitionCol.r != 1.0f &&
			m_info.transitionCol.g != 1.0f &&
			m_info.transitionCol.b != 1.0f)
		{
			m_info.col.r += (m_info.transitionCol.r - m_beginCol.r) / m_info.transitionColEndTime;
			m_info.col.g += (m_info.transitionCol.g - m_beginCol.g) / m_info.transitionColEndTime;
			m_info.col.b += (m_info.transitionCol.b - m_beginCol.b) / m_info.transitionColEndTime;
		}

		// アルファ値の減衰量
		m_info.col.a -= m_info.alphaAttenuation;
	}

	// エミッタからの生成ではない場合
	if (!m_useEmitter)
	{
		m_info.life--;

		if (m_info.life <= 0)
		{
			Destroy();
		}
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C3DEffect::Draw()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;				//計算用マトリックス

	// Zテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテスト
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if (m_info.tractPlayer)
	{
		CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

		// ワールドマトリックスを初期化
		D3DXMatrixIdentity(&m_ParentmtxWorld);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_ParentmtxWorld, &m_ParentmtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_ParentmtxWorld, &m_ParentmtxWorld, &mtxTrans);

		D3DXMatrixMultiply(&m_ParentmtxWorld, &m_ParentmtxWorld, &pPlayer->GetMatrix());

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_ParentmtxWorld);
	}
	else
	{
		// ワールドマトリックスを初期化
		D3DXMatrixIdentity(&m_ParentmtxWorld);

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_ParentmtxWorld, &m_ParentmtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_ParentmtxWorld, &m_ParentmtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_ParentmtxWorld);
	}

	for (size_t i = 0; i < m_modelData.size(); i++)
	{
		// デバイスのポインタを取得
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

		D3DXMATRIX parent = m_ParentmtxWorld;		// プレイヤーの位置を取得
		D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
		D3DMATERIAL9 matDef;						// 現在のマテリアルを保存
		D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

		//テクスチャの設定を戻す
		pDevice->SetTexture(0, NULL);

		//ワールドマトリックスを初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_modelData[i].rotOffset.y, m_modelData[i].rotOffset.x, m_modelData[i].rotOffset.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_modelData[i].posOffset.x, m_modelData[i].posOffset.y, m_modelData[i].posOffset.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// 行列拡縮関数
		D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

		//親のマトリックスをプレイヤーにする
		pDevice->GetTransform(D3DTS_WORLD, &parent);

		//親のマトリックスとかけ合わせる
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &parent);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//現在のマテリアルを保存
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_modelData[i].buffMat->GetBufferPointer();

		for (size_t j = 0; j < m_modelData[i].dwNum; j++)
		{
			//マテリアルの設定
			pMat[j].MatD3D.Diffuse = m_info.col;
			pMat[j].MatD3D.Emissive = m_info.col;
			pDevice->SetMaterial(&pMat[j].MatD3D);

			if (pMat[j].pTextureFilename != nullptr && m_info.useFileTexture)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, pTexture->ConfirmLoadedPath(pMat[j].pTextureFilename));
			}

			//テクスチャの設定
			pDevice->SetTexture(0, m_pTexture);

			//モデルパーツの描画
			m_modelData[i].mesh->DrawSubset(j);
		}

		//保持していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

	// Zバッファの設定を元に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトのモデルデータを取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C3DEffect::LoadModel(std::string path)
{
	// モデルデータのポインタを取得
	CModel *pModel = CApplication::GetInstance()->GetModel();

	SModelData data = {};

	data.mesh = pModel->GetMesh(path);
	data.buffMat = pModel->GetBuffMat(path);
	data.dwNum = pModel->GetModelNum(path);
	data.maxModel = pModel->GetMaxModel(path);
	data.minModel = pModel->GetMinModel(path);
	data.numVtx = pModel->GetVertexCount(path);
	data.numPrim = pModel->GetPrimitiveCount(path);

	m_modelData.push_back(data);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 3Dエフェクトのテクスチャをバインド
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void C3DEffect::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		//テクスチャのポインタ
}