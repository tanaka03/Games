#include "ability.h"
#include "application.h"
#include "enemybullet.h"
#include "effect.h"
#include "enemy.h"
#include "explosion.h"
#include "frameeffect.h"
#include "item.h"
#include "object2d.h"
#include "player.h"
#include "texture.h"
#include "score.h"
#include "game.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//敵の弾のコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemyBullet::CEnemyBullet() : m_tag(BULLETTAG_ENEMY)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCollisionTime = 0;
	m_fBulletCollision = 0.0f;
	m_bGraze = true;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//敵の弾のデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEnemyBullet::~CEnemyBullet()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//敵の弾の初期化処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CEnemyBullet::Init()
{
	CObject2D::SetCol(GetCol());
	CObject2D::SetScale(38.0f, 38.0f);
	CObject2D::Init();
	CObject2D::SetTexture(CTexture::TEXTURE_BIGBULLET);
	CObject2D::SetType(CObject::OBJTYPE_ENEMYBULLET);
	SetFirstPos(GetPos());
	SetBulletTag(m_tag);
	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//敵の弾の終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemyBullet::Uninit()
{
	CObject2D::Uninit();
	CObject::Release();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//敵の弾の更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemyBullet::Update()
{
	CObject2D::Update();
	float fMargin = 30.0f;
	m_col = GetCol();
	m_scale = GetScale();
	m_nLife = GetLife();
	m_fBulletCollision = GetCollisionScale();

	//弾の動きの設定
	m_move = TypeMotion(GetBulletType());

	m_nLife--;
	SetLife(m_nLife);
	if (m_nLife <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			m_pEffect = m_pEffect->Create(GetPos(), D3DXVECTOR3(sinf((i * ((360 / 3) * (D3DX_PI / 180)))), cosf((i * ((360 / 3) * (D3DX_PI / 180)))), 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 40, CEffect::EFFECTTYPE_ASTER);
			m_pEffect->SetScale(80.0f, 80.0f);
		}
		Uninit();
		return;
	}

	//画面外に出た場合の処理
	bool Range = CObject2D::RangeCollision(&GetPos(), -fMargin, SCREEN_WIDTH + fMargin, -fMargin, SCREEN_HEIGHT + fMargin);

	if (Range)
	{
		Uninit();
		return;
	}

	SetMove(m_move);
	SetScale(m_scale.x, m_scale.y);

	//当たり判定
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject *pObject;
		D3DXVECTOR3 Enemypos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pObject = CObject::GetMyObject(i);
		m_pos = CObject2D::GetPos();

		if (pObject == nullptr)
		{
			continue;
		}

		/*↓pObjectがnullptrではなかった場合通る↓*/

		if (GetBulletTag() != BULLETTAG_ENEMY)
		{
			continue;
		}

		/*↓弾のタグが敵の場合通る↓*/

		CObject::EObjType objType;
		objType = pObject->GetObjType();
		Enemypos = pObject->GetPos();

		if (objType != CObject::OBJTYPE_PLAYER)
		{
			continue;
		}

		/*↓オブジェクトタイプがプレイヤーだった場合通る↓*/

		CPlayer *pPlayer = (CPlayer*)pObject;
		CPlayer::ESTATE state = pPlayer->GetState();

		if (state == pPlayer->STATE_INVINCIBLE)
		{
			continue;
		}

		/*↓プレイヤーが無敵状態ではなかった場合通る↓*/

		int life = pPlayer->GetLife();
		bool bCollision = CObject2D::CircleCollision(m_pos, Enemypos, m_fBulletCollision, 2);

		if (!bCollision)
		{
			continue;
		}

		life--;
		pPlayer->SetLife(life);
		pPlayer->SetState(CPlayer::STATE_INVINCIBLE);
		CFrameEffect *pFrameEffect = pFrameEffect->Create();

		for (int i = 0; i < 3; i++)
		{
			m_pEffect = m_pEffect->Create(GetPos(), D3DXVECTOR3(sinf((i * ((360 / 3) * (D3DX_PI / 180)))), cosf((i * ((360 / 3) * (D3DX_PI / 180)))), 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 40, CEffect::EFFECTTYPE_ASTER);
			m_pEffect->SetScale(80.0f, 80.0f);
		}

		Uninit();
		return;
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//敵の弾の描画処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEnemyBullet::Draw()
{
	CObject2D::Draw();
}
