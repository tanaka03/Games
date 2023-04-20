//
//FrameEffect.h
//
#ifndef _FRAMEEFFECT_H_
#define _FRAMEEFFECT_H_

#include "object2d.h"

class CFrameEffect : public CObject2D
{
public:
	CFrameEffect();
	~CFrameEffect() override;

	static CFrameEffect *Create();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	void SetPos(D3DXVECTOR3 pos)  override { m_pos = pos; }

	D3DXVECTOR3 GetPos() override { return m_pos; }

private:
	void Draw();
	D3DXVECTOR3 m_pos;
	D3DXCOLOR m_col;
};

#endif