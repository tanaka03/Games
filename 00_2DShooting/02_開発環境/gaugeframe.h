//
//GaugeFrame.h
//
#ifndef _GAUGEFRAME_H_
#define _GAUGEFRAME_H_

#include "object.h"

class CObject2D;

class CGaugeFrame : public CObject
{
public:
	CGaugeFrame();
	~CGaugeFrame() override;

	static CGaugeFrame *Create(D3DXVECTOR3 pos, D3DXVECTOR2 scale);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }
	void SetScale(D3DXVECTOR2 scale) { m_scale = scale; }

	D3DXVECTOR3 GetPos() override { return m_pos; }

private:
	void Draw() override;
	CObject2D *m_apObject2D;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_scale;
	D3DXCOLOR m_col;
};

#endif