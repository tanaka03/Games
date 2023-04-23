#ifndef _RESULT_H_
#define _RESULT_H_

#include "mode.h"

class CObject2D;
class CScore;
class CBg;

class CResult : public CMode
{
public:
	CResult();
	~CResult();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	CObject2D* m_pObj;
	int m_nNewScore;
	int m_nTime;
};

#endif