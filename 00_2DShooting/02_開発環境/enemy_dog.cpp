#include "enemy_dog.h"
#include "item.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "frameeffect.h"

CEnemyDog::CEnemyDog()
{
	m_data.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nDamageTime = 0;
	m_data.fMinAngle = -0.5f;
	m_data.fMaxAngle = 1.0f;
	m_data.fAttenuation = 1.2f;
}

CEnemyDog::~CEnemyDog()
{
}

HRESULT CEnemyDog::Init()
{
	CObject2D::SetCol(m_data.col);
	CObject2D::Init();
	SetTexture(CTexture::TEXTURE_ENEMYDOG);

	return S_OK;
}

void CEnemyDog::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void CEnemyDog::Update()
{
	m_data.nLife = GetLife();
	CObject2D::Update();
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

	//敵の減衰
	if (m_data.fAttenuation >= 8.0f)
	{
		m_data.fAttenuation = 0.0f;
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

		CPlayer *pPlayer = (CPlayer*)pObject;
		D3DXVECTOR3 Playerpos = pObject->GetPos();
		D3DXVECTOR3 vec = Playerpos - m_pos;

		//正規化
		D3DXVec3Normalize(&vec, &vec);
		m_data.fRadius = 40.0f;
		m_data.fAttenuation += 0.2f;

		bool inner_product = AngleCollision(m_pos, Playerpos, m_data.fMinAngle, m_data.fMaxAngle, m_data.fRadius);

		if (!inner_product)
		{
			continue;
		}

		/*↓衝突判定がtrueになった場合通る↓*/

		//追従
		m_pos += vec * m_data.fAttenuation;
		SetPos(m_pos);

		bool damage = CircleCollision(m_pos, Playerpos, 8.0f, 2);

		if (!damage)
		{
			continue;
		}

		m_nDamageTime++;

		if ((m_nDamageTime % 20) == 0)
		{
			int life = pPlayer->GetLife();
			life -= 2;
			pPlayer->SetLife(life);
			CFrameEffect *pFrameEffect = pFrameEffect->Create();
			m_nDamageTime = 0;
		}

		bool hit = CircleCollision(m_pos, Playerpos, 6.0f, 2);

		if (!hit)
		{
			continue;
		}

		pPlayer->SetMove(vec * 5.0f);
		pPlayer->SetMoving(true);
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

void CEnemyDog::Draw()
{
	CObject2D::Draw();
}