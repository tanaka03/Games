//**************************************************************************************************
//
// ���[�V��������(motion.h)
// Auther�F�������l
// �T�v : ���[�V�����N���X�̐ݒ�
//
//**************************************************************************************************
#ifndef _MOTION_H_			// ���̃}�N����`������ĂȂ�������
#define _MOTION_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include "main.h"
#include "objectX.h"
#include "renderer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CParts;
class CModel3D;

//=============================================================================
// ���[�V�����N���X
// Author : �������l
// �T�v : ���[�V�����ݒ���s���N���X
//=============================================================================
class CMotion
{
public:
	//***************************************************************************
	// �萔��`
	//***************************************************************************
	static const unsigned int MAX_MOTION = (128);			// ���[�V�������̍ő吔
	static const unsigned int MAX_MODEL_PARTS = (128);		// ���f�����̍ő吔
	static const unsigned int MAX_KEY = (64);				// �L�[�̍ő吔
	static const unsigned int MAX_KEYSET = (64);			// �L�[�ݒ�̍ő吔
	static const unsigned int MOTION_BLEND_FRAM = (12);		// ���[�V�����u�����h�̃t���[����	

	//***************************************************************
	// �L�[�\���̂��`
	//***************************************************************
	struct MyKey
	{
		D3DXVECTOR3		pos;	// ���݈ʒu
		D3DXVECTOR3		rot;	// ���݂̌���
	};

	//***************************************************************
	// �L�[�ݒ�\���̂��`
	//***************************************************************
	struct MyKeySet
	{
		int		nFrame;			// �t���[����
		MyKey	*pKey;			// �L�[���
	};

	//***************************************************************
	// ���[�V�����ݒ�\���̂��`
	//***************************************************************
	struct MyMotion
	{
		int				nNumKey;				// �L�[��
		int				nCntKeySet;				// �L�[�Z�b�g�J�E���g
		int				nCntFrame;				// �t���[���J�E���g
		bool			bLoop;					// ���[�v�g�p��
		bool			bMotion;				// ���[�V�������s���Ă��邩
		MyKeySet		*pKeySet;				// �L�[�ݒ���
	};

	//--------------------------------------------------------------------
	// �R���X�g���N�^�ƃf�X�g���N�^
	//--------------------------------------------------------------------
	CMotion(const char *pFileName);
	~CMotion();

	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Update();	// �X�V
	void Uninit(void);	// �I��

	void ReloadMotion(const char *pFileName);	// ���[�V�����̍ēǂݍ���

	// Setter
	void SetPartsOrigin();							// �p�[�c�����Ƃ̏ꏊ�ɔz�u����
	void SetMotion(const int nCntMotionSet);		// ���[�V�����̏����ݒ�
	void SetParts(D3DXMATRIX mtxWorld);				// �p�[�c�̐ݒ�
	void SetNumMotion(const int nNumMotion);		// ���[�V�����ԍ��̐ݒ�
	void SetUseMotion(bool isMotion) { m_bMotion = isMotion; }			// ���[�V�������s���Ă��邩�ݒ�
	void SetMotionBlend(bool isBlend) { m_bMotionBlend = isBlend; }		// ���[�V�����u�����h���s���Ă��邩�ݒ�

	// Getter
	int GetMaxParts() { return m_nMaxParts; }			// �p�[�c�̍ő吔�̎擾
	bool GetMotion() { return m_bMotion; }				// ���[�V�������s���Ă��邩�擾
	bool GetMotionBlend() { return m_bMotionBlend; }	// ���[�V�����u�����h���s���Ă��邩�擾
	CParts *GetParts(int index) { return m_pParts[index]; }	// ���[�V�����u�����h���s���Ă��邩�擾

private:
	//--------------------------------------------------------------------
	// �����o�֐�
	//--------------------------------------------------------------------
	void Init();	// ������

	void PlayMotion();	// ���[�V�����̍Đ�
	void MotionBlend();	// ���[�V�����u�����h
	void LoodSetMotion(const char *pFileName);	// ���[�V�����ǂݍ���
	void CntReset(const int nNumMotionOld);	// �J�E���g���Z�b�g

	float RotNormalization(float inRot);

	//--------------------------------------------------------------------
	// �����o�ϐ�
	//--------------------------------------------------------------------
	CModel3D	*m_pParent;								// �e
	MyMotion	*m_motion;								// ���[�V����
	std::vector<CParts*>	m_pParts;					// �p�[�c
	char		m_partsFile[MAX_MODEL_PARTS][0xff];		// �p�[�c��X�t�@�C����
	int			m_nMaxParts;							// �p�[�c��
	int			m_nNumMotion;							// �������[�V����
	bool		m_bMotion;								// ���[�V�������s����
	bool		m_bMotionBlend;							// ���[�V�����u�����h
};
#endif

