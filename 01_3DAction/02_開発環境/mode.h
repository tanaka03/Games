#ifndef _MODE_H_
#define _MODE_H_

class CTitle;
class CGame;
class CResult;
class CContinue;
class CFade;

class CMode
{
public:
	enum EMode
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_GAME,
		MODE_RESULT,
		MODE_TUTORIAL,
		MODE_CONTINUE,
		MODE_MAX
	};

	CMode();
	~CMode();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();

	void SetMode(EMode mode);

	EMode GetMode() { return m_mode; }
	CGame *GetGame() { return m_pGame; }

private:
	EMode m_mode;
	CTitle *m_pTitle;
	CGame *m_pGame;
	CResult *m_pResult;
	CContinue *m_pContinue;
	CFade *m_pFade;
};

#endif