#include "enemy_emitter.h"
#include "enemy_manager.h"
#include "enemy.h"
#include "application.h"
#include "player.h"
#include "game.h"
#include "utility.h"
#include "debugproc.h"
#include "number.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// エネミーエミッタのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemyEmitter::CEnemyEmitter() : m_time(0),
m_spawnTimer(30),
maxPopEnemy(50)
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// エネミーエミッタのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemyEmitter::~CEnemyEmitter()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// エネミーエミッタの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemyEmitter* CEnemyEmitter::Create()
{
	CEnemyEmitter *pEmitter = nullptr;
	pEmitter = new CEnemyEmitter;

	CEnemyManager *pManager = CApplication::GetInstance()->GetEnemyManager();

	if (pEmitter != nullptr)
	{
		for (auto &p : pManager->GetData())
		{
			pEmitter->m_enemyInfo.push_back(p.second[0]);
		}
		
		pEmitter->Init();
	}

	return pEmitter;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// エネミーエミッタの初期化
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CEnemyEmitter::Init()
{
	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// エネミーエミッタの終了
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemyEmitter::Uninit()
{
	if (!m_enemy.empty())
	{
		if (!m_afterRelease)
		{
			for (size_t i = 0; i < m_enemy.size(); i++)
			{
				m_enemy[i]->Uninit();
			}
		}
		m_enemy.clear();
	}

	if (!m_enemyInfo.empty())
	{
		m_enemyInfo.clear();
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// エネミーエミッタの更新
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemyEmitter::Update()
{
	if (m_enemy.size() >= maxPopEnemy)
	{
		return;
	}

	if (CApplication::GetInstance()->GetMode()->GetGame()->GetCombo()->GetValue() >= 1000)
	{
		maxPopEnemy = 75;
		m_spawnTimer = 25;
	}
	else
	{
		maxPopEnemy = 50;
		m_spawnTimer = 30;
	}

	int spawnRange = 1500;
	float limitPos = 600.0f;

	// プレイヤーが死亡した場合は新たに敵を生成しない
	if (CApplication::GetInstance()->GetMode()->GetGame()->GetDeath())
	{
		return;
	}

	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();
	D3DXVECTOR3 spawnPos = D3DXVECTOR3(pPlayer->GetPos().x + ((rand() % spawnRange) - (spawnRange / 2)), 0.0f, pPlayer->GetPos().z + ((rand() % spawnRange) - (spawnRange / 2)));

	m_time++;
	if ((m_time % m_spawnTimer) == 0)
	{
		// 一定の範囲外でない場合は生成しない
		if (spawnPos.x > limitPos || spawnPos.x < -limitPos &&
			spawnPos.z > limitPos || spawnPos.z < -limitPos)
		{
			if ((m_spawnCounter % 5) == 0)
			{
				m_enemy.push_back(CEnemy::Create(m_enemyInfo[1]));
				m_enemy[m_enemy.size() - 1]->SetPos(spawnPos);
				m_spawnCounter++;
			}
			else
			{
				m_enemy.push_back(CEnemy::Create(m_enemyInfo[0]));
				m_enemy[m_enemy.size() - 1]->SetPos(spawnPos);
				m_spawnCounter++;
			}
		}
	}

	// 特定の敵のライフが０になっていた場合に要素から消す処理
	for (size_t i = 0; i < m_enemy.size(); i++)
	{
		int life = m_enemy[i]->GetLife();
		if (life <= 0)
		{
			m_enemy.erase(m_enemy.begin() + i);
		}
	}
}