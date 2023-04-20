//����������������������������������������
//ScoreItemB.h
//����������������������������������������
#ifndef _SCOREITEM_B_H_
#define _SCOREITEM_B_H_

#include "item.h"

class CScoreItemB : public CItem
{
public:
	CScoreItemB();
	~CScoreItemB() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	//�Z�b�^�[
	void SetObtainScale(float scale) { m_fScale = scale; }

	//�Q�b�^�[
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