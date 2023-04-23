#include "3dgauge.h"
#include "hp.h"

//��������������������������������������������������������������
// �r���{�[�h�̃Q�[�W�̃R���X�g���N�^
//��������������������������������������������������������������
C3DGauge::C3DGauge() : CBillboard(CObject::PRIORITY_FOURTH),
m_value(0),
m_maxValue(100)
{
}

//��������������������������������������������������������������
// �r���{�[�h�̃Q�[�W�̃f�X�g���N�^
//��������������������������������������������������������������
C3DGauge::~C3DGauge()
{
}

//��������������������������������������������������������������
// �r���{�[�h�̃Q�[�W�̐���
//��������������������������������������������������������������
C3DGauge * C3DGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXCOLOR col, ETYPE type, int priority)
{
	C3DGauge *pGauge = nullptr;

	switch (type)
	{
	case GAUGETYPE_HP:
		pGauge = new CHp(priority);
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
		pGauge->SetCol(col);
		pGauge->m_type = type;
		pGauge->Init();
	}

	return pGauge;
}

//��������������������������������������������������������������
// �r���{�[�h�̃Q�[�W�̐��l�ݒ�
//��������������������������������������������������������������
void C3DGauge::ValueSetting(int value)
{
	m_value = value;
	m_maxValue = value;
}