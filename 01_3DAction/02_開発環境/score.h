//
//Score.h
//
#ifndef _SCORE_H_
#define _SCORE_H_

#include "number.h"

class CScore : public CObject2D
{
public:
	CScore(int priority);
	~CScore() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	void SetScore(int score);
	void SetMaxScore(int digit);
	void SetDigit(int digit) { m_digit = digit; }
	void SetPosTexU(int pos) { m_posTexU = pos; }

private:
	void Draw() override;

	int m_posTexU;
	int m_digit;
	int m_score;
	int m_maxScore;
};

#endif