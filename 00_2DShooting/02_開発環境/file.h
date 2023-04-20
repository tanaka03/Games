//
//File.h
//
#ifndef _FILE_H_
#define _FILE_H_

#include "enemy.h"
#include "nlohmann/json.hpp"

class CEnemy;
class CObject2D;

class CFile
{
public:
	struct EnemyData
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 move;
		D3DXVECTOR3 keyPos[16];
		D3DXVECTOR2 scale;
		D3DXCOLOR col;
		CEnemy::ENEMYTYPE type;
		int bullet_interval;
		int specified_frame[16];
		int numKeyframe;
		int score;
		int damage;
		int life;
		int Bulletlife;
		int frame;
	};

	CFile();
	~CFile();

	void Update();

	void Input(const char* FileName);
	void Output(const char* FileName);
	void LoadRanking(const char* FileName);
	void SaveRanking(const char* FileName);
	/*void LoadJson(const char* cUrl);*/

	int GetScore(int idx) { return m_nScore[idx]; }

private:
	static const int Max_EnemyData = 128;

	//“GŠÖŒW
	EnemyData m_enemy[Max_EnemyData];
	CEnemy *m_pEnemy[Max_EnemyData];
	CObject2D *m_pObject;
	int m_nNum = 0;
	int m_nCntAll = 0;

	//ƒ‰ƒ“ƒLƒ“ƒOŠÖŒW
	int m_nScore[11] = {};

	static int m_nTime;
};

#endif