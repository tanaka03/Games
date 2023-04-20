#include "object2d.h"
#include "application.h"
#include "effect.h"
#include "main.h"
#include "texture.h"
#include "player.h"

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//エフェクトのコンストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEffect::CEffect()
{
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_scale = D3DXVECTOR2(20.0f, 20.0f);
	m_nTimer = 0;
	m_fRotSpeed = 0.02f;
	m_behaviorB = BEHAVIOR_NONE;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//エフェクトのデストラクタ
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEffect::~CEffect()
{
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//エフェクトの生成
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int life, EEffectType type)
{
	CEffect *pEffect = nullptr;
	pEffect = new CEffect;

	//ヌルチェック
	if (pEffect != nullptr)
	{
		// ポリゴンの初期化処理
		pEffect->Init(type);
		pEffect->SetPos(pos);
		pEffect->SetMove(move);
		pEffect->SetCol(col);
		pEffect->SetType(CObject::OBJTYPE_EFFECT);
		pEffect->SetLife(life);
	}

	return pEffect;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//エフェクトの初期化処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
HRESULT CEffect::Init(EEffectType type)
{
	CObject2D::SetScale(m_scale.x, m_scale.y);
	CObject2D::Init();

	switch (type)
	{
	case EFFECTTYPE_EXPLOSION:
		CObject2D::SetTexture(CTexture::TEXTURE_EFFECT1);
		break;

	case EFFECTTYPE_BRIGHT:
		CObject2D::SetTexture(CTexture::TEXTURE_EFFECT2);
		break;

	case EFFECTTYPE_BRIGHT2:
		CObject2D::SetTexture(CTexture::TEXTURE_EFFECT3);
		break;

	case EFFECTTYPE_HEART:
		CObject2D::SetTexture(CTexture::TEXTURE_EFFECTHEART);
		break;

	case EFFECTTYPE_SPARK:
		CObject2D::SetTexture(CTexture::TEXTURE_EFFECTSPARK);
		break;

	case EFFECTTYPE_ASTER:
		CObject2D::SetTexture(CTexture::TEXTURE_EFFECT4);
		break;

	case EFFECTTYPE_ROSE:
		CObject2D::SetTexture(CTexture::TEXTURE_PIPO_EFFECT3);
		m_bAnim = true;
		break;

	case EFFECTTYPE_MAGIC:
		CObject2D::SetTexture(CTexture::TEXTURE_EFFECTMAGIC1);
		break;

	case EFFECTTYPE_MAGIC2:
		CObject2D::SetTexture(CTexture::TEXTURE_EFFECTMAGIC2);
		break;
	}

	return S_OK;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//エフェクトの終了処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEffect::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//エフェクトの更新処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEffect::Update()
{
	CObject2D::Update();
	m_pos = GetPos();
	m_scale = GetScale();
	m_col = GetCol();
	m_nLife = GetLife();

	Behavior_Utility(GetBehavior());
	Behavior_Utility(GetBehaviorB());
	Behavior_Utility(GetBehaviorC());

	SetPos(m_pos);
	SetCol(m_col);
	SetScale(m_scale.x, m_scale.y);

	m_nTimer++;
	if (m_nTimer >= m_nLife)
	{
		Uninit();
		return;
	}

	if (m_bRotation)
	{
		//======================
		//正規化
		//======================
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2;
		}

		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2;
		}

		Rotation();
	}

	if (m_bAnim)
	{
		SetAnim(5, 3, 5, 1, false);
	}
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//エフェクトの描画処理
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void CEffect::Draw()
{
	if (GetAlphaBlend())
	{
		//加算合成
		CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	CObject2D::Draw();

	if (GetAlphaBlend())
	{
		//設定を元に戻す
		CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		CApplication::GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

void CEffect::Rotation()
{
	float s_fLength = sqrtf((m_scale.x * m_scale.x) + (m_scale.y * m_scale.y));
	float s_fAngle = atan2f(m_scale.x, m_scale.y);

	VERTEX_2D*pVtx;        //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI + s_fAngle)) * s_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI + s_fAngle)) * s_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - s_fAngle)) * s_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - s_fAngle)) * s_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - (0 + s_fAngle)) * s_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - (0 + s_fAngle)) * s_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z - (0 - s_fAngle)) * s_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z - (0 - s_fAngle)) * s_fLength;
	pVtx[3].pos.z = 0.0f;

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

void CEffect::Behavior_Utility(EBehavior type)
{
	switch (type)
	{
	case BEHAVIOR_SCALEUP:
		m_scale.x += 0.5f;
		m_scale.y += 0.5f;
		break;

	case BEHAVIOR_SCALEDOWN:
		m_scale.x -= 0.5f;
		m_scale.y -= 0.5f;
		break;

	case BEHAVIOR_INVISIBLE:
		m_col.a -= 0.01f;
		break;

	case BEHAVIOR_ROTATION:
		m_rot.z += GetRotSpeed();
		m_bRotation = true;
		break;

	case BEHAVIOR_PLAYER:
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
			SetPos(pPlayer->GetPos());
		}
		break;

	case BEHAVIOR_NONE:
		break;

	default:
		m_scale.x -= 0.2f;
		m_scale.y -= 0.2f;
		m_col.a -= 0.01f;
		break;
	}
}