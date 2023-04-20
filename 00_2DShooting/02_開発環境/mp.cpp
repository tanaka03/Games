#include "application.h"
#include "game.h"
#include "mp.h"
#include "object.h"
#include "player.h"
#include "gaugeframe.h"
#include "char_ui.h"

CMp::CMp()
{
	m_mp = 0;
	m_maxMp = 200;
	m_Width = 100.0f;
	m_Height = 10.0f;
}

CMp::~CMp()
{
}

HRESULT CMp::Init()
{
	CObject2D::SetCol(D3DXCOLOR(0.8f, 0.0f, 0.8f, 1.0f));
	CObject2D::SetScale(m_Width, m_Height);
	CObject2D::Init();
	CObject2D::SetTexture(CTexture::TEXTURE_GAUGE);
	m_pos = GetPos();
	m_pChar = m_pChar->Create(D3DXVECTOR3(m_pos.x - 130.0f, m_pos.y, 0.0f), D3DXVECTOR2(60.0f, 12.0f), CCharUI::UI_MP, CCharUI::STATE_SELECT);
	m_pGaugeFrame = m_pGaugeFrame->Create(D3DXVECTOR3(m_pos.x + 55.0f, m_pos.y, 0.0f), D3DXVECTOR2(270.0f, 23.0f));
	return S_OK;
}

void CMp::Uninit()
{
	CObject2D::Uninit();
}

void CMp::Update()
{
	CObject2D::Update();

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject *pObject;
		pObject = CObject::GetMyObject(i);

		if (pObject == nullptr)
		{
			continue;
		}

		CObject::EObjType objType;
		objType = pObject->GetObjType();

		if (objType != CObject::OBJTYPE_PLAYER)
		{
			continue;
		}

		CPlayer *pPlayer = (CPlayer*)pObject;
		m_mp = pPlayer->GetMP();
	}

	//頂点座標の設定
	VERTEX_2D*pVtx;        //頂点情報へのポインタ 

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Width, m_pos.y - m_Height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_Width + ((m_maxMp / 100) * m_mp), m_pos.y - m_Height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Width, m_pos.y + m_Height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_Width + ((m_maxMp / 100) * m_mp), m_pos.y + m_Height, 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

void CMp::Draw()
{
	CObject2D::Draw();
}