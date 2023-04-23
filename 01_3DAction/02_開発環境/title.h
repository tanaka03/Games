#ifndef _TITLE_H_
#define _TITLE_H_

#include "mode.h"

class CObject2D;

class CTitle : public CMode
{
public:
	enum EMode
	{
		MODE_BEGIN = 0,
		MODE_SELECT,
		MODE_TRANSNEXT,
		MODE_MAX
	};

	enum ESelect
	{
		SELECT_GAMEPLAY = 0,
		SELECT_EXIT,
		SELECT_MAX
	};

	CTitle();
	~CTitle();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void TextBehavior();

private:
	std::vector<CObject2D*> m_pObj;
	EMode m_mode;
	ESelect m_select;
};

#endif