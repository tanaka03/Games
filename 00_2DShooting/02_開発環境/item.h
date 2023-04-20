//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Item.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _ITEM_H_
#define _ITEM_H_

#include "object2d.h"

class CItem : public CObject2D
{
public:
	enum EItem
	{
		ITEMTYPE_NONE = 0,
		ITEMTYPE_SCORE1,
		ITEMTYPE_SCORE2,
		ITEMTYPE_ORB,
		ITEMTYPE_RECOVERY,
		ITEMTYPE_MAGNET,
		ITEMTYPE_RANDOM,
		ITEMTYPE_MAX
	};

	CItem();
	virtual ~CItem();

	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, EItem type);
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, EColor col, EItem type);

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;

	//セッター
	void SetItemType(EItem type) { m_type = type; }
	void SetMagnetUse(bool state) { m_bMagnetUse = state; }

	//ゲッター
	EItem GetItemType() { return m_type; }
	bool GetMagnetUse() { return m_bMagnetUse; }

private:
	virtual void Draw() = 0;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	EItem m_type;
	int m_nLife;
	float m_fScale;
	static CItem *m_apItem;
	static bool m_bMagnetUse;
};

#endif