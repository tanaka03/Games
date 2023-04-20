#include "application.h"
#include "object2d.h"
#include "ability.h"
#include "enemy.h"
#include "score.h"
#include "item.h"

#include "magnet.h"

//����������������������������������������
//�ÓI�����o�ϐ��錾
//����������������������������������������
CAbility *CAbility::m_apAbility;
int CAbility::m_nNumAll = 0;

CAbility::CAbility()
{
	m_nNumAll++;
	m_Radius = 15.0f;
}

CAbility::~CAbility()
{
}

//�A�r���e�B�̐���
CAbility * CAbility::Create(D3DXVECTOR3 pos, EAbilityType type)
{
	switch (type)
	{
	case ABILITYTYPE_MAGNET:
		m_apAbility = new CMagnet;
		break;

	default:
		break;
	}

	//�k���`�F�b�N
	if (m_apAbility != nullptr)
	{
		m_apAbility->Init();
		m_apAbility->SetEnableTime(10);
		m_apAbility->SetABType(type);
		m_apAbility->SetPos(pos);
	}

	return m_apAbility;
}

//�A�r���e�B�̐���
CAbility * CAbility::Create(D3DXVECTOR3 pos, int EnableTime, EAbilityType type)
{
	switch (type)
	{
	case ABILITYTYPE_MAGNET:
		m_apAbility = new CMagnet;
		break;

	default:
		break;
	}

	//�k���`�F�b�N
	if (m_apAbility != nullptr)
	{
		m_apAbility->Init();
		m_apAbility->SetABType(type);
		m_apAbility->SetEnableTime(EnableTime);
		m_apAbility->SetPos(pos);
	}

	return m_apAbility;
}