#ifndef _TITLE_H_
#define _TITLE_H_

#include "mode.h"

class CCharUI;
class CBg;

class CTitle : public CMode
{
public:
	enum ESelect
	{
		SELECT_NONE,
		SELECT_START,
		SELECT_TUTORIAL,
		SELECT_QUIT,
		SELECT_MAX,
	};

	CTitle();
	~CTitle();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	CCharUI *m_pCharUI[4];
	CBg *m_pBg[2];
	int m_nSelect = 1;
};

#endif