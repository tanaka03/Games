#include "fragment.h"
#include "player.h"
#include "input.h"
#include "application.h"
#include "keyboard.h"

CFragment *CFragment::m_pFragment[MAX_FRAGMENT] = {};
int CFragment::m_nCntAll = 0;

CFragment::CFragment()
{
}

CFragment::~CFragment()
{
}

CFragment * CFragment::Create(D3DXVECTOR3 pos)
{
	int All = m_nCntAll;

	if (m_nCntAll >= MAX_FRAGMENT)
	{
		return 0;
	}

	m_pFragment[All] = new CFragment;

	//ヌルチェック
	if (m_pFragment[All] != nullptr)
	{
		// ポリゴンの初期化処理
		m_pFragment[All]->Init();
		m_pFragment[All]->SetPos(D3DXVECTOR3(pos.x + (20.0f * m_nCntAll), pos.y, 0.0f));
		m_nCntAll++;
	}

	return m_pFragment[All];
}

HRESULT CFragment::Init()
{
	CObject2D::SetCol(D3DXCOLOR(0.8f,0.5f,1.0f,1.0f));
	CObject2D::SetScale(25.0f, 25.0f);
	CObject2D::Init();
	CObject2D::SetTexture(CTexture::TEXTURE_FRAGMENT);
	return S_OK;
}

void CFragment::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void CFragment::Update()
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

		/*↓pObjectがnullptrではなかった場合通る↓*/

		CObject::EObjType objType;
		objType = pObject->GetObjType();

		if (objType != CObject::OBJTYPE_PLAYER)
		{
			continue;
		}

		/*↓オブジェクトタイプがプレイヤーの場合通る↓*/

		CPlayer *pPlayer = (CPlayer*)pObject;
		int Mp = pPlayer->GetMP();

		if (CApplication::GetInputKeyboard()->GetTrigger(DIK_O))
		{
			pPlayer->SetMP(199);
			m_nCntAll--;
			Uninit();
		}
	}
}

void CFragment::Draw()
{
	CObject2D::Draw();
}