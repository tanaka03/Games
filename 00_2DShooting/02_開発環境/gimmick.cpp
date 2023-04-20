#include "gimmick.h"
#include "landmine.h"

CGimmick::CGimmick()
{
}

CGimmick::~CGimmick()
{
}

//����������������������������������������
//�M�~�b�N�̐���
//����������������������������������������
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

	//�k���`�F�b�N
	if (pGimmick != nullptr)
	{
		pGimmick->Init();
		pGimmick->SetGimmickType(type);
		pGimmick->SetPos(pos);
		pGimmick->SetMove(move);
	}

	return pGimmick;
}