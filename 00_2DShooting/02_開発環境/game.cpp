#include "game.h"
#include "bg.h"
#include "file.h"
#include "player.h"
#include "score.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "sound.h"
#include "particle_manager.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//����������������������������������������
//�ÓI�����o�ϐ��錾
//����������������������������������������
CBullet *CGame::m_pBullet = nullptr;
CFile *CGame::m_pFile = nullptr;
CPlayer *CGame::m_pPlayer = nullptr;
CScore *CGame::m_pScore = nullptr;
bool CGame::m_bClear = false;
bool CGame::m_bDeath = false;

//����������������������������������������
//�Q�[���̃R���X�g���N�^
//����������������������������������������
CGame::CGame()
{
	m_bClear = false;
	m_bDeath = false;
	m_nTime = 0;
}

//����������������������������������������
//�Q�[���̃f�X�g���N�^
//����������������������������������������
CGame::~CGame()
{
}

//����������������������������������������
//�Q�[���̏���������
//����������������������������������������
HRESULT CGame::Init()
{
	srand(time(0));

	//�t�@�C���N���X�̐���
	m_pFile = new CFile;
	m_pFile->Input("file.json");

	//�w�i�N���X�̐���
	m_pBg[0] = m_pBg[0]->Create(CBg::BG_GAME1, true);	
	m_pBg[0]->SetScroll(true);
	m_pBg[0]->SetRange(D3DXVECTOR2(2.0f, 1.0f));

	//�w�i�N���X�̐���
	m_pBg[1] = m_pBg[1]->Create(CBg::BG_GAMECLOUD, false);
	m_pBg[1]->SetScroll(true, 0.009f);
	m_pBg[1]->SetAlpha(0.4f);

	//�v���C���[�N���X�̐���
	m_pPlayer->Create();

	//�X�R�A�N���X�̐���
	m_pScore = m_pScore->Create(D3DXVECTOR3(30.0f, 35.0f, 0.0f));

	CApplication::GetSound()->PlaySoundA(CSound::SOUND_LABEL_BGM_GAME);

	return S_OK;
}

//����������������������������������������
//�Q�[���̏I������
//����������������������������������������
void CGame::Uninit()
{
	CObject::ReleaseAll();
}

//����������������������������������������
//�Q�[���̍X�V����
//����������������������������������������
void CGame::Update()
{
	//m_pFile->Update();

	if (m_bClear || m_bDeath)
	{
		m_nTime++;

		if (m_nTime >= 150)
		{
			m_pFile->SaveRanking("ranking.json");
			SetNewScore(m_pScore->Get());
			CApplication::GetSound()->StopSound(CSound::SOUND_LABEL_BGM_GAME);
			SetMode(MODE_RESULT);
		}
	}
}