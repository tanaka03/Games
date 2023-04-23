#include "shadow.h"
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "object.h"
#include "mode.h"
#include "game.h"
#include "object2d.h"
#include "keyboard.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 影のコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CShadow::CShadow() : lightEnlargement(15200.0f)
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 影のデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CShadow::~CShadow()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ライト視点で世界を見る処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CShadow::StartViewfromLight()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ライトのポインタを取得
	CLight* pLight = CApplication::GetInstance()->GetMode()->GetGame()->GetLight();

	// ライトからの視点の設定
	D3DXVECTOR3 LEye = D3DXVECTOR3(pLight->GetLightAim().x, pLight->GetLightAim().y , pLight->GetLightAim().z) * lightEnlargement;
	D3DXVECTOR4 LightDir = pLight->GetVecDir();

	// デプスバッファサーフェイスにライト位置からのシーンのZ値を出力
	D3DXMatrixLookAtLH(&m_mtxView, &LEye, (D3DXVECTOR3*)&pLight->GetLightAt(), (D3DXVECTOR3*)&pLight->GetLightUp());

	// ライト位置からの正射影行列の作成
	D3DXMatrixOrthoLH(&m_mtxProj,
		(float)SCREEN_WIDTH * 15,
		(float)SCREEN_HEIGHT * 15,
		100.0f,
		20000.0f);

	D3DXMatrixIdentity(&m_mtxWorld);
	m_calcWVP = m_mtxWorld * m_mtxView * m_mtxProj;

	// サンプラーステートの設定
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	//アルファブレンドによる合成方法を線形合成にする
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//この値とテクスチャーのアルファ値とを比較する
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000080);

	// テクスチャのアルファ値より大きかった場合書き込み
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//レンダーターゲットサーフェイスを設定する
	pDevice->GetRenderTarget(0, &m_oldSurface);
	pDevice->SetRenderTarget(0, m_pZBufferSurface);

	pDevice->GetDepthStencilSurface(&m_oldZMap);
	pDevice->SetDepthStencilSurface(m_pZBuffer);

	// レンダーターゲットを変えた場合、クリアする
	pDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		0xFFFFFFFF,
		1.0f,
		0L
	);
}

void CShadow::StartViewfromLight(D3DXMATRIX& mtxWorld)
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ライトのポインタを取得
	CLight* pLight = CApplication::GetInstance()->GetMode()->GetGame()->GetLight();

	// ライトからの視点の設定
	D3DXVECTOR3 LEye = D3DXVECTOR3(pLight->GetLightAim().x, pLight->GetLightAim().y, pLight->GetLightAim().z) * lightEnlargement;
	D3DXVECTOR4 LightDir = pLight->GetVecDir();

	// デプスバッファサーフェイスにライト位置からのシーンのZ値を出力
	D3DXMatrixLookAtLH(&m_mtxView, &LEye, (D3DXVECTOR3*)&pLight->GetLightAt(), (D3DXVECTOR3*)&pLight->GetLightUp());

	// ライト位置からの正射影行列の作成
	D3DXMatrixOrthoLH(&m_mtxProj,
		(float)SCREEN_WIDTH * 10,
		(float)SCREEN_HEIGHT * 10,
		100.0f,
		9000.0f);

	D3DXMatrixIdentity(&m_mtxWorld);
	m_calcWVP = mtxWorld * m_mtxView * m_mtxProj;

	// サンプラーステートの設定
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	pDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	//アルファブレンドによる合成方法を線形合成にする
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//この値とテクスチャーのアルファ値とを比較する
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000080);

	// テクスチャのアルファ値より大きかった場合書き込み
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	//レンダーターゲットサーフェイスを設定する
	pDevice->GetRenderTarget(0, &m_oldSurface);
	pDevice->SetRenderTarget(0, m_pZBufferSurface);

	pDevice->GetDepthStencilSurface(&m_oldZMap);
	pDevice->SetDepthStencilSurface(m_pZBuffer);

	// レンダーターゲットを変えた場合、クリアする
	pDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		0xFFFFFFFF,
		1.0f,
		0L
	);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ライト視点の処理を終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CShadow::EndViewfromLight()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//m_pTex->SetTexture(m_pZBufferTexture);

	pDevice->SetRenderTarget(0, m_oldSurface);
	if (m_oldSurface != nullptr)
	{
		m_oldSurface->Release();
	}

	pDevice->SetDepthStencilSurface(m_oldZMap);
	if (m_oldZMap != nullptr)
	{
		m_oldZMap->Release();
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 深度テクスチャの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CShadow::CreateZTexture()
{
	// デバイスのポインタを取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	DWORD SurfaceWidth = (DWORD)SCREEN_WIDTH * 2.5f;
	DWORD SurfaceHeight = (DWORD)SCREEN_HEIGHT * 2.5f;

	HRESULT hr;

	// テクスチャの生成
	hr = D3DXCreateTexture(pDevice,
		SurfaceWidth,
		SurfaceHeight,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_R32F,
		D3DPOOL_DEFAULT,
		&m_pZBufferTexture);

	if (hr == E_FAIL)
	{	// テクスチャを生成できなかった場合
		assert(false);
	}

	m_pZBufferTexture->GetSurfaceLevel(0, &m_pZBufferSurface);

	// 深度ステンシルの生成
	hr = pDevice->CreateDepthStencilSurface(SurfaceWidth,
		SurfaceHeight,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pZBuffer,
		NULL);

	if (hr == E_FAIL)
	{	// ステンシルのサーフェイスを生成できなかった場合
		assert(false);
	}
}