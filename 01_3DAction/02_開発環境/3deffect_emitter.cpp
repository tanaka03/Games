#include "3deffect.h"
#include "3deffect_emitter.h"
#include "3deffect_manager.h"
#include "application.h"

//��������������������������������������������������������������
// 3D�G�t�F�N�g�G�~�b�^�̃R���X�g���N�^
//��������������������������������������������������������������
C3DEffectEmitter::C3DEffectEmitter()
{
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�G�~�b�^�̃f�X�g���N�^
//��������������������������������������������������������������
C3DEffectEmitter::~C3DEffectEmitter()
{
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�G�~�b�^�̐���
//��������������������������������������������������������������
C3DEffectEmitter* C3DEffectEmitter::Create(std::string tag)
{
	C3DEffectEmitter *pEmitter = nullptr;
	pEmitter = new C3DEffectEmitter;

	C3DEffectManager *pManager = CApplication::GetInstance()->GetEffectManager();

	if (pEmitter != nullptr)
	{
		pEmitter->m_effectInfo = pManager->GetEffectData(tag);
		pEmitter->Init();
	}

	return pEmitter;
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�G�~�b�^�̏�����
//��������������������������������������������������������������
HRESULT C3DEffectEmitter::Init()
{
	m_pEffect.resize(m_effectInfo.size());
	m_life.resize(m_effectInfo.size());
	for (size_t i = 0; i < m_effectInfo.size(); i++)
	{
		m_pEffect[i] = C3DEffect::Create(m_effectInfo[i], CObject::PRIORITY_THIRD);
		m_pEffect[i]->UseEmitter();
		m_life[i] = m_effectInfo[i].life;
	}

	return S_OK;
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�G�~�b�^�̏I��
//��������������������������������������������������������������
void C3DEffectEmitter::Uninit()
{
	// �G�t�F�N�g�C���t�H���[�V�����̗v�f���폜
	if (!m_effectInfo.empty())
	{
		m_effectInfo.clear();
	}

	// ���C�t�̗v�f���폜
	if (!m_life.empty())
	{
		m_life.clear();
	}

	// �G�t�F�N�g�̉��
	if (!m_pEffect.empty())
	{
		for (size_t i = 0; i < m_pEffect.size(); i++)
		{
			m_pEffect[i]->Uninit();
		}
		m_pEffect.clear();
	}
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�G�~�b�^�̍X�V
//��������������������������������������������������������������
void C3DEffectEmitter::Update()
{
	for (size_t i = 0; i < m_pEffect.size(); i++)
	{
		m_life[i]--;
		if (m_life[i] <= 0)
		{
			m_pEffect[i]->Uninit();
			m_pEffect.erase(m_pEffect.begin() + i);
			m_life.erase(m_life.begin() + i);
		}
	}
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�G�~�b�^�̈ʒu�ݒ�
//��������������������������������������������������������������
void C3DEffectEmitter::SetPos(D3DXVECTOR3 pos)
{
	for (auto &p : m_pEffect)
	{
		p->SetPos(pos);
	}
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�G�~�b�^�̌����ݒ�
//��������������������������������������������������������������
void C3DEffectEmitter::SetRot(D3DXVECTOR3 rot)
{
	for (auto &p : m_pEffect)
	{
		p->SetRot(rot);
	}
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�G�~�b�^�̊g�k�ݒ�
//��������������������������������������������������������������
void C3DEffectEmitter::SetScale(D3DXVECTOR3 scale)
{
	for (auto &p : m_pEffect)
	{
		p->SetScale(scale);
	}
}