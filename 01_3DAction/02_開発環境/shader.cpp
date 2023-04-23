#include "shader.h"
#include "application.h"
#include "renderer.h"

//��������������������������������������������������������������
// �V�F�[�_�[�̃R���X�g���N�^
//��������������������������������������������������������������
CShader::CShader() : m_pEffect(nullptr)
{
}

//��������������������������������������������������������������
// �V�F�[�_�[�̃f�X�g���N�^
//��������������������������������������������������������������
CShader::~CShader()
{
}

//��������������������������������������������������������������
// �V�F�[�_�[�̏I��
//��������������������������������������������������������������
void CShader::End()
{ 
	if (m_pEffect == nullptr)
	{
		return;
	}

	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	m_pEffect->End(); 

	// �Œ�@�\�p�C�v���C���ɖ߂�
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
}