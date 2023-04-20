#include "ability.h"
#include "application.h"
#include "playerbullet.h"
#include "effect.h"
#include "enemy.h"
#include "explosion.h"
#include "frameeffect.h"
#include "item.h"
#include "object2d.h"
#include "player.h"
#include "texture.h"
#include "score.h"
#include "sound.h"
#include "game.h"
#include "skill.h"
#include "input.h"
#include "keyboard.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの弾のコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayerBullet::CPlayerBullet() : m_tag(BULLETTAG_PLAYER)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Destpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, -25.0f, 0.0f);
	m_vec = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_fBulletCollision = 0.0f;
	m_bOnce = true;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの弾のデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CPlayerBullet::~CPlayerBullet()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの弾の初期化処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CPlayerBullet::Init()
{
	CObject2D::SetCol(GetCol());
	CObject2D::SetScale(38.0f, 38.0f);
	CObject2D::Init();
	CObject2D::SetTexture(CTexture::TEXTURE_BULLET);
	SetBulletTag(m_tag);
	SetFirstPos(GetPos());

	if (GetSound())
	{
		CApplication::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SHOT);
	}

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの弾の終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayerBullet::Uninit()
{
	CObject2D::Uninit();
	CObject::Release();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの弾の更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayerBullet::Update()
{
	CExplosion *pExplosion = nullptr;
	CObject2D::Update();
	m_col = GetCol();
	m_nLife = GetLife();
	m_fBulletCollision = GetCollisionScale();
	float fMargin = 50.0f;
	bool bAdulation = false;

	//弾の動きの設定
	m_move = TypeMotion(GetBulletType());

	//画面外に出た場合の処理
	bool Range = CObject2D::RangeCollision(&GetPos(), -fMargin, SCREEN_WIDTH + fMargin, -fMargin, SCREEN_HEIGHT + fMargin);

	if (Range)
	{
		Uninit();
		return;
	}

	SetMove(m_move);

	m_nLife--;
	SetLife(m_nLife);
	if (m_nLife <= 0)
	{//ライフが０になった場合
		
		for (int i = 0; i < 5; i++)
		{
			m_pEffect = m_pEffect->Create(GetPos(), D3DXVECTOR3(sinf((i * ((360 / 5) * (D3DX_PI / 180)))), cosf((i * ((360 / 5) * (D3DX_PI / 180)))), 0.0f), D3DXCOLOR(0.0f,0.8f,0.8f,1.0f), 40, CEffect::EFFECTTYPE_ASTER);
			m_pEffect->SetScale(80.0f, 80.0f);
		}

		Uninit();
		return;
	}

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

		CObject::EObjType objType;
		objType = pObject->GetObjType();
		Enemypos = pObject->GetPos();

		//オブジェクトタイプが敵の場合
		if (objType == CObject::OBJTYPE_ENEMY)
		{
			m_Destpos = pObject->GetPos();

			if (GetBulletTag() != BULLETTAG_PLAYER)
			{
				continue;
			}

			/*↓弾のタグがプレイヤーの場合通る↓*/

			CEnemy *pEnemy = (CEnemy*)pObject;
			int life = pEnemy->GetLife();
			bool bCollision = CObject2D::CircleCollision(m_pos, Enemypos, m_fBulletCollision, 2);

			switch (GetBulletType())
			{
			case BULLETTYPE_ADULATION:
				bAdulation = CObject2D::CircleCollision(m_pos, Enemypos, m_fBulletCollision * 8.0f, 2);

				if (bAdulation)
				{
					m_move = m_pBulletUtility->AdulationMotion(&GetPos(), &m_Destpos) * 12.5f;
				}
			break;

			default:
				break;
			}

			if (!bCollision)
			{
				continue;
			}

			/*↓衝突判定がtrueになった場合通る↓*/

			life--;
			pEnemy->SetLife(life);
			pEnemy->SetState(CEnemy::ENEMYSTATE_DAMAGE);
			Uninit();
			return;
		}
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//プレイヤーの弾の描画処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CPlayerBullet::Draw()
{
	//加算合成
	CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject2D::Draw();

	//設定を元に戻す
	CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
