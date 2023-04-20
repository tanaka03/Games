#include "title.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "texture.h"
#include "bg.h"
#include "sound.h"
#include "char_ui.h"

#define MAX_SELECT	(4)

CTitle::CTitle()
{
	SetNewScore(0);
}

CTitle::~CTitle()
{
}

HRESULT CTitle::Init()
{
	//”wŒiƒNƒ‰ƒX‚Ì¶¬
	m_pBg[0] = m_pBg[0]->Create(CBg::BG_TITLE, false);
	m_pBg[0]->SetScroll(true, 0.001f, true);

	m_pBg[1] = m_pBg[1]->Create(CBg::BG_TITLELACE1, false);
	m_pBg[1]->SetScroll(true, 0.003f, true);

	//•¶ŽšUIƒNƒ‰ƒX‚Ì¶¬
	m_pCharUI[0] = m_pCharUI[0]->Create(D3DXVECTOR3(300.0f, 100.0f, 0.0f), D3DXVECTOR2(350, 60), CCharUI::UI_TITLELOGO, CCharUI::STATE_SELECT);
	m_pCharUI[1] = m_pCharUI[1]->Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + 400.0f, (SCREEN_HEIGHT / 3) + 150.0f, 0.0f), D3DXVECTOR2(200, 35), CCharUI::UI_START, CCharUI::STATE_BLINK);
	m_pCharUI[2] = m_pCharUI[2]->Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + 400.0f, (SCREEN_HEIGHT / 3) + 250.0f, 0.0f), D3DXVECTOR2(200, 65), CCharUI::UI_TUTORIAL, CCharUI::STATE_BLINK);
	m_pCharUI[3] = m_pCharUI[3]->Create(D3DXVECTOR3((SCREEN_WIDTH / 2) + 400.0f, (SCREEN_HEIGHT / 3) + 350.0f, 0.0f), D3DXVECTOR2(200, 35), CCharUI::UI_QUIT, CCharUI::STATE_BLINK);

	CApplication::GetSound()->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);
	m_nSelect = 1;
	return S_OK;
}

void CTitle::Uninit()
{
}

void CTitle::Update()
{
	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_W))
	{
		if (m_nSelect > 1)
		{
			m_nSelect--;
		}
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_S))
	{
		m_nSelect++;
		if (m_nSelect >= MAX_SELECT)
		{
			m_nSelect = 3;
		}
	}

	m_pCharUI[m_nSelect]->SetCharState(CCharUI::STATE_SELECT);

	for (int i = 1; i < MAX_SELECT; i++)
	{
		if (m_nSelect == i)
		{
			continue;
		}

		m_pCharUI[i]->SetCharState(CCharUI::STATE_INVALID);
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		switch (m_nSelect)
		{
		case SELECT_START:
			SetMode(MODE_GAME);
			CApplication::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
			CApplication::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);
			break;

		case SELECT_TUTORIAL:
			SetMode(MODE_TUTORIAL);
			CApplication::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
			CApplication::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT);
			break;

		case SELECT_QUIT:
			PostQuitMessage(WM_QUIT);
			break;

		default:
			break;
		}
	}
}