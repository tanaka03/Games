//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ScoreItem.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _SCOREITEM_H_
#define _SCOREITEM_H_

#include "item.h"

class CScoreItem : public CItem
{
public:
	CScoreItem();
	~CScoreItem() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	//セッター
	void SetObtainScale(float scale) { m_fScale = scale; }

	//ゲッター
	float GetObtainScale() { return m_fScale; }

private:
	void Draw() override;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	EItem m_type;
	int m_nLife;
	float m_fScale;
};

#endif