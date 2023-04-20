#include "enemy_girl.h"
#include "item.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "effect.h"
#include "enemy_funnel.h"
#include "main.h"
#include "application.h"
#include "sound.h"

CEnemyGirl::CEnemyGirl()
{
	m_data.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nBulletTime = 0;
	m_bFunnel = false;
}

CEnemyGirl::~CEnemyGirl()
{
}

HRESULT CEnemyGirl::Init()
{
	CObject2D::SetCol(m_data.col);
	CObject2D::Init();
	SetTexture(CTexture::TEXTURE_ENEMYGIRL);

	return S_OK;
}

void CEnemyGirl::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void CEnemyGirl::Update()
{
	m_data.nLife = GetLife();
	CObject2D::Update();
	m_nBulletTime++;
	m_nItemTime++;
	SetMove(GetMove());

	if (GetPos().y <= 50.0f)
	{
		SetPos(D3DXVECTOR3(GetPos().x, 50.0f, 0.0f));
	}

	//敵の状態変化
	switch (GetState())
	{
	case ENEMYSTATE_DEFAULT:	//通常状態
		m_data.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case ENEMYSTATE_DAMAGE:		//ダメージを受けた状態
		m_nDamageTime++;
		m_data.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		if ((m_nDamageTime % 7) == 0)
		{
			SetState(ENEMYSTATE_DEFAULT);
		}
		break;
	}

	SetCol(m_data.col);

	if(m_nItemTime == 1500)
	{
		m_pItem = m_pItem->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f), EColor::COLOR_PINK, CItem::ITEMTYPE_ORB);

		for (int i = 0; i < 20; i++)
		{
			m_pEffect = m_pEffect->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(sinf((i * ((360 / 20) * (D3DX_PI / 180)))), cosf((i * ((360 / 20) * (D3DX_PI / 180)))), 0.0f) * 3.0f, D3DXCOLOR(1.0f, 0.0f, 0.5f, 1.0f), 45, CEffect::EFFECTTYPE_BRIGHT2);
		}
	}

	if (m_nItemTime == 2000)
	{
		m_pFunnel[0] = m_pFunnel[0]->Create(GetPos(), CEnemyFunnel::FUNNEL_BULLET);
		m_pFunnel[1] = m_pFunnel[1]->Create(GetPos(), CEnemyFunnel::FUNNEL_BULLET);
		m_bFunnel = true;
	}

	if (m_bFunnel)
	{
		m_pFunnel[0]->SetPos(D3DXVECTOR3(m_pos.x - 30.0f, m_pos.y - 40.0f, 0.0f));
		m_pFunnel[1]->SetPos(D3DXVECTOR3(m_pos.x + 30.0f, m_pos.y - 40.0f, 0.0f));
	}

	int random = rand() % 5;

	//敵が弾を出す処理
	if ((m_nBulletTime % GetFiringTime()) == 0)
	{
		m_pEffect = m_pEffect->Create(m_pos, D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXCOLOR(1.0f,0.0f,1.0f,0.8f), 150, CEffect::EFFECTTYPE_MAGIC2);
		m_pEffect->SetScale(80.0f, 80.0f);
		m_pEffect->SetAlphaBlend(false);
		m_pEffect->SetBehavior(CEffect::BEHAVIOR_ROTATION, CEffect::BEHAVIOR_INVISIBLE);

		for (int i = 0; i < 10; i++)
		{
			m_pEffect = m_pEffect->Create(m_pos, D3DXVECTOR3(sinf((i * ((360 / 10) * (D3DX_PI / 180)))), cosf((i * ((360 / 10) * (D3DX_PI / 180)))), 0.0f) * 3.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 30, CEffect::EFFECTTYPE_EXPLOSION);
			m_pEffect->SetAlphaBlend(false);
		}

		switch (random)
		{
		case 0:
			for (int i = 0; i < 10; i++)
			{
				m_pBullet->Create(m_pos, D3DXVECTOR3(sinf((i * ((360 / 10) * (D3DX_PI / 180)))), cosf((i * ((360 / 10) * (D3DX_PI / 180)))), 0.0f) * 3.0f, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), GetBulletLife(), CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_ENEMY);
			}
			break;

		case 1:
			for (int i = 0; i < 10; i++)
			{
				m_pBullet->Create(D3DXVECTOR3(i * 150.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), GetBulletLife(), CBullet::BULLETTYPE_CURVE, CBullet::BULLETTAG_ENEMY);
			}
			break;

		case 2:
			for (int i = 0; i < 10; i++)
			{
				m_pBullet->Create(D3DXVECTOR3(1280.0f, 300.0f, 0.0f), D3DXVECTOR3(-sinf((i * ((180 / 10) * (D3DX_PI / 180)))), cosf((i * ((180 / 10) * (D3DX_PI / 180)))), 0.0f) * 3.0f, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 400, CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_ENEMY);
				m_pBullet->Create(D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(sinf((i * ((180 / 10) * (D3DX_PI / 180)))), -cosf((i * ((180 / 10) * (D3DX_PI / 180)))), 0.0f) * 3.0f, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 400, CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_ENEMY);
			}
			break;

		case 3:
			for (int i = 0; i < 10; i++)
			{
				m_pBullet->Create(m_pos, D3DXVECTOR3(sinf((i * ((360 / 10) * (D3DX_PI / 180)))), cosf((i * ((360 / 10) * (D3DX_PI / 180)))), 0.0f) * 3.0f, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), GetBulletLife(), CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_ENEMY);
				m_pBullet->Create(D3DXVECTOR3(m_pos.x - 100.0f, m_pos.y + 100.0f, 0.0f), D3DXVECTOR3(sinf((i * ((360 / 10) * (D3DX_PI / 180)))), cosf((i * ((360 / 10) * (D3DX_PI / 180)))), 0.0f) * 4.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), GetBulletLife(), CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_ENEMY);
				m_pBullet->Create(D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y + 100.0f, 0.0f), D3DXVECTOR3(sinf((i * ((360 / 10) * (D3DX_PI / 180)))), cosf((i * ((360 / 10) * (D3DX_PI / 180)))), 0.0f) * 4.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), GetBulletLife(), CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_ENEMY);
			}
			break;

		case 4:
			for (int i = 0; i < 10; i++)
			{
				m_pBullet->Create(D3DXVECTOR3(m_pos.x - 100.0f, m_pos.y + (75.0f * i), 0.0f), D3DXVECTOR3(-5.0f, 5.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.5f, 1.0f), 400, CBullet::BULLETTYPE_REFLECTION, CBullet::BULLETTAG_ENEMY);
				m_pBullet->Create(D3DXVECTOR3(m_pos.x + 100.0f, m_pos.y + (75.0f * i), 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.5f, 1.0f), 400, CBullet::BULLETTYPE_REFLECTION, CBullet::BULLETTAG_ENEMY);
			}
			break;

		default:
			break;
		}
	}

	//当たり判定
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject *pObject;

		pObject = CObject::GetMyObject(i);
		m_pos = CObject2D::GetPos();

		if (pObject == nullptr)
		{
			continue;
		}

		/*↓オブジェクトがnullptrではなかった場合通る↓*/

		CObject::EObjType objType;
		objType = pObject->GetObjType();

		if (objType != CObject::OBJTYPE_PLAYER)
		{
			continue;
		}

		/*↓オブジェクトタイプがプレイヤーの場合通る↓*/

		D3DXVECTOR3 Playerpos = pObject->GetPos();
		D3DXVECTOR3 vec = Playerpos - m_pos;

		//正規化
		D3DXVec3Normalize(&vec, &vec);
		m_data.fRadius = 30.0f;

		bool collision = CircleCollision(m_pos, Playerpos, 55.0f, 2);

		if (!collision)
		{
			continue;
		}
	}

	if (m_data.nLife <= 0)
	{
		for (int i = 0; i < 30; i++)
		{
			m_pEffect = m_pEffect->Create(D3DXVECTOR3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 100.0f, 0.0f), D3DXVECTOR3(sinf((i * ((360 / 30) * (D3DX_PI / 180)))), cosf((i * ((360 / 30) * (D3DX_PI / 180)))), 0.0f) * 3.0f, D3DXCOLOR(0.0f, 0.7f, 1.0f, 1.0f), 140, CEffect::EFFECTTYPE_EXPLOSION);
			m_pEffect->SetScale(150.0f, 150.0f);
		}

		CApplication::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_KO);
		CGame::GetScore()->Add(GetKillScore());
		CGame::SetClear(true);
		Uninit();
		return;
	}
}

void CEnemyGirl::Draw()
{
	CObject2D::Draw();
}