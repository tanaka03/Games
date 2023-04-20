#include "enemy_bird.h"
#include "item.h"
#include "game.h"
#include "score.h"
#include "bullet.h"
#include "main.h"

CEnemyBird::CEnemyBird()
{
	m_data.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_data.fMinAngle = -0.5f;
	m_data.fMaxAngle = 1.5f;
	m_data.fAttenuation = 1.2f;
	m_fAngle = 0.0f;
}

CEnemyBird::~CEnemyBird()
{
}

HRESULT CEnemyBird::Init()
{
	CObject2D::SetCol(m_data.col);
	CObject2D::Init();
	SetTexture(CTexture::TEXTURE_ENEMYBIRD);

	return S_OK;
}

void CEnemyBird::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void CEnemyBird::Update()
{
	CObject2D::Update();
	float fMargin = 50.0f;
	m_data.nLife = GetLife();
	m_nBulletTime++;
	m_fAngle += 2.5f;

	if (m_bOnce)
	{
		SetFirstMove(GetMove());
		m_bOnce = false;
	}

	float moveX = sinf((D3DX_PI * 180) + (m_fAngle / 180)) * GetFirstMove().x;
	float moveY = cosf((D3DX_PI * 180) + (m_fAngle / 180)) * GetFirstMove().y;
	SetMove(D3DXVECTOR3(moveX, moveY, 0.0f));

	//‰æ–ÊŠO‚Éo‚½ê‡‚Ìˆ—
	bool Range = CObject2D::RangeCollision(&GetPos(), -fMargin, SCREEN_WIDTH + fMargin, -fMargin, SCREEN_HEIGHT + fMargin);

	//“G‚ª’e‚ðo‚·ˆ—
	if ((m_nBulletTime % GetFiringTime()) == 0)
	{
		if (!Range)
		{
			m_pBullet->Create(GetPos(), D3DXVECTOR3(-sinf((m_nCntBullet * ((180 / 20) * (D3DX_PI / 180)))), -cosf((m_nCntBullet * ((180 / 20) * (D3DX_PI / 180)))), 0.0f) * 2.5f, D3DXCOLOR(0.0f, 0.3f, 1.0f, 1.0f), GetBulletLife(), CBullet::BULLETTYPE_NORMAL, CBullet::BULLETTAG_ENEMY);
			m_nCntBullet++;
		}
	}

	if (m_nCntBullet >= 90)
	{
		m_nCntBullet = 0;
	}

	//“G‚Ìó‘Ô•Ï‰»
	switch (GetState())
	{
	case ENEMYSTATE_DEFAULT:	//’Êíó‘Ô
		m_data.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case ENEMYSTATE_DAMAGE:		//ƒ_ƒ[ƒW‚ðŽó‚¯‚½ó‘Ô
		m_nDamageTime++;
		m_data.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		if ((m_nDamageTime % 7) == 0)
		{
			SetState(ENEMYSTATE_DEFAULT);
		}
		break;
	}

	SetCol(m_data.col);

	//“G‚ÌŒ¸Š
	if (m_data.fAttenuation >= 8.0f)
	{
		m_data.fAttenuation = 0.0f;
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

void CEnemyBird::Draw()
{
	CObject2D::Draw();
}