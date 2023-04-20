#ifndef _FADE_H_
#define _FADE_H_

#include "object2d.h"

class CFade : public CObject2D
{
public:
	enum EFadeType
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	};

	CFade();
	~CFade();

	static CFade *Create(int fadetime, EFadeType type);
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void SetFadeType(EFadeType type) { m_fade = type; }
	void SetFadeSecond(int time) { m_fadeSecond = time; }

	EFadeType GetFadeType() { return m_fade; }
	int GetFadeSecond() { return m_fadeSecond; }

private:
	D3DXCOLOR m_col;
	EFadeType m_fade;
	int m_fadeSecond;
};

#endif