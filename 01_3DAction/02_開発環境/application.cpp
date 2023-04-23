#include "application.h"
#include "renderer.h"
#include "texture.h"
#include "keyboard.h"
#include "camera.h"
#include "light.h"
#include "object.h"
#include "object3d.h"
#include "player.h"
#include "file.h"
#include "model.h"
#include "meshfield.h"
#include "enemy.h"
#include "utility.h"
#include "mode.h"
#include "objectX_group.h"
#include "3deffect_manager.h"
#include "enemy_manager.h"
#include "particle_manager.h"
#include "sound.h"

#include "debugproc.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// 静的メンバ変数宣言
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CApplication* CApplication::m_pApplication = nullptr;

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// グローバル変数宣言
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CObject *g_apObject = nullptr;
CObject3D *g_apObject3d = nullptr;

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// シングルトンでインスタンスの生成、取得
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CApplication* CApplication::GetInstance()
{
	if (m_pApplication == nullptr)
	{
		m_pApplication = new CApplication;
	}

	return m_pApplication;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アプリケーションのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CApplication::CApplication() :
	m_pRenderer(nullptr)
{
	m_bWire = false;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アプリケーションのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CApplication::~CApplication()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アプリケーションの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CApplication::Init(HWND hWnd, HINSTANCE hInstance)
{
	srand(time(0));

	//レンダリングクラスの生成
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

#ifdef _DEBUG
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();
#endif

	//キーボードクラスの生成
	m_pInputKeyboard = new CInputKeyboard;
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//ファイルクラスの生成
	m_pFile = new CFile;

	//ユーティリティクラスの生成
	m_pUtility = new CUtility;

	//テクスチャクラスの生成
	m_pTexture = new CTexture;
	m_pTexture->LoadAll();

	//モデルクラスの生成
	m_pModel = new CModel;
	m_pModel->LoadAll();

	// サウンドクラスの生成
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	// モデルの生成
	m_pObjectXGroup = new CObjectXGroup;
	m_pObjectXGroup->LoadAll();

	// エフェクトマネージャの生成
	m_pEffectManager = new C3DEffectManager;
	m_pEffectManager->LoadAll();

	// パーティクルマネージャの生成
	m_pParticleManager = new CParticleManager;
	m_pParticleManager->LoadAll();

	// エネミーマネージャの生成
	m_pEnemyManager = new CEnemyManager;
	m_pEnemyManager->LoadAll();

	//モードクラスの生成
	m_pMode = new CMode;
	if (FAILED(m_pMode->Init()))
	{//初期化処理が失敗した場合
		return -1;
	}

	//カメラクラスの生成
	m_pCamera = new CCamera;
	m_pCamera->Init();

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アプリケーションの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CApplication::Uninit()
{
#ifdef _DEBUG
	// デバッグプロシージャの破棄
	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}
#endif

	CObject::ReleaseAll();

	// モードクラスの破棄
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	// ユーティリティクラスの破棄
	if (m_pUtility != nullptr)
	{
		delete m_pUtility;
		m_pUtility = nullptr;
	}

	// エフェクトマネージャの破棄
	if (m_pEffectManager != nullptr)
	{
		m_pEffectManager->ReleaseAll();
		delete m_pEffectManager;
		m_pEffectManager = nullptr;
	}

	// パーティクルマネージャの破棄
	if (m_pParticleManager != nullptr)
	{
		m_pParticleManager->ReleaseAll();
		delete m_pParticleManager;
		m_pParticleManager = nullptr;
	}

	// エネミーマネージャの破棄
	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager->ReleaseAll();
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
	}

	// テクスチャクラスの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->UnloadAll();

		delete m_pTexture;
		m_pTexture = nullptr;
	}

	// モデルクラスの破棄
	if (m_pModel != nullptr)
	{
		m_pModel->Clear();
		delete m_pModel;
		m_pModel = nullptr;
	}

	// サウンドクラスの破棄
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	// Xモデルの削除
	if (m_pObjectXGroup != nullptr)
	{
		m_pObjectXGroup->UnloadAll();
		delete m_pObjectXGroup;
		m_pObjectXGroup = nullptr;
	}

	// カメラクラスの破棄
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// キーボードクラスの破棄
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	// レンダリングクラスの破棄
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// ファイルクラスの破棄
	if (m_pFile != nullptr)
	{
		delete m_pFile;
		m_pFile = nullptr;
	}

	// アプリケーションの解放
	if (m_pApplication != nullptr)
	{
		delete m_pApplication;
		m_pApplication = nullptr;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アプリケーションの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CApplication::Update()
{
	// キーボードの更新処理は最初に行う
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	// レンダラークラスの更新
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	// モードクラスの更新
	if (m_pMode != nullptr)
	{
		m_pMode->Update();
	}

	// ワイヤーフレームにする処理
	if (m_pInputKeyboard->GetTrigger(DIK_F2))
	{
		m_bWire = ((!m_bWire) ? true : false);
		if (m_bWire)		m_pRenderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else if (!m_bWire)	m_pRenderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// アプリケーションの描画
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CApplication::Draw()
{
	// レンダラークラスの描画
	m_pRenderer->Draw();
}