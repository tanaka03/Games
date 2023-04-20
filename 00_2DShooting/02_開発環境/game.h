#ifndef _GAME_H_
#define _GAME_H_

#include "mode.h"

class CBg;
class CBullet;
class CFile;
class CPlayer;
class CScore;

class CGame : public CMode
{
public:
	CGame();
	~CGame();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	static CBullet *GetBullet() { return m_pBullet; }
	static CFile *GetFile() { return m_pFile; }
	static CPlayer *GetPlayer() { return m_pPlayer; }
	static CScore *GetScore() { return m_pScore; }

	static void SetClear(bool clear) { m_bClear = clear; }
	static void SetDeath(bool death) { m_bDeath = death; }

private:
	CBg *m_pBg[3];
	int m_nTime = 0;
	static bool m_bDeath;
	static bool m_bClear;
	static CBullet *m_pBullet;
	static CFile *m_pFile;
	static CPlayer *m_pPlayer;
	static CScore *m_pScore;
};

#endif