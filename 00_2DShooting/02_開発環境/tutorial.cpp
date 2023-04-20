#include "tutorial.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "score.h"
#include "file.h"
#include "char_ui.h"
#include "player.h"
#include "file.h"
#include "bg.h"

CTutorial::CTutorial()
{
	m_nCntSkip = 0;
	m_nTime = 0;
	m_nTutorialNum = 0;
}

CTutorial::~CTutorial()
{
}

HRESULT CTutorial::Init()
{
	//ファイルクラスの生成
	m_pFile = new CFile;

	//背景クラスの生成
	m_pBg[0] = m_pBg[0]->Create(CBg::BG_TUTORIAL, true);
	m_pBg[0]->SetScroll(true);
	m_pBg[0]->SetRange(D3DXVECTOR2(2.0f, 2.0f));

	//背景クラスの生成
	m_pBg[1] = m_pBg[1]->Create(CBg::BG_GAMECLOUD, false);
	m_pBg[1]->SetScroll(true, 0.009f);
	m_pBg[1]->SetAlpha(0.6f);

	//プレイヤークラスの生成
	m_pPlayer->Create();

	return S_OK;
}

void CTutorial::Uninit()
{
}

void CTutorial::Update()
{
	m_nTime++;

	if (m_nTime == 50)
	{
		m_pCharUI = m_pCharUI->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 180.0f, 0.0f), D3DXVECTOR2(400.0f, 250.0f), CCharUI::UI_TUTORIAL1, CCharUI::STATE_SELECT);
	}

	if (m_nTime == 200)
	{
		m_pCharUI->SetCharState(CCharUI::STATE_INVISIBLE);
		m_pCharUI = m_pCharUI->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 180.0f, 0.0f), D3DXVECTOR2(400.0f, 250.0f), CCharUI::UI_TUTORIAL2, CCharUI::STATE_SELECT);
	}

	if (m_nTime == 600)
	{
		m_pCharUI->SetCharState(CCharUI::STATE_INVISIBLE);
		m_pCharUI = m_pCharUI->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 180.0f, 0.0f), D3DXVECTOR2(400.0f, 250.0f), CCharUI::UI_TUTORIAL3, CCharUI::STATE_SELECT);
	}

	if (m_nTime == 800)
	{
		m_pCharUI->SetCharState(CCharUI::STATE_INVISIBLE);
		m_pCharUI = m_pCharUI->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 180.0f, 0.0f), D3DXVECTOR2(400.0f, 250.0f), CCharUI::UI_TUTORIAL4, CCharUI::STATE_SELECT);
	}

	if (m_nTime == 1000)
	{
		m_pCharUI->SetCharState(CCharUI::STATE_INVISIBLE);
		m_pCharUI = m_pCharUI->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 180.0f, 0.0f), D3DXVECTOR2(400.0f, 250.0f), CCharUI::UI_TUTORIAL5, CCharUI::STATE_SELECT);
	}

	if (m_nTime == 1200)
	{
		m_pCharUI->SetCharState(CCharUI::STATE_INVISIBLE);
		m_pCharUI = m_pCharUI->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 180.0f, 0.0f), D3DXVECTOR2(400.0f, 250.0f), CCharUI::UI_TUTORIAL6, CCharUI::STATE_SELECT);
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		m_nCntSkip++;
	}

	if (m_nCntSkip >= 5 || m_nTime == 1400)
	{
		SetMode(MODE_TITLE);
	}
}