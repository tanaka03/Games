#include "item_orb.h"
#include "player.h"
#include "game.h"
#include "score.h"
#include "effect.h"
#include "sound.h"
#include "application.h"

COrbItem::COrbItem()
{
}

COrbItem::~COrbItem()
{
}

HRESULT COrbItem::Init()
{
	CObject2D::Init();
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject2D::SetScale(25.0f, 25.0f);
	CObject2D::SetTexture(CTexture::TEXTURE_ORB);

	return S_OK;
}

void COrbItem::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void COrbItem::Update()
{
	CObject2D::Update();

	//�����蔻��
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
			bGraze = CObject2D::CircleCollision(m_pos, Playerpos, GetObtainScale(), 2);		//�����蔻��p�i�Ǐ]�j

			bool bCollision = false;
			bCollision = CObject2D::SquareCollision(m_pos, Playerpos, 11.0f, 2);	//�A�C�e�����蔻��

			if (bGraze)
			{
				D3DXVECTOR3 vec = Playerpos - m_pos;

				//���K��
				D3DXVec3Normalize(&vec, &vec);

				//�Ǐ]
				m_pos += vec * 0.8f;
				SetPos(m_pos);
			}

			//�A�C�e���ɏՓ˂������̌���
			if (bCollision)
			{
				CApplication::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ITEM);
				CGame::GetScore()->Add(500);
				pPlayer->SetFunnel(true);
				m_pEffect = m_pEffect->Create(pPlayer->GetPos(), D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), 120, CEffect::EFFECTTYPE_ROSE);
				m_pEffect->SetScale(100.0f,100.0f);
				Uninit();
				return;
			}
		}
	}
}

void COrbItem::Draw()
{
	CObject2D::Draw();
}