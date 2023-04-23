//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//Player.h
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object.h"
#include "motion_model3D.h"

class CCamera;
class CModel;
class C3DGauge;
class CGauge;
class CLine;
class CBullet;
class CNumber;

class CBeam;

class CMotionModel3D;

class CPlayer : public CObject
{
public:
	//--------------------------------------
	// モデルデータの構造体
	//--------------------------------------
	struct SModelData
	{
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点情報
		LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// インデックス情報
		LPD3DXMESH m_mesh;						// メッシュ情報
		LPD3DXBUFFER m_buffMat;					// マテリアル情報
		DWORD m_dwNum;							// マテリアルの個数
		D3DXVECTOR3 m_maxModel;					// モデルの最大値
		D3DXVECTOR3 m_minModel;					// モデルの最小値
		D3DXVECTOR3 m_posOffset;				// モデルの位置のオフセット
		D3DXVECTOR3 m_rotOffset;				// モデルの向きのオフセット
		int m_numVtx;							// 頂点数
		int m_numPrim;							// ポリゴン数
	};

	//--------------------------------------
	// スキル発動の構造体
	//--------------------------------------
	struct SSkill
	{
		bool m_damageField;
		bool m_beam;
	};

	//--------------------------------------
	// プレイヤーの移動関係の状態の列挙
	//--------------------------------------
	enum EEvent
	{
		EVENT_NONE = 0,
		EVENT_JUMPING,
		EVENT_FALLING,
	};

	//--------------------------------------
	// プレイヤーのモーションの列挙
	//--------------------------------------
	enum EMotionType
	{
		MOTION_NEUTRAL = 0,
		MOTION_MOVE,
		MOTION_ATTACK,
		MOTION_JUMP,
		MOTION_ATTACK2,
		MOTION_ATTACK3,
		MOTION_ATTACK4,
		MOTION_MAX
	};

	//--------------------------------------
	// プレイヤーの攻撃方法の列挙
	//--------------------------------------
	enum EAttack
	{
		ATTACK_FIRST = 0,
		ATTACK_SECOND,
		ATTACK_THIRD,
		ATTACK_BEAM,
		ATTACK_MAX
	};

	CPlayer();
	~CPlayer() override;

	static CPlayer *Create(D3DXVECTOR3 pos);
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Action();
	void Attack();
	void LoadModel(std::string path);
	void Motion(EMotionType type);
	void Invincible();
	void Destroy() override { m_bRelease = true; }

	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }
	void SetRotDest(D3DXVECTOR3 rot) { m_rotDest = rot; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetEvent(EEvent set) { m_event = set; }
	void SetSkill(SSkill skill) { m_skill = skill; }
	void SetLife(int value) { m_life = value; }
	void SetPower(int value) { m_basicPower = value; }
	void SetAttackSpeed(int value) { m_attackSpeed = value; }
	void SetSpeed(float value) { m_fSpeed = value; }
	void SetBasicWalkSpeed(float value) { m_basicWalkSpeed = value; }
	void SetCollision(bool set) { m_bCollision = set; }
	void SetInvincible(bool set) { m_invincible = set; }

	D3DXVECTOR3 GetPos() override { return m_objpos; }
	D3DXVECTOR3 GetPosOld() { return m_posOld; }
	D3DXVECTOR3 GetMove() { return m_move; }
	D3DXVECTOR3 GetRot() { return m_rot; }
	D3DXVECTOR3 GetRotDest() { return m_rotDest; }
	D3DXVECTOR3 GetVec() { return m_vec; }
	D3DXMATRIX GetMatrix() { return m_mtxWorld; }
	SModelData *GetModelData(int idx) { return &m_modelData[idx]; }
	SSkill GetSkill() { return m_skill; }
	EEvent GetEvent() { return m_event; }
	C3DGauge *GetHPGauge() { return m_pHp; }
	CGauge *GetExpGauge(int idx) { return m_pExp[idx]; }
	CGauge *GetSPGauge() { return m_pSp; }
	CMotionModel3D *GetMotionModel() { return m_pMotionModel; }
	int GetNumExpGauge() { return m_numExpGauge; }
	int GetPower() { return m_basicPower; }
	int GetAttackSpeed() { return m_attackSpeed; }
	float GetBasicWalkSpeed() { return m_basicWalkSpeed; }
	bool GetCollision() { return m_bCollision; }
	bool GetInvincible() { return m_invincible; }
	bool GetDestroy() override { return m_bRelease; }

private:
	D3DXVECTOR3 m_objpos;					// 位置
	D3DXVECTOR3 m_posOld;					// 前回の位置
	D3DXVECTOR3 m_beginPos;					// 最初の位置
	D3DXVECTOR3 m_move;						// プレイヤーの移動量
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_rotDest;					// 目的の向き
	D3DXVECTOR3 m_vec;						// プレイヤーの向きのベクトル
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	EEvent m_event;							// プレイヤーの移動関係の列挙
	EMotionType m_motionType;				// プレイヤーのモーションの列挙
	EAttack m_attackType;					// プレイヤーの攻撃方法の列挙
	std::vector<CGauge*> m_pExp;			// 経験値のポインタ
	std::vector<SModelData> m_modelData;	// モデルデータのベクター
	CMotionModel3D *m_pMotionModel;			// プレイヤーのモデルのポインタ
	C3DGauge *m_pHp;						// HPのポインタ
	CGauge *m_pSp;							// SPのポインタ
	CNumber *m_pDamage;						// ダメージ数値のポインタ
	CBeam *m_pSkill;						// スキルのポインタ

	int m_time;								// スキル発動間隔の時間
	int m_life;								// プレイヤーの体力
	int m_coolTime;							// 次の攻撃に遷移する場合のクールタイム
	int m_transitionTime;					// モーション遷移の時間
	int m_invincibleTime;					// 無敵時間
	int m_numExpGauge;						// 経験値ゲージのカウンタ
	float m_fSpeed;							// プレイヤーの速度
	float m_hitRadius;						// ヒット範囲
	bool m_invincible;						// 無敵かどうか
	bool m_bCollision;						// 当たり判定
	bool m_bJump;							// ジャンプしているかどうか
	bool m_bRelease;						// オブジェクトの死亡フラグ

	// プレイヤーステータス関係
	int m_basicPower;						// 基本の攻撃力
	int m_hitPower;							// ヒットした時の攻撃力
	int m_attackSpeed;						// 攻撃速度
	float m_basicWalkSpeed;					// 移動速度
	SSkill m_skill;							// スキル発動の構造体
};

#endif