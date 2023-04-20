#include "application.h"
#include "ability.h"
#include "object2d.h"
#include "game.h"
#include "score.h"
#include "player.h"
#include "item_recovery.h"
#include "particle_manager.h"
#include "effect.h"

//����������������������������������������
//�A�C�e���̃R���X�g���N�^
//����������������������������������������
CRecoveryItem::CRecoveryItem()
{
	m_nLife = 250;
}

//����������������������������������������
//�A�C�e���̃f�X�g���N�^
//����������������������������������������
CRecoveryItem::~CRecoveryItem()
{
}

//����������������������������������������
//�A�C�e���̏���������
//����������������������������������������
HRESULT CRecoveryItem::Init()
{
	CObject2D::Init();
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject2D::SetScale(25.0f, 25.0f);
	CObject2D::SetTexture(CTexture::TEXTURE_RECOVERYITEM);

	return S_OK;
}

//����������������������������������������
//�A�C�e���̏I������
//����������������������������������������
void CRecoveryItem::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//����������������������������������������
//�A�C�e���̍X�V����
//����������������������������������������
void CRecoveryItem::Update()
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

		if (objType != CObject::OBJTYPE_PLAYER)
		{
			continue;
		}

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

//����������������������������������������
//�A�C�e���̕`�揈��
//����������������������������������������
void CRecoveryItem::Draw()
{
	CObject2D::Draw();
}