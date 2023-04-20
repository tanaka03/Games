#include "object2d.h"
#include "application.h"
#include "file.h"
#include "enemy.h"
#include "game.h"
#include "enemy_dog.h"
#include "enemy_bird.h"
#include "enemy_ghost.h"
#include "enemy_fairyfire.h"
#include "enemy_fairyaqua.h"
#include "enemy_girl.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//敵のコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemy::CEnemy()
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nBulletTime = 0;
	m_nDamageTime = 0;
	memset(&m_data, 0, sizeof(m_data));
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//敵のデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemy::~CEnemy()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//敵の生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	CEnemy *pEnemy = nullptr;

	switch (type)
	{
	case ENEMYTYPE_DOG:
		pEnemy = new CEnemyDog;
		break;

	case ENEMYTYPE_BIRD:
		pEnemy = new CEnemyBird;
		break;

	case ENEMYTYPE_GHOST:
		pEnemy = new CEnemyGhost;
		break;

	case ENEMYTYPE_FAIRYFIRE:
		pEnemy = new CEnemyFairyFire;
		break;

	case ENEMYTYPE_FAIRYAQUA:
		pEnemy = new CEnemyFairyAqua;
		break;

	case ENEMYTYPE_GIRL:
		pEnemy = new CEnemyGirl;
		break;

	default:
		break;
	}

	//ヌルチェック
	if (pEnemy != nullptr)
	{
		// ポリゴンの初期化処理
		pEnemy->SetPos(pos);
		pEnemy->SetType(CObject::OBJTYPE_ENEMY);
		pEnemy->SetEnemyType(type);
		pEnemy->Init();
	}

	return pEnemy;
}