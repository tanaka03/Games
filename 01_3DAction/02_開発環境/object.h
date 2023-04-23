//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Object.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "renderer.h"

class CObject
{
public:
	//--------------------------------------
	// プライオリティの列挙
	//--------------------------------------
	enum EPriority
	{
		PRIORITY_FIRST = 0,
		PRIORITY_SECOND,
		PRIORITY_THIRD,
		PRIORITY_FOURTH,
		PRIOTITY_IMPORTANT,
		PRIORITY_MAX
	};

	//--------------------------------------
	// オブジェクトタイプの列挙
	//--------------------------------------
	enum EObjType
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_BULLET,
		OBJTYPE_ENEMY,
		OBJTYPE_GIMMICK,
		OBJTYPE_STAGE,
		OBJTYPE_MAX
	};

	enum EObjState
	{
		OBJSTATE_2D = 0,
		OBJSTATE_3D,
		OBJSTATE_MAX
	};

	explicit CObject(int nPriority = PRIORITY_THIRD);
	virtual ~CObject();

	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();
	static void PauseAll();
	static void ResumeAll();
	virtual void Destroy() { m_bDestroy = true; }
	virtual void Invisible() { m_bInvisible = true; }
	virtual void Visible() { m_bInvisible = false; }
	virtual void Pause() { m_bPause = true; }
	virtual void Resume() { m_bPause = false; }

	void SetObjType(EObjType obj) { m_objtype = obj; }
	void SetObjState(EObjState state) { m_objState = state; }
	virtual void SetPos(D3DXVECTOR3 pos) = 0;

	EObjType GetObjType() { return m_objtype; }
	EObjState GetObjState() {return m_objState;}
	virtual D3DXVECTOR3 GetPos() = 0;
	virtual bool GetDestroy() = 0;
	virtual bool GetPause() { return m_bPause; }
	virtual bool GetInvisible() { return m_bInvisible; }

	static CObject* GetTop(int nPriority) { return m_Top[nPriority]; }
	static CObject* GetCurrent(int nPriority) { return m_Current[nPriority]; }
	CObject *GetPrev() { return m_Prev; }
	CObject *GetNext() { return m_Next; }

protected:
	void Release();

private:
	static CObject *m_Top[PRIORITY_MAX];
	static CObject *m_Current[PRIORITY_MAX];

	CObject *m_Prev;
	CObject *m_Next;
	EObjType m_objtype;
	EObjState m_objState;
	int m_nID;			//格納先の番号
	int m_nPriority;
	bool m_bPause;
	bool m_bInvisible;
	bool m_bDestroy;
};

#endif