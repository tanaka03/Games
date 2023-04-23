//����������������������������������������
//Player.h
//����������������������������������������
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
	// ���f���f�[�^�̍\����
	//--------------------------------------
	struct SModelData
	{
		LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_���
		LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;		// �C���f�b�N�X���
		LPD3DXMESH m_mesh;						// ���b�V�����
		LPD3DXBUFFER m_buffMat;					// �}�e���A�����
		DWORD m_dwNum;							// �}�e���A���̌�
		D3DXVECTOR3 m_maxModel;					// ���f���̍ő�l
		D3DXVECTOR3 m_minModel;					// ���f���̍ŏ��l
		D3DXVECTOR3 m_posOffset;				// ���f���̈ʒu�̃I�t�Z�b�g
		D3DXVECTOR3 m_rotOffset;				// ���f���̌����̃I�t�Z�b�g
		int m_numVtx;							// ���_��
		int m_numPrim;							// �|���S����
	};

	//--------------------------------------
	// �X�L�������̍\����
	//--------------------------------------
	struct SSkill
	{
		bool m_damageField;
		bool m_beam;
	};

	//--------------------------------------
	// �v���C���[�̈ړ��֌W�̏�Ԃ̗�
	//--------------------------------------
	enum EEvent
	{
		EVENT_NONE = 0,
		EVENT_JUMPING,
		EVENT_FALLING,
	};

	//--------------------------------------
	// �v���C���[�̃��[�V�����̗�
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
	// �v���C���[�̍U�����@�̗�
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
	D3DXVECTOR3 m_objpos;					// �ʒu
	D3DXVECTOR3 m_posOld;					// �O��̈ʒu
	D3DXVECTOR3 m_beginPos;					// �ŏ��̈ʒu
	D3DXVECTOR3 m_move;						// �v���C���[�̈ړ���
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_rotDest;					// �ړI�̌���
	D3DXVECTOR3 m_vec;						// �v���C���[�̌����̃x�N�g��
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	EEvent m_event;							// �v���C���[�̈ړ��֌W�̗�
	EMotionType m_motionType;				// �v���C���[�̃��[�V�����̗�
	EAttack m_attackType;					// �v���C���[�̍U�����@�̗�
	std::vector<CGauge*> m_pExp;			// �o���l�̃|�C���^
	std::vector<SModelData> m_modelData;	// ���f���f�[�^�̃x�N�^�[
	CMotionModel3D *m_pMotionModel;			// �v���C���[�̃��f���̃|�C���^
	C3DGauge *m_pHp;						// HP�̃|�C���^
	CGauge *m_pSp;							// SP�̃|�C���^
	CNumber *m_pDamage;						// �_���[�W���l�̃|�C���^
	CBeam *m_pSkill;						// �X�L���̃|�C���^

	int m_time;								// �X�L�������Ԋu�̎���
	int m_life;								// �v���C���[�̗̑�
	int m_coolTime;							// ���̍U���ɑJ�ڂ���ꍇ�̃N�[���^�C��
	int m_transitionTime;					// ���[�V�����J�ڂ̎���
	int m_invincibleTime;					// ���G����
	int m_numExpGauge;						// �o���l�Q�[�W�̃J�E���^
	float m_fSpeed;							// �v���C���[�̑��x
	float m_hitRadius;						// �q�b�g�͈�
	bool m_invincible;						// ���G���ǂ���
	bool m_bCollision;						// �����蔻��
	bool m_bJump;							// �W�����v���Ă��邩�ǂ���
	bool m_bRelease;						// �I�u�W�F�N�g�̎��S�t���O

	// �v���C���[�X�e�[�^�X�֌W
	int m_basicPower;						// ��{�̍U����
	int m_hitPower;							// �q�b�g�������̍U����
	int m_attackSpeed;						// �U�����x
	float m_basicWalkSpeed;					// �ړ����x
	SSkill m_skill;							// �X�L�������̍\����
};

#endif