#include "lambert.h"
#include "application.h"
#include "renderer.h"

//��������������������������������������������������������������
// �����o�[�g�Ɩ��̃R���X�g���N�^
//��������������������������������������������������������������
CLambert::CLambert()
{
}

//��������������������������������������������������������������
// �����o�[�g�Ɩ��̃f�X�g���N�^
//��������������������������������������������������������������
CLambert::~CLambert()
{
}

//��������������������������������������������������������������
// �����o�[�g�Ɩ���fx�t�@�C���̓ǂݍ���
//��������������������������������������������������������������
HRESULT CLambert::Load()
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	if (SUCCEEDED(D3DXCreateEffectFromFile(pDevice, _T("Lambert.fx"), NULL, NULL, 0, NULL, &m_pEffect, NULL)))
	{
		m_pTechnique = m_pEffect->GetTechniqueByName("TShader");
		m_pWVP = m_pEffect->GetParameterByName(NULL, "m_WVP");

		m_pEffect->SetTechnique(m_pTechnique);
	}
	else
	{
		return E_FAIL;
	}

	return S_OK;
}

//��������������������������������������������������������������
// �����o�[�g�Ɩ��̊J�n
//��������������������������������������������������������������
void CLambert::Begin()
{
	if (m_pEffect == nullptr)
	{
		return;
	}

	m_pEffect->Begin(NULL, 0);
}

//��������������������������������������������������������������
// �����o�[�g�Ɩ��̃}�g���b�N�X�ݒ�
//��������������������������������������������������������������
void CLambert::SetMatrix(D3DXMATRIX* pMatWVP)
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	if (m_pEffect != nullptr)
	{
		m_pEffect->SetMatrix(m_pWVP, pMatWVP);
	}
}