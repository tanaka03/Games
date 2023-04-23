//＝＝＝＝＝＝＝＝＝＝＝＝＝
//camera.cpp
//＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "application.h"
#include "camera.h"
#include "input.h"
#include "keyboard.h"
#include "player.h"
#include "game.h"
#include "utility.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// カメラのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CCamera::CCamera() : 
	m_quakeFrameCount(0),
	m_quakeMagnitude(0.0f),
	m_bTraction(false)
{
	memset(&m_camera, 0, sizeof(CCamera));
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// カメラのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CCamera::~CCamera()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// カメラの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CCamera::Init()
{
	//視点・注視点・上方向を設定する
	m_camera.posV = D3DXVECTOR3(0.0f, 900.0f, 900.0f);	//視点
	m_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の視点
	m_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//注視点
	m_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の注視点
	m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//上方向ベクトル
	m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//目的の向き

	float x = m_camera.posR.x - m_camera.posV.x;
	float z = m_camera.posR.z - m_camera.posV.z;
	m_camera.fDistance = sqrtf((x * x) + (z * z));		//視点から注視点の距離

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// カメラの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CCamera::Uninit()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// カメラの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CCamera::Update()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();
	D3DXMATRIX mtxTrans, mtxRot;

	//----------------------------------------------------------
	// カメラの注視点
	//----------------------------------------------------------
	//左
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_Q))
	{
		m_camera.rot.y -= 0.05f;
	}

	//右
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_E))
	{
		m_camera.rot.y += 0.05f;
	}

	//----------------------------------------------------------
	// カメラの視点
	//----------------------------------------------------------
	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_R))
	{
		m_camera.posV.y -= 0.5f * 8;
		m_camera.posV.z -= 1.5f * 8;
	}

	if (CApplication::GetInstance()->GetInputKeyboard()->GetPress(DIK_F))
	{
		m_camera.posV.y += 0.5f * 8;
		m_camera.posV.z += 1.5f * 8;
	}

	D3DXVECTOR3 pos;

	if (!CApplication::GetInstance()->GetMode()->GetGame()->GetDeath())
	{
		pos = pPlayer->GetPos();
	}
	if (CApplication::GetInstance()->GetMode()->GetGame()->GetDeath())
	{
		pos = m_posOld;
	}
	m_posOld = pos;

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_camera.rot.y, m_camera.rot.x, m_camera.rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	D3DXVec3TransformCoord(&m_worldposV, &m_camera.posV, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_worldposR, &m_camera.posR, &m_mtxWorld);

	//----------------------------------------------------------
	// 正規化
	//----------------------------------------------------------
	CUtility::angleNormalize(m_camera.rot.y);
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// カメラの設定
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_camera.mtxView);

	D3DXVECTOR3 adjustPos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	if (m_quakeFrameCount > 0)
	{
		adjustPos = D3DXVECTOR3(rand() % 20 * m_quakeMagnitude, rand() % 20 * m_quakeMagnitude, rand() % 20 * m_quakeMagnitude);
	}

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_camera.mtxView,
		&(m_worldposV + adjustPos),
		&(m_worldposR + adjustPos),
		&m_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		5.0f,
		50000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_camera.mtxProjection);
}