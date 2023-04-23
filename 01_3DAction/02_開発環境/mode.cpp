#include "mode.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "continue.h"
#include "object.h"
#include "object2d.h"
#include "fade.h"

CMode::CMode() : 
	m_mode(MODE_TITLE)
{
}

CMode::~CMode()
{
}

HRESULT CMode::Init()
{
	switch (m_mode)
	{
	case MODE_TITLE:
		m_pTitle = new CTitle;
		m_pTitle->Init();
		break;

	case MODE_GAME:
		m_pGame = new CGame;
		m_pGame->Init();
		break;

	case MODE_RESULT:
		m_pResult = new CResult;
		m_pResult->Init();
		break;

	case MODE_CONTINUE:
		m_pContinue = new CContinue;
		m_pContinue->Init();

	default:
		break;
	}

	return S_OK;
}

void CMode::Uninit()
{
	// フェードの破棄
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();

		delete m_pFade;
		m_pFade = nullptr;
	}

	// タイトルの破棄
	if (m_pTitle != nullptr)
	{
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = nullptr;
	}

	// ゲームの破棄
	if (m_pGame != nullptr)
	{
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = nullptr;
	}

	// リザルトの破棄
	if (m_pResult != nullptr)
	{
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = nullptr;
	}

	// コンティニューの破棄
	if (m_pContinue != nullptr)
	{
		m_pContinue->Uninit();
		delete m_pContinue;
		m_pContinue = nullptr;
	}
}

void CMode::Update()
{
	if (m_pFade != nullptr)
	{
		m_pFade->Update();
	}

	switch (GetMode())
	{
	case MODE_TITLE:
		m_pTitle->Update();
		break;

	case MODE_GAME:
		m_pGame->Update();
		break;

	case MODE_RESULT:
		m_pResult->Update();
		break;

	case MODE_CONTINUE:
		m_pContinue->Update();
		break;

	default:
		break;
	}
}

void CMode::SetMode(EMode mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		// タイトルの破棄
		if (m_pTitle != nullptr)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = nullptr;
		}
		break;

	case MODE_GAME:
		// ゲームの破棄
		if (m_pGame != nullptr)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = nullptr;
		}
		break;

	case MODE_RESULT:
		// リザルトの破棄
		if (m_pResult != nullptr)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = nullptr;
		}
		break;

	case MODE_CONTINUE:
		// コンティニューの破棄
		if (m_pContinue != nullptr)
		{
			m_pContinue->Uninit();
			delete m_pContinue;
			m_pContinue = nullptr;
		}
		break;

	default:
		assert(false);
		break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = new CTitle;
		m_pTitle->Init();
		break;

	case MODE_GAME:
		m_pGame = new CGame;
		m_pGame->Init();
		break;

	case MODE_RESULT:
		m_pResult = new CResult;
		m_pResult->Init();
		break;

	case MODE_CONTINUE:
		m_pContinue = new CContinue;
		m_pContinue->Init();
		break;

	default:
		assert(false);
		break;
	}

	m_mode = mode;
}