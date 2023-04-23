#ifndef _CONTINUE_H_
#define _CONTINUE_H_

#include "mode.h"

class CObject2D;

class CContinue : public CMode
{
public:
	CContinue();
	~CContinue();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	CObject2D* m_pObj;
	int m_nTime;
};

#endif