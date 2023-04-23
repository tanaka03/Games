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
	// �t�F�[�h�̔j��
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();

		delete m_pFade;
		m_pFade = nullptr;
	}

	// �^�C�g���̔j��
	if (m_pTitle != nullptr)
	{
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = nullptr;
	}

	// �Q�[���̔j��
	if (m_pGame != nullptr)
	{
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = nullptr;
	}

	// ���U���g�̔j��
	if (m_pResult != nullptr)
	{
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = nullptr;
	}

	// �R���e�B�j���[�̔j��
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
		// �^�C�g���̔j��
		if (m_pTitle != nullptr)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = nullptr;
		}
		break;

	case MODE_GAME:
		// �Q�[���̔j��
		if (m_pGame != nullptr)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = nullptr;
		}
		break;

	case MODE_RESULT:
		// ���U���g�̔j��
		if (m_pResult != nullptr)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = nullptr;
		}
		break;

	case MODE_CONTINUE:
		// �R���e�B�j���[�̔j��
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