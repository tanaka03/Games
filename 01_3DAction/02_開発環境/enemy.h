//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Enemy.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "object.h"

class C3DGauge;
class CMotionModel3D;

class CEnemy : public CObject
{
public:
	//--------------------------------------
	// モデルデータの構造体
	//--------------------------------------
	struct SModelData
	{
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
		LPDIRECT3DINDEXBUFFER9 pIdxBuff;
		LPD3DXMESH mesh;
		LPD3DXBUFFER buffMat;
		DWORD dwNum;
		D3DXVECTOR3 maxModel;
		D3DXVECTOR3 minModel;
		D3DXVECTOR3 posOffset;
		D3DXVECTOR3 rotOffset;
		int numVtx;
		int numPrim;
	};

	//--------------------------------------
	// エネミーインフォメーションの構造体
	//--------------------------------------
	struct SInfo
	{
		D3DXVECTOR3 scale;
		std::vector<std::string> behavior;
		std::vector<float> visionValue;
		std::string animationPath;
		int life;
		int score;
		int power;
		int coolTime;
		int exp;
		float speed;
	};

	//--------------------------------------
	// 敵の状態変化の列挙
	//--------------------------------------
	enum EEnemyState
	{
		STATE_DEFAULT = 0,
		STATE_DAMAGE,
		STATE_MAX
	};

	//--------------------------------------
	// 敵のモーションの状態の列挙
	//--------------------------------------
	enum EMotionType
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_MAX
	};

	CEnemy();
	~CEnemy() override;

	static CEnemy *Create(SInfo& info);

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Behavior(int idx);
	void Motion(EMotionType type);
	//virtual void Action();
	void Destroy() override { m_bRelease = true; }
	void AddLife(int value) { m_info.life += value; }

	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }
	void SetCollisionPos(D3DXVECTOR3 pos) { m_collisionPos = pos; }
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetState(EEnemyState state) { m_state = state; }
	void SetInfo(SInfo info) { m_info = info; }
	void SetMeshIdx(int idx) { m_meshIdx = idx; }
	void SetLife(int life) { m_info.life = life; }
	void SetAttenuation(float value) { m_fAttenuation = value; }
	void SetCollision(bool set) { m_bCollision = set; }
	void SetCollisionOnce(bool set) { m_OnceCollision = set; }

	D3DXVECTOR3 GetPos() override { return m_objpos; }
	D3DXVECTOR3 GetPosOld() { return m_posOld; }
	D3DXMATRIX GetMtx() { return m_mtxWorld; }
	SModelData *GetModelData(int idx) { return &m_modelData[idx]; }
	EEnemyState GetEnemyState() { return m_state; }
	int GetLife() { return m_info.life; }
	int GetMeshIdx() { return m_meshIdx; }
	int GetPower() { return m_info.power; }
	bool GetCollision() { return m_bCollision; }
	bool GetCollisionOnce() { return m_OnceCollision; }
	bool GetDestroy() override { return m_bRelease; }

private:
	void LoadModel(std::string path);
	void EnemyMtx();
	void ModelDraw();
	void EnemyState();

	D3DXVECTOR3 m_objpos;
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_collisionPos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_rotDest;
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;
	D3DXMATRIX m_enemymtxWorld;
	std::vector<SModelData> m_modelData;
	EEnemyState m_state;
	EMotionType m_motionType;
	SInfo m_info;
	CMotionModel3D *m_pMotionModel;
	C3DGauge *m_pHp;
	int m_stateTime;
	int m_transitionTime;
	int m_meshIdx;
	int m_attackCnt;
	float m_fAttenuation;
	bool m_bCollision;
	bool m_OnceCollision;
	bool m_bJump;
	bool m_bRelease;
};

#endif