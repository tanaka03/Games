#include "reflect_sphere.h"
#include "enemy.h"
#include "texture.h"
#include "application.h"
#include "bullet.h"
#include "effect.h"

CReflectSphere::CReflectSphere()
{
	m_nEnableTime = 0;
	m_fAttenuation = 0.02f;
	m_fCollision = 20.0f;
	m_fScale = 135.0f;
}

CReflectSphere::~CReflectSphere()
{
}

HRESULT CReflectSphere::Init()
{
	CObject2D::SetCol(D3DXCOLOR(0.0f, 1.0f, 0.6f, 1.0f));
	CObject2D::SetScale(m_fScale, m_fScale);
	CObject2D::Init();
	CObject2D::SetTexture(CTexture::TEXTURE_BIGBULLET);

	m_move = GetMove();
	m_startPos = GetPos();

	return S_OK;
}

void CReflectSphere::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void CReflectSphere::Update()
{
	CObject2D::Update();
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nEnableTime = GetEnableTime();
	m_nEnableTime--;
	m_pos = GetPos();
	float fMargin = 50.0f;
	m_fScale -= 0.5f;
	m_fCollision -= 0.02f;

	SetScale(m_fScale, m_fScale);

	//壁の判定による反射の処理
	if (m_pos.y <= 0.0f)
	{
		D3DXVECTOR3 CollisionPos = GetPos();
		vec = CollisionPos - m_startPos;
		m_move = ReflectMotion(&vec, VEC_TOP) * m_fAttenuation;
		m_fAttenuation -= 0.005f;
	}

	if (m_pos.y >= SCREEN_HEIGHT)
	{
		D3DXVECTOR3 CollisionPos = GetPos();
		vec = CollisionPos - m_startPos;
		m_move = ReflectMotion(&vec, VEC_BOTTOM) * m_fAttenuation;
		m_fAttenuation -= 0.01f;
	}

	if (m_pos.x <= 0.0f)
	{
		D3DXVECTOR3 CollisionPos = GetPos();
		vec = CollisionPos - m_startPos;
		m_move = ReflectMotion(&vec, VEC_LEFT) * m_fAttenuation;
		m_fAttenuation -= 0.01f;
	}

	if (m_pos.x >= SCREEN_WIDTH)
	{
		D3DXVECTOR3 CollisionPos = GetPos();
		vec = CollisionPos - m_startPos;
		m_move = ReflectMotion(&vec, VEC_RIGHT) * m_fAttenuation;
		m_fAttenuation -= 0.01f;
	}

	SetMove(m_move);
	SetEnableTime(m_nEnableTime);

	//画面外に出た場合の処理
	bool Range = CObject2D::RangeCollision(&GetPos(), -fMargin, SCREEN_WIDTH + fMargin, -fMargin, SCREEN_HEIGHT + fMargin);

	if (m_nEnableTime <= 0 || Range)
	{
		for (int i = 0; i < 10; i++)
		{
			CEffect *pEffect = pEffect->Create(m_pos, D3DXVECTOR3(sinf((i * ((360 / 10) * (D3DX_PI / 180)))) * (rand() % 6), cosf((i * ((360 / 10) * (D3DX_PI / 180)))) * (rand() % 6), 0.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f), 30, CEffect::EFFECTTYPE_BRIGHT2);
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
			CEnemy *pEnemy = (CEnemy*)pObject;
			int life = pEnemy->GetLife();
			bool bCollision = CObject2D::CircleCollision(m_pos, Enemypos, m_fCollision, 2);

			if (!bCollision)
			{
				continue;
			}

			/*↓衝突判定がtrueになった場合通る↓*/

			m_CollisionTime++;
			if ((m_CollisionTime % 10) == 0)
			{
				life -= 2;
				pEnemy->SetLife(life);
				pEnemy->SetState(CEnemy::ENEMYSTATE_DAMAGE);
				m_CollisionTime = 0;
			}
		}
	}
}

void CReflectSphere::Draw()
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

D3DXVECTOR3 CReflectSphere::ReflectMotion(D3DXVECTOR3* vec, NormalVec type)
{
	D3DXVECTOR3 DestVec = *vec;
	D3DXVECTOR3 Vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (type)
	{
	case VEC_TOP:
		Vec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;

	case VEC_BOTTOM:
		Vec = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		break;

	case VEC_LEFT:
		Vec = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		break;

	case VEC_RIGHT:
		Vec = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		break;

	default:
		break;
	}

	D3DXVec3Normalize(&Vec, &Vec);
	float fDot = D3DXVec3Dot(&Vec, &(-DestVec));

	return (2 * fDot * Vec) + DestVec;
}