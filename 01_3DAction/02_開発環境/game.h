#ifndef _GAME_H_
#define _GAME_H_

#include "mode.h"

class CObject2D;
class CMeshField;
class CPlayer;
class CLight;
class CNumber;
class CStage;
class CEnemyEmitter;
class CAbilitySelect;

class CDepthBufferShadow;
class CLambert;
class CShadow;

class CGame : public CMode
{
public:
	CGame();
	~CGame();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void AddKillCount() { m_killCnt++; }
	void ComboDisappear() { m_comboDisappear = true; }
	void StopTimer() { m_stopTimer = true; }
	void StartTimer() { m_stopTimer = false; }
	void SetClear(bool clear) { m_bClear = clear; }
	void SetDeath(bool death) { m_bDeath = death; }

	CPlayer *GetPlayer() { return m_pPlayer; }
	CMeshField *GetMeshField() { return m_pMesh; }
	CLight *GetLight() { return m_pLight; }
	CNumber *GetCombo() { return m_pNumber; }
	CNumber *GetScore() { return m_pScore; }
	CStage *GetStage() { return m_pStage; }
	CAbilitySelect *GetAbilitySelect() { return m_pAbilitySelect; }
	CEnemyEmitter *GetEnemyEmitter() { return m_pEnemyEmitter; }
	CShadow *GetShadow() { return m_pShadow; }
	CLambert *GetLambert() { return m_pLambert; }
	CDepthBufferShadow *GetDepthBuffShadow() { return m_pDepthBuffShadow; }
	int GetKillCount() { return m_killCnt; }
	bool GetClear() { return m_bClear;}
	bool GetDeath() { return m_bDeath; }

private:
	CLight *m_pLight;
	CPlayer *m_pPlayer;
	CMeshField *m_pMesh;
	CNumber *m_pNumber;
	CNumber *m_pScore;
	CNumber *m_pTime;
	CStage *m_pStage;
	CEnemyEmitter *m_pEnemyEmitter;
	CAbilitySelect *m_pAbilitySelect;
	CObject2D *m_pEndBanner;

	CShadow *m_pShadow;
	CLambert *m_pLambert;
	CDepthBufferShadow *m_pDepthBuffShadow;

	int m_killCnt;
	int m_nTime;
	bool m_comboDisappear;
	bool m_stopTimer;
	bool m_bDeath;
	bool m_bClear;
};

#endif