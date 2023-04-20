//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Object.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
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
		OBJTYPE_PLAYER,			//プレイヤー
		OBJTYPE_ENEMY,			//敵
		OBJTYPE_BULLET,			//弾
		OBJTYPE_ENEMYBULLET,	//敵の弾
		OBJTYPE_ABILITY,		//アビリティ
		OBJTYPE_SKILL,
		OBJTYPE_ITEM,			//アイテム
		OBJTYPE_EFFECT,			//エフェクト
		OBJTYPE_FRAMEEFFECT,	//フレームエフェクト
		OBJTYPE_FRAMEABILITY,	//アビリティフレーム
		OBJTYPE_SCORE,			//スコア
		OBJTYPE_GAUGE,
		OBJTYPE_FRAGMENT,
		OBJTYPE_BG,				//背景
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
	int m_nID;			//格納先の番号
};

#endif