#include "mode.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "tutorial.h"
#include "object.h"
#include "object2d.h"
#include "fade.h"
#include "char_ui.h"

CMode::EMode CMode::m_mode = MODE_NONE;
CObject *g_apObject = nullptr;
CObject2D *g_apObject2d = nullptr;
CTitle *CMode::m_pTitle = nullptr;
CGame *CMode::m_pGame = nullptr;
CResult *CMode::m_pResult = nullptr;
CTutorial *CMode::m_pTutorial = nullptr;
CBg *CMode::m_pBg = nullptr;
CCharUI *CMode::m_pCharUI = nullptr;
CFade *CMode::m_pFade = nullptr;
int CMode::m_nNewScore = 0;

CMode::CMode()
{
}

CMode::~CMode()
{
}

HRESULT CMode::Init()
{
	SetMode(MODE_TITLE);

	switch (GetMode())
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

	case MODE_TUTORIAL:
		m_pTutorial = new CTutorial;
		m_pTutorial->Init();
		break;

	default:
		break;
	}

	return S_OK;
}

void CMode::Uninit()
{
	//ƒtƒF[ƒh‚Ì”jŠü
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();

		delete m_pFade;
		m_pFade = nullptr;
	}

	//ƒ^ƒCƒgƒ‹‚Ì”jŠü
	if (m_pTitle != nullptr)
	{
		delete m_pTitle;
		m_pTitle = nullptr;
	}

	//ƒQ[ƒ€‚Ì”jŠü
	if (m_pGame != nullptr)
	{
		delete m_pGame;
		m_pGame = nullptr;
	}

	//ƒŠƒUƒ‹ƒg‚Ì”jŠü
	if (m_pResult != nullptr)
	{
		delete m_pResult;
		m_pResult = nullptr;
	}

	//ƒ`ƒ…[ƒgƒŠƒAƒ‹‚Ì”jŠü
	if (m_pTutorial != nullptr)
	{
		delete m_pTutorial;
		m_pTutorial = nullptr;
	}

	g_apObject->ReleaseAll();
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

	case MODE_TUTORIAL:
		m_pTutorial->Update();
		break;

	default:
		break;
	}
}

void CMode::SetMode(EMode mode)
{
	switch (GetMode())
	{
	case MODE_TITLE:
		//ƒ^ƒCƒgƒ‹‚Ì”jŠü
		if (m_pTitle != nullptr)
		{
			m_pTitle->Uninit();

			delete m_pTitle;
			m_pTitle = nullptr;
		}
		break;

	case MODE_GAME:
		//ƒQ[ƒ€‚Ì”jŠü
		if (m_pGame != nullptr)
		{
			m_pGame->Uninit();

			delete m_pGame;
			m_pGame = nullptr;
		}
		break;

	case MODE_RESULT:
		//ƒŠƒUƒ‹ƒg‚Ì”jŠü
		if (m_pResult != nullptr)
		{
			m_pResult->Uninit();

			delete m_pResult;
			m_pResult = nullptr;
		}
		break;

	case MODE_TUTORIAL:
		//ƒ`ƒ…[ƒgƒŠƒAƒ‹‚Ì”jŠü
		if (m_pTutorial != nullptr)
		{
			m_pTutorial->Uninit();

			delete m_pTutorial;
			m_pTutorial = nullptr;
		}
		break;

	default:
		break;
	}

	g_apObject->ReleaseAll();

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

	case MODE_TUTORIAL:
		m_pTutorial = new CTutorial;
		m_pTutorial->Init();
		break;

	default:
		break;
	}

	m_pFade->Create(0, CFade::FADE_OUT);
	m_mode = mode;
}