#ifndef _MODE_H_
#define _MODE_H_

#include "object2d.h"

class CTitle;
class CGame;
class CResult;
class CTutorial;
class CBg;
class CCharUI;
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
		MODE_MAX
	};

	CMode();
	~CMode();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();

	//セッター
	static void SetMode(EMode mode);
	void SetNewScore(int score) { m_nNewScore = score; }

	//ゲッター
	static EMode GetMode() { return m_mode; }
	static CBg *GetBg() { return m_pBg; }
	static CCharUI *GetCharUI() { return m_pCharUI; }
	int GetNewScore() { return m_nNewScore; }

private:
	static EMode m_mode;
	static CFade *m_pFade;
	static CBg *m_pBg;
	static CCharUI *m_pCharUI;
	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static CTutorial *m_pTutorial;

	static int m_nNewScore;
};

#endif