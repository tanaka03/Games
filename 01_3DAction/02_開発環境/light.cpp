//＝＝＝＝＝＝＝＝＝＝＝＝＝
//light.cpp
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "light.h"
#include "application.h"
#include "renderer.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ライトのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CLight::CLight()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ライトのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CLight::~CLight()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ライトの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DMATERIAL9 material;
	memset(&material, 0, sizeof(D3DMATERIAL9));

	//ライトをクリアする
	memset(&m_light, 0, sizeof(D3DLIGHT9));

	D3DXMATRIX mtxRot;

	//平行光源の回転マトリックス
	D3DXMatrixIdentity(&m_lightMatrix);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, D3DXToRadian(180.0f), D3DXToRadian(90.0f), 0.0f);
	D3DXMatrixMultiply(&m_lightMatrix, &m_lightMatrix, &mtxRot);

	D3DXVec3TransformCoord((D3DXVECTOR3*)&m_lightAim, (D3DXVECTOR3*)&m_lightAim, &m_lightMatrix);
	D3DXVec3TransformCoord((D3DXVECTOR3*)&m_lightUp, (D3DXVECTOR3*)&m_lightUp, &m_lightMatrix);
	D3DXVec3TransformCoord((D3DXVECTOR3*)&m_lightAt, (D3DXVECTOR3*)&m_lightAt, &m_lightMatrix);

	//ライトの方向ベクトルを計算
	m_lightDir = m_lightAt - m_lightAim;

	//m_lightAim.y += 6.5f;
	m_lightAim.z += 0.6f;

	//----------------------------------------------------------
	// １つ目のライトを設定
	//----------------------------------------------------------
	//ライトの種類を設定
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光を設定
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//正規化する
	D3DXVec3Normalize((D3DXVECTOR3*)&m_lightDir, (D3DXVECTOR3*)&m_lightDir);
	m_light[0].Direction = (D3DXVECTOR3)m_lightDir;

	//ライトを設定する
	pDevice->SetLight(0, &m_light[0]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ライトの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CLight::Uninit()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// ライトの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CLight::Update()
{
}