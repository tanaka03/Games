#include "item.h"
#include "item_score.h"
#include "item_score_B.h"
#include "item_magnet.h"
#include "item_recovery.h"
#include "item_orb.h"
#include "application.h"
#include "sound.h"

//����������������������������������������
//�ÓI�����o�ϐ��錾
//����������������������������������������
CItem *CItem::m_apItem;
bool CItem::m_bMagnetUse = false;

//����������������������������������������
//�A�C�e���̃R���X�g���N�^
//����������������������������������������
CItem::CItem()
{
	m_nLife = 250;
}

//����������������������������������������
//�A�C�e���̃f�X�g���N�^
//����������������������������������������
CItem::~CItem()
{
}

//����������������������������������������
//�A�C�e���̐���
//����������������������������������������
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, EItem type)
{
	switch (type)
	{
	case ITEMTYPE_SCORE1:		//�X�R�A�A�C�e���i���ʗ�100�j
		m_apItem = new CScoreItem;
		break;

	case ITEMTYPE_SCORE2:		//�X�R�A�A�C�e���i���ʗ�75�j
		m_apItem = new CScoreItemB;
		break;

	case ITEMTYPE_MAGNET:		//���苭���A�C�e��
		m_apItem = new CMagnetItem;
		break;

	case ITEMTYPE_RECOVERY:		//�񕜃A�C�e��
		m_apItem = new CRecoveryItem;
		break;

	case ITEMTYPE_ORB:		//���@�����A�C�e��
		m_apItem = new COrbItem;

	default:
		break;
	}

	//�k���`�F�b�N
	if (m_apItem != nullptr)
	{
		// �|���S���̏���������
		m_apItem->SetItemType(type);
		m_apItem->SetType(CObject::OBJTYPE_ITEM);
		m_apItem->Init();
		m_apItem->SetPos(pos);
		m_apItem->SetMove(move);
	}

	return m_apItem;
}

CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, EColor col, EItem type)
{
	switch (type)
	{
	case ITEMTYPE_SCORE1:		//�X�R�A�A�C�e���i���ʗ�100�j
		m_apItem = new CScoreItem;
		break;

	case ITEMTYPE_SCORE2:		//�X�R�A�A�C�e���i���ʗ�75�j
		m_apItem = new CScoreItemB;
		break;

	case ITEMTYPE_ORB:			//���@�����A�C�e��
		m_apItem = new COrbItem;

	default:
		break;
	}

	//�k���`�F�b�N
	if (m_apItem != nullptr)
	{
		// �|���S���̏���������
		m_apItem->SetItemType(type);
		m_apItem->SetType(CObject::OBJTYPE_ITEM);
		m_apItem->Init();
		m_apItem->SetPos(pos);
		m_apItem->SetMove(move);
		m_apItem->SetMyCol(col);
	}

	return m_apItem;
}