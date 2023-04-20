#include <stdlib.h>
#include "object2d.h"
#include "application.h"
#include "ability.h"
#include "bullet.h"
#include "effect.h"
#include "enemy.h"
#include "enemybullet.h"
#include "frameeffect.h"
#include "game.h"
#include "gauge.h"
#include "input.h"
#include "keyboard.h"
#include "player.h"
#include "score.h"
#include "skill.h"
#include "sound.h"
#include "fragment.h"
#include "funnel.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayer::CPlayer()
{
	m_nMp = 0;
	m_nInvincibleTime = 100;
	m_fTimer = 0.0f;
	m_bOnce = true;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayer::~CPlayer()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayer * CPlayer::Create()
{
	CPlayer *pPlayer = nullptr;
	pPlayer = new CPlayer;

	//ヌルチェック
	if (pPlayer != nullptr)
	{
		// ポリゴンの初期化処理
		pPlayer->Init();
		pPlayer->SetType(CObject::OBJTYPE_PLAYER);
	}

	return pPlayer;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの初期化処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CPlayer::Init()
{
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject2D::SetScale(25.0f,40.0f);
	CObject2D::Init();
	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);
	m_pGauge = m_pGauge->Create(D3DXVECTOR3(950.0f,20.0f,0.0f), CGauge::GAUGETYPE_HP);
	m_pGauge = m_pGauge->Create(D3DXVECTOR3(950.0f, 40.0f, 0.0f), CGauge::GAUGETYPE_MP);
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2,700.0f,0.0f);
	SetLife(100);
	SetInvincible(m_nInvincibleTime);

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Update()
{
	CEffect *pEffect = nullptr;
	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;    // 計算用マトリックス
	int nRand = rand() % 6;
	m_pos += GetMove();
	m_col = GetCol();
	m_nMp = GetMP();
	m_nTime++;

	CObject2D::Update();

	if (GetMoving())
	{
		m_InitCounter++;

		if ((m_InitCounter % 15) == 0)
		{
			SetMove(D3DXVECTOR3(0.0f,0.0f,0.0f));
			m_InitCounter = 0;
			SetMoving(false);
		}
	}

	//キー入力
	if (CApplication::GetInputKeyboard()->GetPress(DIK_LSHIFT))
	{
		m_fSpeed = 5.0f;
	}

	else
	{
		m_fSpeed = 10.0f;
	}

	if (CApplication::GetInputKeyboard()->GetPress(DIK_D))
	{
		m_pos.x += m_fSpeed;
	}

	if (CApplication::GetInputKeyboard()->GetPress(DIK_A))
	{
		m_pos.x -= m_fSpeed;
	}

	if (CApplication::GetInputKeyboard()->GetPress(DIK_S))
	{
		m_pos.y += m_fSpeed;
	}

	if (CApplication::GetInputKeyboard()->GetPress(DIK_W))
	{
		m_pos.y -= m_fSpeed;
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_SPACE))
	{
		m_nPressTime = 0;
		m_pBullet = m_pBullet->Create(m_pos, D3DXVECTOR3(0.0f, -15.0f, 0.0f),D3DXCOLOR(1.0f,1.0f,0.0f,1.0f), 25, CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_PLAYER);
	}

	if (CApplication::GetInputKeyboard()->GetPress(DIK_SPACE))
	{
		m_nPressTime++;

		//バレットクラスの生成
		if ((m_nPressTime % 10) == 0 )
		{
			m_pBullet = m_pBullet->Create(m_pos, D3DXVECTOR3(0.0f, -15.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 25, CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_PLAYER);
			m_nPressTime = 0;
		}
	}

	if (CApplication::GetInputKeyboard()->GetTrigger(DIK_P))
	{
		if (m_nMp >= 50)
		{
			for (int i = 0; i < 5; i++)
			{
				m_pSkill = m_pSkill->Create(m_pos, D3DXVECTOR3(sinf((i * ((180 / 5) * (D3DX_PI / 180)))), -cosf((i * ((180 / 5) * (D3DX_PI / 180)))), 0.0f) * 5.0f, 200, CSkill::SKILLTYPE_REFLECTSPHERE);
				m_pSkill = m_pSkill->Create(m_pos, D3DXVECTOR3(-sinf((i * ((180 / 5) * (D3DX_PI / 180)))), -cosf((i * ((180 / 5) * (D3DX_PI / 180)))), 0.0f) * 5.0f, 200, CSkill::SKILLTYPE_REFLECTSPHERE);
			}

			m_pAbility = m_pAbility->Create(m_pos, 50, CAbility::ABILITYTYPE_MAGNET);
			m_pEffect = m_pEffect->Create(m_pos, D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXCOLOR(0.0f,0.7f,0.7f,1.0f), 70, CEffect::EFFECTTYPE_MAGIC);
			m_pEffect->SetBehavior(CEffect::BEHAVIOR_PLAYER, CEffect::BEHAVIOR_ROTATION, CEffect::BEHAVIOR_SCALEDOWN);
			m_pEffect->SetScale(75.0f, 75.0f);
			m_nMp -= 50;
			SetState(STATE_INVINCIBLE);
		}
	}

	//画面端判定
	if (m_pos.x <= 0.0f)
	{
		m_pos.x += 10.0f;
	}

	if (m_pos.x >= SCREEN_WIDTH)
	{
		m_pos.x -= 10.0f;
	}

	if (m_pos.y <= 0.0f)
	{
		m_pos.y += 10.0f;
	}

	if (m_pos.y >= SCREEN_HEIGHT)
	{
		m_pos.y -= 10.0f;
	}

	SetPos(m_pos);

	if (GetFunnel())
	{
		if (m_bOnce)
		{
			m_pFunnel[0] = m_pFunnel[0]->Create(GetPos(), CFunnel::FUNNEL_BULLET);
			m_pFunnel[1] = m_pFunnel[1]->Create(GetPos(), CFunnel::FUNNEL_BULLET);

			m_bOnce = false;
		}

		m_pFunnel[0]->SetPos(D3DXVECTOR3(m_pos.x - 30.0f, m_pos.y + 40.0f, 0.0f));
		m_pFunnel[1]->SetPos(D3DXVECTOR3(m_pos.x + 30.0f, m_pos.y + 40.0f, 0.0f));
	}

	//状態変化
	switch (GetState())
	{
	case STATE_DEFAULT:
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case STATE_DAMAGE:
		m_nDamageTime++;
		m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		if ((m_nDamageTime % 7) == 0)
		{
			m_nDamageTime = 0;
			SetState(STATE_DEFAULT);
		}
		break;

	case STATE_INVINCIBLE:
		m_bInvincible = true;
		m_nDamageTime++;

		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		if ((m_nDamageTime % GetInvincible()) == 0)
		{
			m_bInvincible = false;
			m_nDamageTime = 0;
			SetState(STATE_DEFAULT);
		}
		break;

	default:
		break;
	}

	SetCol(m_col);

	//MPが２００になった時の処理
	if (GetMP() >= 200)
	{
		m_pFragment = m_pFragment->Create(D3DXVECTOR3(880.0f, 70.0f, 0.0f));
		CGame::GetScore()->Add(1000);
		SetMP(0);
	}

	//当たり判定
	for (int i = 0; i < GetObjAll(); i++)
	{
		if (m_bInvincible)
		{
			continue;
		}

		/*↓プレイヤーが無敵状態ではなかった場合通る↓*/

		CObject *pObject;

		pObject = CObject::GetMyObject(i);
		D3DXVECTOR3 posOld = CObject2D::GetPos();

		if (pObject == nullptr)
		{
			continue;
		}

		/*↓オブジェクトがnullptrではなかった場合通る↓*/

		CObject::EObjType objType;
		objType = pObject->GetObjType();

		if (objType == CObject::OBJTYPE_ENEMY)
		{
			CEnemy *pEnemy = (CEnemy*)pObject;
			D3DXVECTOR3 Enemypos = pObject->GetPos();
			bool bCollision = CObject2D::CircleCollision(posOld, Enemypos, 3.0f, 2);
			bool bGraze = CObject2D::CircleCollision(posOld, Enemypos, 4.0f, 2);

			//ダメージを受けた場合
			if (bCollision && (m_nTime % 30) == 0)
			{
				CFrameEffect *pFrameEffect = pFrameEffect->Create();
				CGame::GetScore()->Add(-50);
				SetState(CPlayer::STATE_INVINCIBLE);
				m_nTime = 0;
				int life = GetLife();
				life -= pEnemy->GetPlayerDamage();

				SetLife(life);
			}

			//グレイズが発動した場合
			else if (bGraze && (m_nTime % 40) == 0)
			{
				CGame::GetScore()->Add(250);

				m_nMp += 5;
				m_nTime = 0;
				SetMP(m_nMp);
			}
		}

		if (objType == CObject::OBJTYPE_ENEMYBULLET)
		{
			CEnemyBullet *pEnemyBullet = (CEnemyBullet*)pObject;
			bool bGraze = CObject2D::CircleCollision(m_pos, pEnemyBullet->GetPos(), 15.0f, 2);

			if (bGraze && pEnemyBullet->GetGraze())
			{
				CGame::GetScore()->Add(100);

				for (int i = 0; i < 5; i++)
				{
					CEffect *pEffect = CEffect::Create(GetPos(), D3DXVECTOR3(sinf((i * ((360 / 5) * (D3DX_PI / 180)))), cosf((i * ((360 / 5) * (D3DX_PI / 180)))), 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.5f, 1.0f), 120, CEffect::EFFECTTYPE_BRIGHT);
				}

				pEnemyBullet->SetGraze(false);
			}
		}
	}

	//プレイヤーの体力管理
	if (GetLife() >= 100)
	{
		SetLife(100);
	}

	if (GetLife() <= 0)
	{	//ライフが０になった場合
		for (int i = 0; i < 10; i++)
		{
			CEffect *pEffect = CEffect::Create(GetPos(), D3DXVECTOR3(sinf((i * ((360 / 10) * (D3DX_PI / 180)))), cosf((i * ((360 / 10) * (D3DX_PI / 180)))), 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 120, CEffect::EFFECTTYPE_EXPLOSION);
		}

		CGame::SetDeath(true);
		Uninit();
		return;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの描画処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayer::Draw()
{
	CObject2D::Draw();
}