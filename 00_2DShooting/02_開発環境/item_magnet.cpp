#include "application.h"
#include "ability.h"
#include "object2d.h"
#include "game.h"
#include "score.h"
#include "item_magnet.h"
#include "player.h"
#include "effect.h"

//����������������������������������������
//�A�C�e���̃R���X�g���N�^
//����������������������������������������
CMagnetItem::CMagnetItem()
{
	m_nLife = 250;
}

//����������������������������������������
//�A�C�e���̃f�X�g���N�^
//����������������������������������������
CMagnetItem::~CMagnetItem()
{
}

//����������������������������������������
//�A�C�e���̏���������
//����������������������������������������
HRESULT CMagnetItem::Init()
{
	CObject2D::Init();
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject2D::SetScale(25.0f, 25.0f);
	CObject2D::SetTexture(CTexture::TEXTURE_MAGNET);

	return S_OK;
}

//����������������������������������������
//�A�C�e���̏I������
//����������������������������������������
void CMagnetItem::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//����������������������������������������
//�A�C�e���̍X�V����
//����������������������������������������
void CMagnetItem::Update()
{
	float fAttenuation = 6.0f;
	int recovery = 0;
	CObject2D::Update();

	//�v���C���[�̃A�C�e���̋z���͈�
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
				m_pos += vec * fAttenuation;
				SetPos(m_pos);
			}

			//�A�C�e���ɏՓ˂������̌���
			if (bCollision)
			{
				CGame::GetScore()->Add(125);
				CAbility::Create(pPlayer->GetPos(), CAbility::ABILITYTYPE_MAGNET);

				m_pEffect = m_pEffect->Create(pPlayer->GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.3f, 1.0f, 1.0f), 550, CEffect::EFFECTTYPE_SPARK);
				m_pEffect->SetBehavior(CEffect::BEHAVIOR_ROTATION, CEffect::BEHAVIOR_PLAYER, CEffect::BEHAVIOR_NONE);
				m_pEffect->SetRotSpeed(0.07f);
				m_pEffect->SetScale(60.0f, 60.0f);

				int mp = pPlayer->GetMP();
				mp += 2;
				pPlayer->SetMP(mp);

				Uninit();
				return;
			}
		}
	}
}

//����������������������������������������
//�A�C�e���̕`�揈��
//����������������������������������������
void CMagnetItem::Draw()
{
	CObject2D::Draw();
}