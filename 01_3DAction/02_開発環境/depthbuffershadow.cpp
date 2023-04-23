#include "depthbuffershadow.h"
#include "application.h"
#include "renderer.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デプスバッファシャドウのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CDepthBufferShadow::CDepthBufferShadow()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デプスバッファシャドウのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CDepthBufferShadow::~CDepthBufferShadow()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デプスバッファシャドウのfxファイルの読み込み
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CDepthBufferShadow::Load()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	if (SUCCEEDED(D3DXCreateEffectFromFile(pDevice, _T("DepthBufferShadow.fx"), NULL, NULL, 0, NULL, &m_pEffect, NULL)))
	{
		m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
		m_pWVP = m_pEffect->GetParameterByName(NULL, "m_WVP");
		m_pLWVP = m_pEffect->GetParameterByName(NULL, "m_LWVP");
		m_pLWVPT = m_pEffect->GetParameterByName(NULL, "m_LWVPT");
		m_pMatDiffuse = m_pEffect->GetParameterByName(NULL, "m_matDiffuse");
		m_pLightDir = m_pEffect->GetParameterByName(NULL, "m_LightDir");
		m_pAmbient = m_pEffect->GetParameterByName(NULL, "m_Ambient");
		m_pBias = m_pEffect->GetParameterByName(NULL, "m_Bias");
		m_pShadowColor = m_pEffect->GetParameterByName(NULL, "m_ShadowColor");

		m_pEffect->SetTechnique(m_pTechnique);
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デプスバッファシャドウの開始
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CDepthBufferShadow::Begin()
{
	if (m_pEffect == nullptr)
	{
		return;
	}

	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	pDevice->GetTransform(D3DTS_VIEW, &m_mtxView);
	pDevice->GetTransform(D3DTS_PROJECTION, &m_mtxProj);
	m_pEffect->Begin(NULL, 0);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デプスバッファシャドウのアンビエント設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CDepthBufferShadow::SetAmbient(float value)
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	if (m_pEffect != nullptr)
	{
		D3DXVECTOR4 A;
		A = D3DXVECTOR4(value, value, value, 1.0f);
		m_pEffect->SetVector(m_pAmbient, &A);
	}

	else
	{
		D3DMATERIAL9 old_material;
		pDevice->GetMaterial(&old_material);
		old_material.Ambient.r = value;
		old_material.Ambient.g = value;
		old_material.Ambient.b = value;
		old_material.Ambient.a = 1.0f;
		pDevice->SetMaterial(&old_material);
	}
}

void CDepthBufferShadow::SetAmbient(D3DXVECTOR4* value)
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	if (m_pEffect != nullptr)
	{
		m_pEffect->SetVector(m_pAmbient, value);
	}

	else
	{
		D3DMATERIAL9 old_material;
		pDevice->GetMaterial(&old_material);
		old_material.Ambient.r = value->x;
		old_material.Ambient.g = value->y;
		old_material.Ambient.b = value->z;
		old_material.Ambient.a = value->w;
		pDevice->SetMaterial(&old_material);
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// モデルのマテリアルのディフューズカラーの設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CDepthBufferShadow::SetDiffuse(D3DXVECTOR4 value)
{
	if (m_pEffect == nullptr)
	{
		return;
	}
	m_pEffect->SetVector(m_pMatDiffuse, &value);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デプスバッファシャドウのマトリックス設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CDepthBufferShadow::SetMatrix(D3DXMATRIX* pMatWorld, D3DXMATRIX* pMatLight, D3DXVECTOR4* pLightDir)
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	if (m_pEffect != nullptr)
	{
		D3DXMATRIX m, m1, m2;
		D3DXVECTOR4 LightDir;
		D3DXVECTOR4 v;

		//カメラ基準の行列変換マトリックスを設定
		m = (*pMatWorld) * m_mtxView * m_mtxProj;
		m_pEffect->SetMatrix(m_pWVP, &m);

		//ライトの方向ベクトル計算
		LightDir = *pLightDir;
		D3DXMatrixInverse(&m1, NULL, pMatWorld);
		D3DXVec4Transform(&v, &LightDir, &m1);

		//XYZ成分の正規化
		D3DXVec3Normalize((D3DXVECTOR3*)&v, (D3DXVECTOR3*)&v);
		m_pEffect->SetVector(m_pLightDir, &v);

		//ライト基準の行列変換マトリックスを設定
		m = (*pMatWorld) * (*pMatLight);
		m_pEffect->SetMatrix(m_pLWVP, &m);

		//ライト基準の行列変換マトリックスをテクスチャー座標系へ変換
		D3DXMatrixScaling(&m1, 0.5f, -0.5f, 1.0f);
		D3DXMatrixTranslation(&m2, 0.5f, 0.5f, 0.0f);
		m = m * m1 * m2;
		m_pEffect->SetMatrix(m_pLWVPT, &m);
	}
	else
	{
		pDevice->SetTransform(D3DTS_WORLD, pMatWorld);
	}
}
