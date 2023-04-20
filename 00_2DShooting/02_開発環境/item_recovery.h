//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//RecoveryItem.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _RECOVERYITEM_H_
#define _RECOVERYITEM_H_

#include "item.h"

class CEffect;

class CRecoveryItem : public CItem
{
public:
	CRecoveryItem();
	~CRecoveryItem() override;

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
	CEffect *m_pEffect;
	int m_nLife;
	float m_fScale;
};

#endif