#include "main.h"
#include "input.h"
#include "keyboard.h"
#include "application.h"
#include "bg.h"
#include "bullet.h"
#include "particle_manager.h"
#include "player.h"
#include "enemy.h"
#include "renderer.h"
#include "texture.h"
#include "score.h"
#include "sound.h"
#include "mode.h"
#include "file.h"
#include "debugproc.h"

CEnemy *CApplication::m_pEnemy = nullptr;
CInputKeyboard *CApplication::m_pInputKeyboard = nullptr;
CItem *CApplication::m_pItem = nullptr;
CRenderer *CApplication::m_pRenderer = nullptr;
CSound *CApplication::m_pSound = nullptr;
CTexture *CApplication::m_pTexture = nullptr;
CDebugProc *CApplication::m_pDebugProc = nullptr;

CMode *CApplication::m_mode = nullptr;

CApplication::CApplication()
{

}

CApplication::~CApplication()
{

}

HRESULT CApplication::Init(HWND hWnd, HINSTANCE hInstance)
{
	//キーボードクラスの生成
	m_pInputKeyboard = new CInputKeyboard;

	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//レンダリングクラスの生成
	m_pRenderer = new CRenderer;

	// 初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

#ifdef _DEBUG
	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();
#endif

	//テクスチャクラスの生成
	m_pTexture = new CTexture;

	//サウンドクラスの生成
	m_pSound = new CSound;
	if (FAILED(m_pSound->Init(hWnd)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//モードクラスの生成
	m_mode = new CMode;

	if (FAILED(m_mode->Init()))
	{//初期化処理が失敗した場合
		return -1;
	}

	return S_OK;
}

void CApplication::Uninit()
{
#ifdef _DEBUG
	//デバッグプロシージャの破棄
	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Uninit();

		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}
#endif

	//テクスチャクラスの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->ReleaseAll();

		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//キーボードクラスの破棄
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//モードクラスの破棄
	if (m_mode != nullptr)
	{
		// 終了処理
		m_mode->Uninit();

		delete m_mode;
		m_mode = nullptr;
	}

	//レンダリングクラスの破棄
	if (m_pRenderer != nullptr)
	{
		// 終了処理
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//キーボードクラスの破棄
	if (m_pInputKeyboard != nullptr)
	{
		// 終了処理
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	//サウンドクラスの破棄
	if (m_pSound != nullptr)
	{
		// 終了処理
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = nullptr;
	}

}

void CApplication::Update()
{
	//キーボードの更新処理は最初に行う
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}

	m_pRenderer->Update();
	m_mode->Update();
}

void CApplication::Draw()
{
	m_pRenderer->Draw();
}