//
//Gimmick.h
//
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

#include "object2d.h"

class CGimmick : public CObject2D
{
public:
	enum EType
	{
		GIMMICKTYPE_NONE = 0,
		GIMMICKTYPE_LANDMINE,
		GIMMICKTYPE_MAX
	};

	CGimmick();
	~CGimmick();

	static CGimmick *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, EType type);
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;

	void SetGimmickType(EType type) { m_type = type; }

	EType GetGimmickType() { return m_type; }

private:
	virtual void Draw() = 0;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	EType m_type;
	int m_nLife;
};

#endif