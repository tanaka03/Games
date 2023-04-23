//=============================================================================
//
// 3D���[�V�����L�����N�^�[�N���X(motion_model3D.h)
// Author : �������l
// �T�v : 3D�v���C���[�������s��
//
//=============================================================================
#ifndef _MOTION_MODEL3D_H_			// ���̃}�N����`������ĂȂ�������
#define _MOTION_MODEL3D_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object.h"
#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CMotion;

//=============================================================================
// 3D�v���C���[�N���X
// Author : �������l
// �T�v : 3D�v���C���[�������s���N���X
//=============================================================================
class CMotionModel3D
{
public:
	//--------------------------------------------------------------------
	// �ÓI�����o�֐�
	//--------------------------------------------------------------------
	static CMotionModel3D *Create();			// 3D�v���C���[�̐���

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CMotionModel3D();
	~CMotionModel3D();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	HRESULT Init();											// ������
	void Uninit();												// �I��
	void Update();												// �X�V
	void Destroy() { m_bRelease = true; }

	// Setter
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; };				// �ʒu
	void SetModelPos(D3DXVECTOR3 pos) { m_pos = pos; };					// �ʒu
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	void SetSize(D3DXVECTOR3 size) { m_size = size; }			// �傫��
	void SetMtxWorld(D3DXMATRIX mtxWorld) { m_mtxWorld = mtxWorld; }	// ���[���h�}�g���b�N�X�̃Z�b�^�[
	void SetMotion(const char *pName);									// ���[�V�������̐ݒ�
	void SetMove(D3DXVECTOR3 inMove) { m_move = inMove; }
	void SetCol(D3DXCOLOR) {};
	void SetUpdateStop(bool isStop) { m_isUpdateStop = isStop; }
	void SetMaxMinVtx();

	// Getter
	D3DXVECTOR3 GetPos() { return m_pos; }						// �ʒu
	D3DXVECTOR3 GetSize()  { return m_size; }					// �傫��
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }						// ���[���h�}�g���b�N�X�̃Q�b�^�[
	CMotion *GetMotion() { return m_pMotion; }							// ���[�V�������̎擾
	D3DXVECTOR3 GetMove() { return m_move; }
	D3DXCOLOR GetCol() { return D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetMaxVtx() { return m_MaxVtx; }
	D3DXVECTOR3 GetMinVtx() { return m_MinVtx; }

	float LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0);

private:
	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CMotion			*m_pMotion;				// ���[�V�����C���X�^���X
	D3DXVECTOR3		m_MinVtx;				// ���f���̒��_�ŏ��l
	D3DXVECTOR3		m_MaxVtx;				// ���f���̒��_�ő�l
	D3DXMATRIX		m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3		m_pos;					// �ʒu
	D3DXVECTOR3		m_move;					// 
	D3DXVECTOR3		m_rot;					// ����
	D3DXVECTOR3		m_size;					// �傫��
	bool			m_isUpdateStop;			// �X�V���~������B
	bool m_bRelease;
};

#endif