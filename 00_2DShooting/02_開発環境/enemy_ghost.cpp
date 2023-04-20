#include "enemy_ghost.h"
#include "item.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "main.h"

CEnemyGhost::CEnemyGhost()
{
	m_data.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_data.fMinAngle = -1.0f;
	m_data.fMaxAngle = 2.0f;
	m_data.fAttenuation = 2.0f;
	m_nBulletTime = 0;
}

CEnemyGhost::~CEnemyGhost()
{
}

HRESULT CEnemyGhost::Init()
{
	CObject2D::SetCol(m_data.col);
	CObject2D::Init();
	SetTexture(CTexture::TEXTURE_ENEMYGHOST);

	return S_OK;
}

void CEnemyGhost::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void CEnemyGhost::Update()
{
	m_data.nLife = GetLife();
	CObject2D::Update();
	float fMargin = 50.0f;
	m_nBulletTime++;
	SetMove(GetMove());

	//アニメーション
	CObject2D::SetAnim(5,1,15,1,true);

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

	//画面外に出た場合の処理
	bool Range = CObject2D::RangeCollision(&GetPos(), -fMargin, SCREEN_WIDTH + fMargin, -fMargin, SCREEN_HEIGHT + fMargin);

	//敵が弾を出す処理
	if ((m_nBulletTime % GetFiringTime()) == 0)
	{
		if (!Range)
		{
			m_pBullet->Create(m_pos, D3DXVECTOR3(0.0f, 4.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), GetBulletLife(), CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_ENEMY);
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

		bool inner_product = AngleCollision(m_pos, Playerpos, m_data.fMinAngle, m_data.fMaxAngle, m_data.fRadius);

		if (!inner_product)
		{
			continue;
		}

		/*↓衝突判定がtrueになった場合通る↓*/

		//追従
		m_pos += vec * m_data.fAttenuation;
		SetPos(m_pos);
	}

	if (m_data.nLife <= 0)
	{
		if (GetWidth() >= 50.0f, GetHeight() >= 50.0f)
		{
			m_pItem->Create(GetPos(), D3DXVECTOR3(0.0f, 3.5f, 0.0f), CItem::ITEMTYPE_MAGNET);
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

void CEnemyGhost::Draw()
{
	CObject2D::Draw();
}