//
//Gauge.h
//
#ifndef _GAUGE_H_
#define _GAUGE_H_

class CGauge : public CObject2D
{
public:
	enum ETYPE
	{
		GAUGETYPE_NONE = 0,
		GAUGETYPE_HP,
		GAUGETYPE_MP,
		GAUGETYPE_MAX
	};

	CGauge();
	~CGauge();

	static CGauge *Create(D3DXVECTOR3 pos, ETYPE type);

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetType(ETYPE type) { m_type = type; }

	ETYPE GetType() { return m_type; }

private:
	static CGauge *m_apGauge;
	ETYPE m_type;
	int m_nValue;
};

#endif