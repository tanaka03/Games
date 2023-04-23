//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Gauge.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "object2d.h"

class CGauge : public CObject2D
{
public:
	enum ETYPE
	{
		GAUGETYPE_NONE = 0,
		GAUGETYPE_EXP,
		GAUGETYPE_SP,
		GAUGETYPE_MAX
	};

	CGauge();
	~CGauge();

	static CGauge *Create(D3DXVECTOR3 pos, float rot, D3DXVECTOR2 scale, D3DXCOLOR col, ETYPE type, int priority);

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void AddValue(int value) { m_value += value; }

	//セッター
	void SetValue(int value) { m_value = value; }
	void SetMaxValue(int max) { m_maxValue = max; }
	void SetRot(float rot) { m_rot = rot; }

	int GetValue() { return m_value; }
	int GetMaxValue() { return m_maxValue; }
	float GetRot() { return m_rot; }

private:
	ETYPE m_type;
	int m_value;
	int m_maxValue;
	float m_rot;
};

#endif