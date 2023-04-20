//����������������������������������������
//Object.h
//����������������������������������������
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "renderer.h"

#define MAX_OBJECT	(512)

class CObject
{
public:
	enum EObjType
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,			//�v���C���[
		OBJTYPE_ENEMY,			//�G
		OBJTYPE_BULLET,			//�e
		OBJTYPE_ENEMYBULLET,	//�G�̒e
		OBJTYPE_ABILITY,		//�A�r���e�B
		OBJTYPE_SKILL,
		OBJTYPE_ITEM,			//�A�C�e��
		OBJTYPE_EFFECT,			//�G�t�F�N�g
		OBJTYPE_FRAMEEFFECT,	//�t���[���G�t�F�N�g
		OBJTYPE_FRAMEABILITY,	//�A�r���e�B�t���[��
		OBJTYPE_SCORE,			//�X�R�A
		OBJTYPE_GAUGE,
		OBJTYPE_FRAGMENT,
		OBJTYPE_BG,				//�w�i
		OBJTYPE_MAX,
	};

	CObject();
	virtual ~CObject();

	//explicit CObject(int nPriority = 3);
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void SetPos(D3DXVECTOR3 pos) = 0;
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();

	void SetType(EObjType obj) { m_objtype = obj; }

	CObject *GetMyObject(int nNum);
	EObjType GetObjType() { return m_objtype; }
	virtual D3DXVECTOR3 GetPos() = 0;
	int GetObjAll() { return m_nNumAll; }

protected:
	void Release();

private:
	static CObject *CObject::m_apObject[MAX_OBJECT];
	static int m_nNumAll;
	EObjType m_objtype;
	int m_nID;			//�i�[��̔ԍ�
};

#endif