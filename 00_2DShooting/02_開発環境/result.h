#ifndef _RESULT_H_
#define _RESULT_H_

#include "mode.h"

class CScore;
class CCharUI;
class CBg;

class CResult : public CMode
{
public:
	CResult();
	~CResult();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	static CScore *GetScore() { return m_pScore[0]; }

private:
	CCharUI *m_pCharUI;
	CBg *m_pBg[3];
	int m_nNewScore;
	int m_nTime;

	static CScore *m_pScore[11];
};

#endif