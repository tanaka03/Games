#include "gauge.h"
#include "exp.h"
#include "sp.h"

//��������������������������������������������������������������
// �Q�[�W�̃R���X�g���N�^
//��������������������������������������������������������������
CGauge::CGauge() : CObject2D(CObject::PRIORITY_FOURTH),
m_value(0),
m_maxValue(100)
{
}

//��������������������������������������������������������������
// �Q�[�W�̃f�X�g���N�^
//��������������������������������������������������������������
CGauge::~CGauge()
{
}

//��������������������������������������������������������������
// �Q�[�W�̐���
//��������������������������������������������������������������
CGauge * CGauge::Create(D3DXVECTOR3 pos, float rot, D3DXVECTOR2 scale, D3DXCOLOR col, ETYPE type, int priority)
{
	CGauge *pGauge = nullptr;

	switch (type)
	{
	case GAUGETYPE_EXP:
		pGauge = new CExp(priority);
		break;

	case GAUGETYPE_SP:
		pGauge = new CSp(priority);
		break;

	default:
		assert(false);
		break;
	}

	//�k���`�F�b�N
	if (pGauge != nullptr)
	{
		pGauge->SetPos(pos);
		pGauge->SetScale(scale);
		pGauge->m_rot = rot;
		pGauge->SetCol(col);
		pGauge->m_type = type;
		pGauge->Init();
	}

	return pGauge;
}