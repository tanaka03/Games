#include "result.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "score.h"
#include "file.h"
#include "char_ui.h"
#include "bg.h"
#include "sound.h"

CScore *CResult::m_pScore[11] = {};

CResult::CResult()
{
	m_nTime = 0;
	m_nNewScore = 0;
}

CResult::~CResult()
{
}

HRESULT CResult::Init()
{
	CFile *pFile = nullptr;
	pFile = new CFile;
	int nNum = 0;
	bool NewRank = false;
	m_nNewScore = GetNewScore();

	pFile->LoadRanking("ranking.json");

	//背景クラスの生成
	m_pBg[0] = m_pBg[0]->Create(CBg::BG_RESULT, false);

	//スコア表示の生成
	for (int i = 0; i < 10; i++)
	{
		m_pScore[i] = m_pScore[i]->Create(D3DXVECTOR3(300.0f, 35.0f + (70.0f * i), 0.0f), pFile->GetScore(i));
		
		if (pFile->GetScore(i) == GetNewScore())
		{
			NewRank = true;
			nNum = i;
		}
	}

	//順位の生成
	for (int i = 0; i < 10; i++)
	{
		m_pCharUI = m_pCharUI->Create(D3DXVECTOR3(200.0f, 35.0f + (70.0f * i), 0.0f), D3DXVECTOR2(30.0f, 30.0f), i, CCharUI::STATE_SELECT);

		if (NewRank)
		{
			m_pCharUI = m_pCharUI->Create(D3DXVECTOR3(100.0f, 35.0f + (70.0f * nNum), 0.0f), D3DXVECTOR2(30.0f, 30.0f), CCharUI::UI_RANK_NEW, CCharUI::STATE_SELECT);
			NewRank = false;
		}
	}

	CApplication::GetSound()->PlaySoundA(CSound::SOUND_LABEL_BGM_RESULT);

	return S_OK;
}

void CResult::Uninit()
{
}

void CResult::Update()
{
	m_nTime++;

	if (m_nTime >= 100)
	{
		if (CApplication::GetInputKeyboard()->GetTrigger(DIK_RETURN))
		{
			SetMode(MODE_TITLE);
			CApplication::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_RESULT);
		}
	}
}