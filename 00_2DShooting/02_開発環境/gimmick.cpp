#include "gimmick.h"
#include "landmine.h"

CGimmick::CGimmick()
{
}

CGimmick::~CGimmick()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//ギミックの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CGimmick * CGimmick::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, EType type)
{
	CGimmick *pGimmick = nullptr;

	switch (type)
	{
	case GIMMICKTYPE_LANDMINE:
		pGimmick = new CLandmine;
		break;

	default:
		break;
	}

	//ヌルチェック
	if (pGimmick != nullptr)
	{
		pGimmick->Init();
		pGimmick->SetGimmickType(type);
		pGimmick->SetPos(pos);
		pGimmick->SetMove(move);
	}

	return pGimmick;
}