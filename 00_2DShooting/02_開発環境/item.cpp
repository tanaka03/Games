#include "item.h"
#include "item_score.h"
#include "item_score_B.h"
#include "item_magnet.h"
#include "item_recovery.h"
#include "item_orb.h"
#include "application.h"
#include "sound.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//静的メンバ変数宣言
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CItem *CItem::m_apItem;
bool CItem::m_bMagnetUse = false;

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CItem::CItem()
{
	m_nLife = 250;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CItem::~CItem()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, EItem type)
{
	switch (type)
	{
	case ITEMTYPE_SCORE1:		//スコアアイテム（効果量100）
		m_apItem = new CScoreItem;
		break;

	case ITEMTYPE_SCORE2:		//スコアアイテム（効果量75）
		m_apItem = new CScoreItemB;
		break;

	case ITEMTYPE_MAGNET:		//判定強化アイテム
		m_apItem = new CMagnetItem;
		break;

	case ITEMTYPE_RECOVERY:		//回復アイテム
		m_apItem = new CRecoveryItem;
		break;

	case ITEMTYPE_ORB:		//自機強化アイテム
		m_apItem = new COrbItem;

	default:
		break;
	}

	//ヌルチェック
	if (m_apItem != nullptr)
	{
		// ポリゴンの初期化処理
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
	case ITEMTYPE_SCORE1:		//スコアアイテム（効果量100）
		m_apItem = new CScoreItem;
		break;

	case ITEMTYPE_SCORE2:		//スコアアイテム（効果量75）
		m_apItem = new CScoreItemB;
		break;

	case ITEMTYPE_ORB:			//自機強化アイテム
		m_apItem = new COrbItem;

	default:
		break;
	}

	//ヌルチェック
	if (m_apItem != nullptr)
	{
		// ポリゴンの初期化処理
		m_apItem->SetItemType(type);
		m_apItem->SetType(CObject::OBJTYPE_ITEM);
		m_apItem->Init();
		m_apItem->SetPos(pos);
		m_apItem->SetMove(move);
		m_apItem->SetMyCol(col);
	}

	return m_apItem;
}