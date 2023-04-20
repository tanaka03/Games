#include "magnet_field.h"
#include "enemy.h"
#include "texture.h"
#include "application.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//静的メンバ変数宣言
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
int CMagnetField::m_nCntAll = 0;

CMagnetField::CMagnetField()
{
	m_nEnableTime = 0;
	m_fCollision = 150.0f;
	m_nCntAll++;
}

CMagnetField::~CMagnetField()
{
}

HRESULT CMagnetField::Init()
{
	CObject2D::SetCol(D3DXCOLOR(1.0f,0.0f,1.0f,0.7f));
	CObject2D::SetScale(150.0f, 150.0f);
	CObject2D::Init();
	CObject2D::SetType(CObject::OBJTYPE_SKILL);
	CObject2D::SetTexture(CTexture::TEXTURE_PIPO_EFFECT2);
	return S_OK;
}

void CMagnetField::Uninit()
{
	m_nCntAll--;
	CObject2D::Uninit();
	CObject2D::Release();
}

void CMagnetField::Update()
{
	if (m_nCntAll >= 2)
	{
		Uninit();
		return;
	}

	CObject2D::Update();
	m_nEnableTime = GetEnableTime();
	m_nEnableTime--;

	//アニメーション
	CObject2D::SetAnim(10, 1 , 3, 1, true);

	SetEnableTime(m_nEnableTime);
	if (m_nEnableTime <= 0)
	{
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
			CEnemy *pEnemy = (CEnemy*)pObject;
			int life = pEnemy->GetLife();
			bool bCollision = CObject2D::CircleCollision(m_pos, Enemypos, m_fCollision, 2);

			if (!bCollision)
			{
				continue;
			}

			/*↓衝突判定がtrueになった場合通る↓*/

			D3DXVECTOR3 vec = m_pos - pEnemy->GetPos();

			//正規化
			D3DXVec3Normalize(&vec, &vec);

			pEnemy->SetMove(vec * 2);
		}
	}
}

void CMagnetField::Draw()
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