#include "application.h"
#include "ability.h"
#include "object2d.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "item_recovery.h"
#include "particle_manager.h"
#include "effect.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CRecoveryItem::CRecoveryItem()
{
	m_nLife = 250;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CRecoveryItem::~CRecoveryItem()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムの初期化処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CRecoveryItem::Init()
{
	CObject2D::Init();
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject2D::SetScale(25.0f, 25.0f);
	CObject2D::SetTexture(CTexture::TEXTURE_RECOVERYITEM);

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムの終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CRecoveryItem::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CRecoveryItem::Update()
{
	float fAttenuation = 6.0f;
	int recovery = 0;
	CObject2D::Update();

	//プレイヤーのアイテムの吸収範囲
	m_fScale = 15.0f;
	if (GetMagnetUse())
	{
		m_fScale = 80.0f;
	}

	m_nLife--;

	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	//当たり判定
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject *pObject;
		D3DXVECTOR3 Playerpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pObject = CObject::GetMyObject(i);
		m_pos = CObject2D::GetPos();

		if (pObject == nullptr)
		{
			continue;
		}

		CObject::EObjType objType;
		objType = pObject->GetObjType();
		Playerpos = pObject->GetPos();

		if (objType != CObject::OBJTYPE_PLAYER)
		{
			continue;
		}

		CPlayer *pPlayer = (CPlayer*)pObject;

		bool bGraze = false;
		bGraze = CObject2D::CircleCollision(m_pos, Playerpos, GetObtainScale(), 2);		//かすり判定用（追従）

		bool bCollision = false;
		bCollision = CObject2D::SquareCollision(m_pos, Playerpos, 11.0f, 2);	//アイテム入手判定

		if (bGraze)
		{
			D3DXVECTOR3 vec = Playerpos - m_pos;

			//正規化
			D3DXVec3Normalize(&vec, &vec);

			//追従
			m_pos += vec * fAttenuation;
			SetPos(m_pos);
		}

		//アイテムに衝突した時の効果
		if (bCollision)
		{
			for (int i = 0; i < 40; i++)
			{
				m_pEffect = m_pEffect->Create(D3DXVECTOR3(rand() % 1280, 720.0f, 0.0f), D3DXVECTOR3(0.0f, -(rand() % 10), 0.0f), D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f), 55, CEffect::EFFECTTYPE_HEART);
				m_pEffect->SetBehavior(CEffect::BEHAVIOR_ROTATION, CEffect::BEHAVIOR_SCALEDOWN);
				m_pEffect->SetScale(90.0f, 90.0f);
			}

			CGame::GetScore()->Add(250);
			recovery = pPlayer->GetLife();
			recovery += 5;
			pPlayer->SetLife(recovery);
			int mp = pPlayer->GetMP();
			mp += 3;
			pPlayer->SetMP(mp);
			Uninit();
			return;
		}
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムの描画処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CRecoveryItem::Draw()
{
	CObject2D::Draw();
}