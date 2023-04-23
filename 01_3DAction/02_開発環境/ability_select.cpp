#include "ability_select.h"
#include "ability.h"
#include "object2d.h"
#include "application.h"
#include "keyboard.h"
#include "utility.h"
#include "sound.h"
#include "game.h"

//��������������������������������������������������������������
// �A�r���e�B�Z���N�g�̃R���X�g���N�^
//��������������������������������������������������������������
CAbilitySelect::CAbilitySelect() : 
	m_time(0),
	m_selectNum(0),
	m_slotStart(false),
	m_afterRelease(false)
{
}

//��������������������������������������������������������������
// �A�r���e�B�Z���N�g�̃f�X�g���N�^
//��������������������������������������������������������������
CAbilitySelect::~CAbilitySelect()
{
}

//��������������������������������������������������������������
// �A�r���e�B�Z���N�g�̐���
//��������������������������������������������������������������
CAbilitySelect * CAbilitySelect::Create()
{
	CAbilitySelect *pAbility = nullptr;
	pAbility = new CAbilitySelect;

	//�k���`�F�b�N
	if (pAbility != nullptr)
	{
		pAbility->Init();
	}

	return pAbility;
}

//��������������������������������������������������������������
// �A�r���e�B�Z���N�g�̏�����
//��������������������������������������������������������������
HRESULT CAbilitySelect::Init()
{
	m_divisionX = 1;
	m_divisionY = CAbility::ABILITY_MAX;

	return S_OK;
}

//��������������������������������������������������������������
// �A�r���e�B�Z���N�g�̏I��
//��������������������������������������������������������������
void CAbilitySelect::Uninit()
{
	if (!m_pAbility.empty())
	{
		if (m_afterRelease)
		{	// ReleaseAll�ŃI�u�W�F�N�g��������ꂽ��̏���
			for (size_t i = 0; i < m_pAbility.size(); i++)
			{
				m_pAbility[i]->AfterRelease();
				m_pAbility[i]->Uninit();
			}
			m_pAbility.clear();
		}
		else if (!m_afterRelease)
		{	// ReleaseAll�ŃI�u�W�F�N�g���������Ă��Ȃ����̏���
			for (size_t i = 0; i < m_pAbility.size(); i++)
			{
				if (!m_pAbility[i]->GetRelease())
				{
					continue;
				}

				m_pAbility[i]->Uninit();
				m_pAbility.erase(m_pAbility.begin() + i);
			}
		}
	}

	// �A�r���e�B�X���b�g�̉��
	if (!m_pAbilitySlot.empty())
	{
		if (!m_afterRelease)
		{
			for (size_t i = 0; i < m_pAbilitySlot.size(); i++)
			{
				m_pAbilitySlot[i]->Destroy();
			}
		}
		m_pAbilitySlot.clear();
	}

	// �I�����g�̉��
	if (!m_pSelectFrame.empty())
	{
		if (!m_afterRelease)
		{
			for (size_t i = 0; i < m_pSelectFrame.size(); i++)
			{
				m_pSelectFrame[i]->Destroy();
			}
		}
		m_pSelectFrame.clear();
	}
}

//��������������������������������������������������������������
// �A�r���e�B�Z���N�g�̍X�V
//��������������������������������������������������������������
void CAbilitySelect::Update()
{
	for (size_t i = 0; i < m_pAbility.size(); i++)
	{
		m_pAbility[i]->Update();
	}

	// �J�n���Ă��Ȃ��ꍇ�͒ʂ�Ȃ�
	if (!m_slotStart)
	{
		return;
	}

	//--------------------------------------------------------------

	m_time++;
	if (m_time >= 60)
	{
		m_pAbilitySlot[0]->SetUV(0.0f
			, 1.0f
			, (1.0f / m_divisionY) * m_selectAbility[0]
			, (1.0f / m_divisionY) + (1.0f / m_divisionY) * m_selectAbility[0]);
	}
	if (m_time >= 80)
	{
		m_pAbilitySlot[1]->SetUV(0.0f
			, 1.0f
			, (1.0f / m_divisionY) * m_selectAbility[1]
			, (1.0f / m_divisionY) + (1.0f / m_divisionY) * m_selectAbility[1]);
	}
	if (m_time >= 100)
	{
		CApplication::GetInstance()->GetSound()->Stop(CSound::LABEL_SE_ROULETTE);
		m_pAbilitySlot[2]->SetUV(0.0f
			, 1.0f
			, (1.0f / m_divisionY) * m_selectAbility[2]
			, (1.0f / m_divisionY) + (1.0f / m_divisionY) * m_selectAbility[2]);

		// ���ݑI�����Ă���ԍ��̈ʒu�Ƀt���[�����ړ�
		if (!m_pSelectFrame.empty())
		{
			m_pSelectFrame[0]->Visible();
			m_pSelectFrame[0]->SetPos(D3DXVECTOR3(250.0f + (400.0f * m_selectNum), 400.0f, 0.0f));

			D3DXVECTOR2 scale = m_pSelectFrame[0]->GetScale();

			static bool back = false;
			if (scale.x > 200.0f)		{ back = true; }
			else if (scale.x < 170.0f)	{ back = false; }

			if (back)		{ scale.x -= 0.5f, scale.y -= 0.5f; }
			else if (!back) { scale.x += 0.5f, scale.y += 0.5f; }

			m_pSelectFrame[0]->SetScale(scale);

			// �{�^�����͂ɂ��I��ԍ��̕ύX
			if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_A))
			{
				if (m_selectNum > 0) { m_selectNum--; }
			}
			if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_D))
			{
				if (m_selectNum < 2) { m_selectNum++; }
			}

			if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
			{
				CObject::ResumeAll();
				CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_STATUSUP);
				CApplication::GetInstance()->GetMode()->GetGame()->StartTimer();

				if (!m_pAbility.empty())
				{
					for (size_t i = 0; i < m_pAbility.size(); i++)
					{
						m_pAbility[i]->Resume();
					}
				}

				m_pAbility.push_back(CAbility::Create(m_selectAbility[m_selectNum]));
				m_time = 0;
				m_slotStart = false;
				Uninit();
				return;
			}
		}
	}
} 

//��������������������������������������������������������������
// �A�r���e�B�Z���N�g�̊J�n
//��������������������������������������������������������������
void CAbilitySelect::Start()
{
	// �X���b�g�J�n�ȑO�̑S�ẴI�u�W�F�N�g���~
	CObject::PauseAll();

	if (!m_pAbility.empty())
	{
		for (size_t i = 0; i < m_pAbility.size(); i++)
		{
			m_pAbility[i]->Pause();
		}
	}

	// �A�r���e�B�X���b�g�̐���
	m_pAbilitySlot.resize(3);
	for (size_t i = 0; i < m_pAbilitySlot.size(); i++)
	{
		m_pAbilitySlot[i] = CObject2D::Create(D3DXVECTOR3(250.0f + (400.0f * i), 400.0f, 0.0f), D3DXVECTOR2(150.0f, 150.0f), "TEST3", CObject::PRIORITY_FOURTH);
		m_pAbilitySlot[i]->Resume();
		m_pAbilitySlot[i]->SetAnimation(1, CAbility::ABILITY_MAX, 1, 1, true);
	}

	for (int i = 0; i < numAbility; i++)
	{
		m_selectAbility[i] = rand() % CAbility::ABILITY_MAX;
	}

	// �I�����̘g�̐���
	m_pSelectFrame.resize(1);
	m_pSelectFrame[0] = CObject2D::Create(D3DXVECTOR3(250.0f, 400.0f, 0.0f), D3DXVECTOR2(185.0f, 185.0f), "SELECTFRAME", CObject::PRIORITY_FOURTH);
	m_pSelectFrame[0]->Invisible();

	m_selectNum = 0;
	m_slotStart = true;
	CApplication::GetInstance()->GetSound()->Play(CSound::LABEL_SE_ROULETTE);
	CApplication::GetInstance()->GetMode()->GetGame()->StopTimer();
}