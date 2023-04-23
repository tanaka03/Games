//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//3DGauge.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _3DGAUGE_H_
#define _3DGAUGE_H_

#include "billboard.h"

class C3DGauge : public CBillboard
{
public:
	//--------------------------------------
	// ゲージタイプの列挙
	//--------------------------------------
	enum ETYPE
	{
		GAUGETYPE_NONE = 0,
		GAUGETYPE_HP,
		GAUGETYPE_MAX
	};

	C3DGauge();
	~C3DGauge();

	static C3DGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR col, ETYPE type, int priority);

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void AddValue(int value) { m_value += value; }
	void ValueSetting(int value);

	//セッター
	void SetValue(int value) { m_value = value; }
	void SetMaxValue(int max) { m_maxValue = max; }

	int GetValue() { return m_value; }
	int GetMaxValue() { return m_maxValue; }

private:
	ETYPE m_type;
	int m_value;
	int m_maxValue;
};

#endif