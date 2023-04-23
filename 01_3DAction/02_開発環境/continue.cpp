#include "continue.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "object2d.h"

CContinue::CContinue()
{
}

CContinue::~CContinue()
{
}

HRESULT CContinue::Init()
{
	m_pObj = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), "THANKYOU", CObject::PRIORITY_FOURTH);
	m_pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

void CContinue::Uninit()
{
}

void CContinue::Update()
{
	if (CApplication::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		m_pObj->Destroy();
		CApplication::GetInstance()->GetMode()->SetMode(MODE_TITLE);
	}
}