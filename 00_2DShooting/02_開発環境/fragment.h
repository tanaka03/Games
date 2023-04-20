//
//Fragment.h
//
#ifndef _FRAGMENT_H_
#define _FRAGMENT_H_

#define MAX_FRAGMENT	(10)

#include "object2d.h"

class CFragment : public CObject2D
{
public:
	CFragment();
	~CFragment() override;

	static CFragment *Create(D3DXVECTOR3 pos);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	void Draw() override;
	D3DXVECTOR3 m_pos;
	static CFragment *m_pFragment[MAX_FRAGMENT];
	static int m_nCntAll;
};

#endif