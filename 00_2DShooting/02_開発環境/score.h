//
//Score.h
//
#ifndef _SCORE_H_
#define _SCORE_H_

class CScore : public CObject2D
{
public:
	CScore();
	~CScore() override;

	static CScore *Create(D3DXVECTOR3 pos);
	static CScore *Create(D3DXVECTOR3 pos, int score);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Add(int nValue);

	void Set(int nScore);
	void SetRank();
	void SetIdx(int num) { m_nCntAll = num; }
	void SetResult(int score, int idx) { m_aRankingScore[idx] = score; }
	void SetUseRank(bool rank) { m_bUseRank = rank; }

	int Get() { return m_nScore; }
	int GetIdx() { return m_nCntAll; }
	int GetResult(int idx) { return m_aRankingScore[idx]; }
	bool GetUseRank() { return m_bUseRank; }

private:
	void Draw() override;
	int StrErase(char* Str, int Num);
	int m_nCntAll;
	bool m_bUseRank;
	static int m_nScore;
	static int m_nNum;
	static int m_nAll;
	static int m_aRankingScore[10];
	static int m_aPosTexU[8];
};

#endif