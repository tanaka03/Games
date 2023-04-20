//
//LandMine.h
//
#ifndef _LANDMINE_H_
#define _LANDMINE_H_

#include "gimmick.h"

class CLandmine : public CGimmick
{
public:
	CLandmine();
	~CLandmine();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:

};

#endif