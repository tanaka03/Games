#include "object.h"

//===============================
//�ÓI�����o�ϐ��錾
//===============================
CObject* CObject::m_Top[CObject::PRIORITY_MAX] = {};
CObject* CObject::m_Current[CObject::PRIORITY_MAX] = {};

//===============================
//�I�u�W�F�N�g�̃R���X�g���N�^
//===============================
CObject::CObject(int nPriority) :
	m_bPause(false),
	m_bInvisible(false),
	m_bDestroy(false)
{
	m_nPriority = nPriority;

	if (m_Top[nPriority] == nullptr)
	{
		this->m_Prev = nullptr;
		this->m_Next = nullptr;
		m_Top[nPriority] = this;
		m_Current[nPriority] = this;
	}
	else
	{
		this->m_Next = nullptr;
		this->m_Prev = m_Current[nPriority];
		this->m_Prev->m_Next = this;
		m_Current[nPriority] = this;
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
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		// �S�ẴI�u�W�F�N�g���X�V
		CObject *pObj = m_Top[i];
		while (pObj)
		{
			CObject *pObjNext = pObj->m_Next;
			pObj->Uninit();
			pObj = pObjNext;
		}

		// ���S�t���O��true�̏ꍇ�I�u�W�F�N�g�����
		pObj = m_Top[i];
		while (pObj)
		{
			CObject *pObjNext = pObj->m_Next;
			pObj->Release();
			pObj = pObjNext;
		}
	}
}

//===============================
//�I�u�W�F�N�g�̍X�V
//===============================
void CObject::UpdateAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		// �S�ẴI�u�W�F�N�g���X�V
		CObject *pObj = m_Top[i];
		while (pObj)
		{
			CObject *pObjNext = pObj->m_Next;

			if (!pObj->GetPause())
			{
				pObj->Update();
			}
			pObj = pObjNext;
		}

		// ���S�t���O��true�̏ꍇ�I�u�W�F�N�g�����
		pObj = m_Top[i];
		while (pObj)
		{
			CObject *pObjNext = pObj->m_Next;
			pObj->Release();
			pObj = pObjNext;
		}
	}
}

//===============================
//�I�u�W�F�N�g�̕`��
//===============================
void CObject::DrawAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		// �S�ẴI�u�W�F�N�g��`��
		CObject *pObj = m_Top[i];
		while (pObj)
		{
			CObject *pObjNext = pObj->m_Next;

			if (!pObj->GetInvisible())
			{
				pObj->Draw();
			}
			pObj = pObj->m_Next;
		}
	}
}

//===============================
//�I�u�W�F�N�g�̒�~
//===============================
void CObject::PauseAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		// �S�ẴI�u�W�F�N�g��`��
		CObject *pObj = m_Top[i];
		while (pObj)
		{
			CObject *pObjNext = pObj->m_Next;
			pObj->Pause();
			pObj = pObj->m_Next;
		}
	}
}

//===============================
//�I�u�W�F�N�g�̍ĊJ
//===============================
void CObject::ResumeAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		// �S�ẴI�u�W�F�N�g��`��
		CObject *pObj = m_Top[i];
		while (pObj)
		{
			CObject *pObjNext = pObj->m_Next;
			pObj->Resume();
			pObj = pObj->m_Next;
		}
	}
}

//===============================
//�I�u�W�F�N�g�̉��
//===============================
void CObject::Release()
{
	if (this->GetDestroy())
	{
		if (this->m_Next != nullptr && this->m_Prev != nullptr)
		{
			this->m_Next->m_Prev = this->m_Prev;
			this->m_Prev->m_Next = this->m_Next;
		}
		else if (this->m_Prev == nullptr && this->m_Next != nullptr)
		{
			this->m_Next->m_Prev = nullptr;
			m_Top[m_nPriority] = this->m_Next;
		}
		else if (this->m_Next == nullptr && this->m_Prev != nullptr)
		{
			this->m_Prev->m_Next = nullptr;
			m_Current[m_nPriority] = this->m_Prev;
		}
		else if (this->m_Next == nullptr && this->m_Prev == nullptr)
		{
			m_Top[m_nPriority] = nullptr;
			m_Current[m_nPriority] = nullptr;
		}

		this->Uninit();
		delete this;
	}
}