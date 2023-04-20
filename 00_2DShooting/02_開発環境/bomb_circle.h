//
//BombCircle.h
//
#ifndef _BOMBCIRCLE_H_
#define _BOMBCIRCLE_H_

#include "gimmick.h"

class CBombCircle : public CGimmick
{
public:
	CBombCircle();
	~CBombCircle();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:

};

#endif