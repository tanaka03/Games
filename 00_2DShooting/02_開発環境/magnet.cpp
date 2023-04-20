#include "magnet.h"
#include "player.h"
#include "item.h"
#include "texture.h"
#include "application.h"
#include "particle_manager.h"

CMagnet::CMagnet()
{
	m_nTime = 0;
}

CMagnet::~CMagnet()
{
}

HRESULT CMagnet::Init()
{
	CObject2D::Init();
	return S_OK;
}

void CMagnet::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

void CMagnet::Update()
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

		if (objType == CObject::OBJTYPE_ITEM)
		{
			CItem *pItem = (CItem*)pObject;
			pItem->SetMagnetUse(true);

			if (enable * 60 <= m_nTime)
			{
				pItem->SetMagnetUse(false);
				Uninit();
				return;
			}
		}
	}
}