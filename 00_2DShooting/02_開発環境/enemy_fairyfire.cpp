#include "enemy_fairyfire.h"
#include "item.h"
#include "bullet.h"
#include "game.h"
#include "score.h"

CEnemyFairyFire::CEnemyFairyFire()
{
	m_data.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nBulletTime = 0;
}

CEnemyFairyFire::~CEnemyFairyFire()
{
}

HRESULT CEnemyFairyFire::Init()
{
	CObject2D::SetCol(m_data.col);
	CObject2D::Init();
	SetTexture(CTexture::TEXTURE_ENEMYFAIRYFIRE);

	return S_OK;
}

void CEnemyFairyFire::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void CEnemyFairyFire::Update()
{
	m_data.nLife = GetLife();
	CObject2D::Update();
	m_nBulletTime++;
	SetMove(GetMove());

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

		bool collision = CircleCollision(m_pos, Playerpos, 400.0f, 2);

		if (!collision)
		{
			continue;
		}

		//敵が弾を出す処理
		if ((m_nBulletTime % GetFiringTime()) == 0)
		{
			for (int i = -1; i < 2; i++)
			{
				m_pBullet = m_pBullet->Create(m_pos, D3DXVECTOR3(vec.x + (1.0f * i), vec.y + (1.0f * i), 0.0f) * 5.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), GetBulletLife(), CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_ENEMY);
				m_pBullet->SetTexture(CTexture::TEXTURE_REDBULLET);
				m_pBullet->SetScale(25.0f,25.0f);
			}
		}
	}

	if (m_data.nLife <= 0)
	{
		if (GetWidth() >= 50.0f, GetHeight() >= 50.0f)
		{
			m_pItem->Create(GetPos(), D3DXVECTOR3(0.0f, 3.5f, 0.0f), CItem::ITEMTYPE_RECOVERY);
		}

		else
		{
			for (int i = 0; i < 10; i++)
			{
				m_pItem->Create(GetPos(), D3DXVECTOR3(sinf((i * ((360 / 10) * (D3DX_PI / 180)))), cosf((i * ((360 / 10) * (D3DX_PI / 180)))), 0.0f), CItem::ITEMTYPE_SCORE1);
			}
		}

		CGame::GetScore()->Add(GetKillScore());
		Uninit();
		return;
	}
}

void CEnemyFairyFire::Draw()
{
	CObject2D::Draw();
}