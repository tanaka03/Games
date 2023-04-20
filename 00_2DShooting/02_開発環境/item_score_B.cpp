#include "application.h"
#include "object2d.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "item_score_B.h"
#include "sound.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CScoreItemB::CScoreItemB()
{
	m_nLife = 250;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CScoreItemB::~CScoreItemB()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムの初期化処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CScoreItemB::Init()
{
	CObject2D::Init();
	CObject2D::SetCol(D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f));
	CObject2D::SetScale(15.0f, 15.0f);
	CObject2D::SetTexture(CTexture::TEXTURE_SCOREITEM2);

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムの終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CScoreItemB::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CScoreItemB::Update()
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

		if (objType == CObject::OBJTYPE_PLAYER)
		{
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
				CApplication::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ITEM);
				int mp = pPlayer->GetMP();
				mp += 1;
				pPlayer->SetMP(mp);
				CGame::GetScore()->Add(75);
				Uninit();
				return;
			}
		}
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//アイテムの描画処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CScoreItemB::Draw()
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