#include "regeneration.h"
#include "player.h"
#include "item.h"
#include "texture.h"
#include "application.h"
#include "particle_manager.h"

CRegene::CRegene()
{
	m_nTime = 0;
}

CRegene::~CRegene()
{
}

HRESULT CRegene::Init()
{
	CObject2D::Init();
	return S_OK;
}

void CRegene::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void CRegene::Update()
{
	CObject2D::Update();
	int enable = GetEnableTime();
	m_nTime++;

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject *pObject;

		pObject = CObject::GetMyObject(i);

		if (pObject == nullptr)
		{
			continue;
		}

		/*«pObject‚ªnullptr‚Å‚Í‚È‚©‚Á‚½ê‡’Ê‚é«*/

		CObject::EObjType objType;
		objType = pObject->GetObjType();

		if (objType == CObject::OBJTYPE_PLAYER)
		{
			CPlayer *pPlayer = (CPlayer*)pObject;

			if ((m_nTime % 30) == 0)
			{
				int life = pPlayer->GetLife();
				life += 3;
				pPlayer->SetLife(life);
			}

			if (enable * 60 <= m_nTime)
			{
				Uninit();
				return;
			}
		}
	}
}