#include "object.h"
#include <assert.h>

//===============================
//�ÓI�����o�ϐ��錾
//===============================
CObject *CObject::m_apObject[MAX_OBJECT];
int CObject::m_nNumAll = 0;

//===============================
//�I�u�W�F�N�g�̃R���X�g���N�^
//===============================
CObject::CObject()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] == nullptr)
		{
			m_apObject[i] = this;
			m_nID = i;
			m_nNumAll++;
			break;
		}
	}
}

//===============================
//�I�u�W�F�N�g�̃f�X�g���N�^
//===============================
CObject::~CObject()
{
}

//===============================
//�I�u�W�F�N�g�̑S���
//===============================
void CObject::ReleaseAll()
{
	//���������
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		//NULL�`�F�b�N
		if (m_apObject[i] != nullptr)
		{
			m_apObject[i]->Release();
		}
	}
}

//===============================
//�I�u�W�F�N�g�̍X�V
//===============================
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] != nullptr)
		{
			// �|���S���̍X�V����
			m_apObject[i]->Update();
		}
	}
}

//===============================
//�I�u�W�F�N�g�̕`��
//===============================
void CObject::DrawAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		// �|���S���̕`�揈��
		if (m_apObject[i] != nullptr)
		{
			// �|���S���̍X�V����
			m_apObject[i]->Draw();
		}
	}
}

//===============================
//�I�u�W�F�N�g�̉��
//===============================
void CObject::Release()
{
	if (m_apObject[m_nID] != nullptr)
	{
		int nID = m_nID;

		delete m_apObject[nID];
		m_apObject[nID] = nullptr;
		m_nNumAll--;
	}
}

CObject *CObject::GetMyObject(int nNum)
{
	return m_apObject[nNum];
}