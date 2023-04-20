#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "mode.h"

class CBg;
class CCharUI;
class CPlayer;
class CFile;

class CTutorial : public CMode
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	CBg *m_pBg[3];
	CCharUI *m_pCharUI;
	CPlayer *m_pPlayer;
	CFile *m_pFile;
	int m_nTime;
	int m_nCntSkip;
	int m_nTutorialNum;
};

#endif