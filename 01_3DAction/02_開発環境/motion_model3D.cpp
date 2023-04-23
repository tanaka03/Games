//=============================================================================
//
// モーションキャラクター3Dクラス(model3D.h)
// Author : 唐﨑結斗
// 概要 : モーションキャラクター3D生成を行う
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <assert.h>

#include "motion_model3D.h"
#include "motion.h"
#include "renderer.h"
#include "application.h"
#include "objectX.h"
#include "parts.h"

//=============================================================================
// インスタンス生成
// Author : 唐﨑結斗
// 概要 : モーションキャラクター3Dを生成する
//=============================================================================
CMotionModel3D * CMotionModel3D::Create()
{
	// オブジェクトインスタンス
	CMotionModel3D *pMotionModel3D = nullptr;

	// メモリの解放
	pMotionModel3D = new CMotionModel3D;

	// メモリの確保ができなかった
	assert(pMotionModel3D != nullptr);

	// 数値の初期化
	pMotionModel3D->Init();

	// インスタンスを返す
	return pMotionModel3D;
}

//=============================================================================
// コンストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス生成時に行う処理
//=============================================================================
CMotionModel3D::CMotionModel3D() :
	m_pMotion(nullptr),		// モーション情報
	m_mtxWorld(D3DXMATRIX()),									// ワールドマトリックス
	m_pos(D3DXVECTOR3()),										// 位置
	m_rot(D3DXVECTOR3()),										// 向き
	m_size(D3DXVECTOR3()),										// 大きさ
	m_isUpdateStop(false)
{
}

//=============================================================================
// デストラクタ
// Author : 唐﨑結斗
// 概要 : インスタンス終了時に行う処理
//=============================================================================
CMotionModel3D::~CMotionModel3D()
{
	assert(m_pMotion == nullptr);
}

//=============================================================================
// 初期化
// Author : 唐﨑結斗
// 概要 : 頂点バッファを生成し、メンバ変数の初期値を設定
//=============================================================================
HRESULT CMotionModel3D::Init()
{
	// 変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向き

	return E_NOTIMPL;
}

//=============================================================================
// 終了
// Author : 唐﨑結斗
// 概要 : テクスチャのポインタと頂点バッファの解放
//=============================================================================
void CMotionModel3D::Uninit()
{
	if (m_pMotion != nullptr)
	{// 終了処理
		m_pMotion->Uninit();

		// メモリの解放
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// オブジェクト2Dの解放
	Destroy();
}

//=============================================================================
// 更新
// Author : 唐﨑結斗
// 概要 : 2D更新を行う
//=============================================================================
void CMotionModel3D::Update()
{
	if (m_pMotion != nullptr)
	{// モーション番号の設定
		if (!m_isUpdateStop)
		{
			m_pMotion->Update();
		}
	}
}

//=============================================================================
// モーションの設定
// Author : 唐﨑結斗
// 概要 : モーションの読み込みを行う
//=============================================================================
void CMotionModel3D::SetMotion(const char * pName)
{
	if (m_pMotion != nullptr)
	{// 終了処理
		m_pMotion->Uninit();

		// メモリの解放
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// モーション情報
	m_pMotion = new CMotion(pName);
	assert(m_pMotion != nullptr);

	// モーションの初期設定
	m_pMotion->SetMotion(0);

	// モーション番号の設定
	m_pMotion->SetNumMotion(0);

	SetMaxMinVtx();
}

void CMotionModel3D::SetMaxMinVtx()
{

	D3DXVECTOR3 minVtx(FLT_MAX, FLT_MAX, FLT_MAX);
	D3DXVECTOR3 maxVtx(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int nCntParts = 0; nCntParts < m_pMotion->GetMaxParts(); nCntParts++)
	{
		D3DXVECTOR3 partsMinVtx = m_pMotion->GetParts(nCntParts)->GetMinVtx();
		D3DXVECTOR3 partsMaxVtx = m_pMotion->GetParts(nCntParts)->GetMaxVtx();

		//X
		if (partsMinVtx.x < minVtx.x)
		{//最小値
			minVtx.x = partsMinVtx.x;
		}
		if (partsMaxVtx.x > maxVtx.x)
		{//最大値
			maxVtx.x = partsMaxVtx.x;
		}

		//Y
		if (partsMinVtx.y < minVtx.y)
		{//最小値
			minVtx.y = partsMinVtx.y;
		}
		if (partsMaxVtx.y > maxVtx.y)
		{//最大値
			maxVtx.y = partsMaxVtx.y;
		}

		//Z
		if (partsMinVtx.z < minVtx.z)
		{//最小値
			minVtx.z = partsMinVtx.z;
		}
		if (partsMaxVtx.z > maxVtx.z)
		{//最大値
			maxVtx.z = partsMaxVtx.z;
		}
	}

	m_MinVtx = minVtx;
	m_MaxVtx = maxVtx;
}

float CMotionModel3D::LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	float r1 = fabs(D3DXVec3Dot(Sep, e1));
	float r2 = fabs(D3DXVec3Dot(Sep, e2));
	float r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
	return r1 + r2 + r3;
}
