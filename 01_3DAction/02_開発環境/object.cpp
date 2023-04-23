#include "object.h"

//===============================
//静的メンバ変数宣言
//===============================
CObject* CObject::m_Top[CObject::PRIORITY_MAX] = {};
CObject* CObject::m_Current[CObject::PRIORITY_MAX] = {};

//===============================
//オブジェクトのコンストラクタ
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
//オブジェクトのデストラクタ
//===============================
CObject::~CObject()
{
}

//===============================
//オブジェクトの全解放
//===============================
void CObject::ReleaseAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		// 全てのオブジェクトを更新
		CObject *pObj = m_Top[i];
		while (pObj)
		{
			CObject *pObjNext = pObj->m_Next;
			pObj->Uninit();
			pObj = pObjNext;
		}

		// 死亡フラグがtrueの場合オブジェクトを解放
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
//オブジェクトの更新
//===============================
void CObject::UpdateAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		// 全てのオブジェクトを更新
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

		// 死亡フラグがtrueの場合オブジェクトを解放
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
//オブジェクトの描画
//===============================
void CObject::DrawAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		// 全てのオブジェクトを描画
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
//オブジェクトの停止
//===============================
void CObject::PauseAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		// 全てのオブジェクトを描画
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
//オブジェクトの再開
//===============================
void CObject::ResumeAll()
{
	for (int i = 0; i < PRIORITY_MAX; i++)
	{
		// 全てのオブジェクトを描画
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
//オブジェクトの解放
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