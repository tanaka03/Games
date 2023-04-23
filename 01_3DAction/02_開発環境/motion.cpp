//**************************************************************************************************
//
// ���[�V��������(motion.cpp)
// Auther�F�������l
//
//**************************************************************************************************

//***************************************************************************
// �C���N���[�h
//***************************************************************************
#include <stdio.h>
#include <assert.h>

#include "application.h"
#include "motion.h"	
#include "objectX.h"
#include "parts.h"
#include "texture.h"
#include "objectX_group.h"

//=============================================================================
// �R���X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�������ɍs������
//=============================================================================
CMotion::CMotion(const char * pFileName)
{
	// �p�[�c���̏�����
	memset(&m_partsFile, 0, sizeof(m_partsFile));

	// ���[�V�����̏�����
	m_motion = nullptr;

	// �p�[�c���̏�����
	m_nMaxParts = 0;

	// ���[�V�����̓ǂݍ���
	LoodSetMotion(pFileName);

	// �������[�V����
	m_nNumMotion = 0;

	// ���[�V�������s����
	m_bMotion = false;

	// ���[�V�����u�����h
	m_bMotionBlend = false;
}

//=============================================================================
// �f�X�g���N�^
// Author : �������l
// �T�v : �C���X�^���X�I�����ɍs������
//=============================================================================
CMotion::~CMotion()
{
	assert(m_pParent == nullptr);
}

//=============================================================================
// ������
// Author : �������l
// �T�v : �p�[�c����X�t�@�C���ǂݍ���
//=============================================================================
void CMotion::Init(void)
{
	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{// �J�E���g�̃��Z�b�g
		CntReset(nCntMotion);
	}
}

//=============================================================================
// �I��
// Author : �������l
// �T�v : �������̉��
//=============================================================================
void CMotion::Uninit(void)
{
	for (int i = 0; i < MAX_MOTION; i++)
	{
		if (&m_motion[i] != nullptr)
		{// �������̉��
			if (m_motion[i].pKeySet != nullptr)
			{
				for (int j = 0; j < m_motion[i].nNumKey; j++)
				{
					if (m_motion[i].pKeySet[j].pKey != nullptr)
					{
						delete[] m_motion[i].pKeySet[j].pKey;
						m_motion[i].pKeySet[j].pKey = nullptr;
					}
				}
				delete[] m_motion[i].pKeySet;
				m_motion[i].pKeySet = nullptr;
			}
		}
	}
	if (m_motion != nullptr)
	{// �������̉��
		delete[] m_motion;
		m_motion = nullptr;
	}

	for (int i = 0; i < m_nMaxParts; i++)
	{
		if (m_pParts[i] != NULL)
		{
			m_pParts[i]->Uninit();
			m_pParts[i] = nullptr;
		}
	}

	if (!m_pParts.empty())
	{
		m_pParts.clear();
	}
}

//=============================================================================
// �X�V
// Author : �������l
// �T�v : ���[�V�����̍X�V
//=============================================================================
void CMotion::Update()
{
	if (m_bMotionBlend)
	{
		MotionBlend();
	}
	else if (m_bMotion
		&& !m_bMotionBlend)
	{
		PlayMotion();
	}
}

//=============================================================================
// ���[�V�����̐ݒ�
// Author : �������l
// �T�v : ���[�V�����̏����ʒu�ɐݒ�
//=============================================================================
void CMotion::SetMotion(const int nCntMotionSet)
{
	CMotion::MyMotion *motion = (m_motion + nCntMotionSet);

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		// �ϐ��錾
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����
		D3DXVECTOR3 posOrigin = m_pParts[nCntParts]->GetPosOrigin();		// ���̈ʒu
		D3DXVECTOR3 rotOrigin = m_pParts[nCntParts]->GetRotOrigin();		// ���̌���

		// �ʒu�̐ݒ�
		pos = (posOrigin + motion->pKeySet[motion->nCntKeySet].pKey[nCntParts].pos);

		//	�����̐ݒ�
		rot = (rotOrigin + motion->pKeySet[motion->nCntKeySet].pKey[nCntParts].rot);

		// �p�x�̐��K��
		rot.x = RotNormalization(rot.x);
		rot.y = RotNormalization(rot.y);
		rot.z = RotNormalization(rot.z);

		// ���̍X�V
		m_pParts[nCntParts]->SetPos(pos);
		m_pParts[nCntParts]->SetRot(rot);
	}
}

//=============================================================================
// �p�[�c�̐ݒ�
// Author : �������l
// �T�v : �s��𗘗p���āA�p�[�c�̐e�q�֌W�ƕ`��ݒ���s��
//=============================================================================
void CMotion::SetParts(D3DXMATRIX mtxWorld)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{// ���f���̕`��
		if (m_pParts[nCntParts]->GetParent() != nullptr)
		{
			m_pParts[nCntParts]->Draw();
		}
		else
		{
			m_pParts[nCntParts]->Draw(mtxWorld);
		}
	}

	// �V�K�[�x�l��Z�o�b�t�@�̐[�x�l�������l�Ȃ�e�X�g�����ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// ���[�V�����̍Đ�
// Author : �������l
// �T�v : �ړI�̈ʒu�܂œ���̃t���[�����œ������鏈�����p�[�c���Ƃɍs��
//=============================================================================
void CMotion::PlayMotion()
{
	CMotion::MyMotion *motion = (m_motion + m_nNumMotion);

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		// �ϐ��錾
		D3DXVECTOR3 pos = m_pParts[nCntParts]->GetPos();			// �ʒu
		D3DXVECTOR3 rot = m_pParts[nCntParts]->GetRot();			// ����
		D3DXVECTOR3 posDest = m_pParts[nCntParts]->GetPosDest();	// �ړI�̈ʒu
		D3DXVECTOR3 rotDest = m_pParts[nCntParts]->GetRotDest();	// �ړI�̌���

		if (motion->nCntFrame == 0)
		{// �t���[���J�E���g��0�̎�
		 // �ϐ��錾
			D3DXVECTOR3 posOrigin = m_pParts[nCntParts]->GetPosOrigin();		// ���̈ʒu
			D3DXVECTOR3 rotOrigin = m_pParts[nCntParts]->GetRotOrigin();		// ���̌���

			// �ړI�̈ʒu�ƌ����̎Z�o
			posDest = (posOrigin + motion->pKeySet[motion->nCntKeySet].pKey[nCntParts].pos) - pos;
			rotDest = (rotOrigin + motion->pKeySet[motion->nCntKeySet].pKey[nCntParts].rot) - rot;

			// �p�x�̐��K��
			rotDest.x = RotNormalization(rotDest.x);
			rotDest.y = RotNormalization(rotDest.y);
			rotDest.z = RotNormalization(rotDest.z);

			// ���̍X�V
			m_pParts[nCntParts]->SetPosDest(posDest);
			m_pParts[nCntParts]->SetRotDest(rotDest);
		}

		// �ϐ��錾
		D3DXVECTOR3 addPos = D3DXVECTOR3(posDest / (float)(motion->pKeySet[motion->nCntKeySet].nFrame));
		D3DXVECTOR3 addRot = D3DXVECTOR3(rotDest / (float)(motion->pKeySet[motion->nCntKeySet].nFrame));

		// �ʒu�̉��Z
		pos += addPos;

		//	�����̉��Z
		rot += addRot;

		// �p�x�̐��K��
		rot.x = RotNormalization(rot.x);
		rot.y = RotNormalization(rot.y);
		rot.z = RotNormalization(rot.z);

		// ���̍X�V
		m_pParts[nCntParts]->SetPos(pos);
		m_pParts[nCntParts]->SetRot(rot);
	}

	// �t���[���J�E���g�̉��Z
	motion->nCntFrame++;

	if (motion->nCntFrame >= motion->pKeySet[motion->nCntKeySet].nFrame)
	{// �t���[���J�E���g���w��̃t���[�����𒴂����ꍇ
	 // �t���[�����̏�����
		motion->nCntFrame = 0;

		// �Đ����̃L�[�ԍ����̉��Z
		motion->nCntKeySet++;

		if (motion->nCntKeySet >= motion->nNumKey && motion->bLoop)
		{// �Đ����̃L�[���J�E���g���L�[���̍ő�l�𒴂����Ƃ��A���̃��[�V���������[�v���g�p���Ă���
		 // �Đ����̃L�[���J�E���g��������
			motion->nCntKeySet = 0;

		}
		else if (motion->nCntKeySet >= motion->nNumKey)
		{
			motion->nCntKeySet = 0;
			m_bMotion = false;
		}
	}
}

//=============================================================================
// ���[�V�����u�����h
// Author : �������l
// �T�v : ���[�V�����ƃ��[�V�����̂Ȃ��ڂ𒲐�����
// �Ԃ�l : ���[�V�����u�����h�g�p�̉�
//=============================================================================
void CMotion::MotionBlend()
{
	CMotion::MyMotion* motion = (m_motion + m_nNumMotion);

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		// �ϐ��錾
		D3DXVECTOR3 pos = m_pParts[nCntParts]->GetPos();			// �ʒu
		D3DXVECTOR3 rot = m_pParts[nCntParts]->GetRot();			// ����
		D3DXVECTOR3 posDest = m_pParts[nCntParts]->GetPosDest();	// �ړI�̈ʒu
		D3DXVECTOR3 rotDest = m_pParts[nCntParts]->GetRotDest();	// �ړI�̌���

		if (motion->nCntFrame == 0)
		{// �t���[���J�E���g��0�̎�
		 // �ϐ��錾
			D3DXVECTOR3 posOrigin = m_pParts[nCntParts]->GetPosOrigin();		// ���̈ʒu
			D3DXVECTOR3 rotOrigin = m_pParts[nCntParts]->GetRotOrigin();		// ���̌���

			// �ړI�̈ʒu�ƌ����̎Z�o
			CMotion::MyKey myKey = motion->pKeySet[motion->nCntKeySet].pKey[nCntParts];
			posDest = posOrigin + myKey.pos - pos;
			rotDest = rotOrigin + myKey.rot - rot;

			// �p�x�̐��K��
			rotDest.x = RotNormalization(rotDest.x);
			rotDest.y = RotNormalization(rotDest.y);
			rotDest.z = RotNormalization(rotDest.z);

			// ���̍X�V
			m_pParts[nCntParts]->SetPosDest(posDest);
			m_pParts[nCntParts]->SetRotDest(rotDest);
		}

		// �ϐ��錾
		D3DXVECTOR3 addPos = D3DXVECTOR3(posDest / (float)(MOTION_BLEND_FRAM));
		D3DXVECTOR3 addRot = D3DXVECTOR3(rotDest / (float)(MOTION_BLEND_FRAM));

		// �ʒu�̉��Z
		pos += addPos;

		//	�����̉��Z
		rot += addRot;

		// �p�x�̐��K��
		rot.x = RotNormalization(rot.x);
		rot.y = RotNormalization(rot.y);
		rot.z = RotNormalization(rot.z);

		// ���̍X�V
		m_pParts[nCntParts]->SetPos(pos);
		m_pParts[nCntParts]->SetRot(rot);
	}

	// �t���[���J�E���g�̉��Z
	motion->nCntFrame++;

	if (motion->nCntFrame >= MOTION_BLEND_FRAM)
	{// �t���[���J�E���g���w��̃t���[�����𒴂����ꍇ

		motion->nCntFrame = 0;	// �t���[�����̏�����
		motion->nCntKeySet++;	// �Đ����̃L�[�ԍ����̉��Z

		m_bMotionBlend = false;
	}
}

//=============================================================================
// �p�[�c�ƃ��[�V�����̓ǂݍ���
// Author : �������l
// �T�v : �p�[�c�ƃ��[�V�����̓ǂݍ��݁A���������Ăяo��
//=============================================================================
void CMotion::LoodSetMotion(const char *pFileName)
{
	// �ϐ��錾
	char aString[128] = {};		// �������r�p�̕ϐ�
	char g_aEqual[128] = {};	// ���ǂݍ��ݗp�ϐ�
	int	nCntKeySet = 0;			// KeySet�J�E���g
	int	nCntKey = 0;			// Key�J�E���g
	int nCntFileName = 0;		// �t�@�C����
	int nCntParts = 0;			// �p�[�c���̃J�E���g
	int nCntMotion = 0;			// ���[�V�������̃J�E���g

	// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	//�t�@�C�����J��
	pFile = fopen(pFileName, "r");

	if (pFile == nullptr)
	{
		assert(false);
	}

	fscanf(pFile, "%s", &aString);

	while (strncmp(&aString[0], "SCRIPT", 6) != 0)
	{// �����񂪈�v�����ꍇ
		aString[0] = {};
		// ������̓ǂݍ���
		fscanf(pFile, "%s", &aString[0]);
	}

	while (strncmp(&aString[0], "END_SCRIPT", 10) != 0)
	{
		fscanf(pFile, "%s", &aString[0]);

		if (strncmp(&aString[0], "#", 1) == 0)
		{// ���ǂݍ���
			fgets(&aString[0], sizeof(aString), pFile);
		}

		if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
		{// �t�@�C�����̓ǂݍ���
			fscanf(pFile, "%s", &g_aEqual[0]);
			fscanf(pFile, "%s", &m_partsFile[nCntFileName][0]);

			// �}�e���A�����̎擾
			std::string nameTag = "MOTION";

			nameTag += std::to_string(nCntFileName);

			CApplication::GetInstance()->GetObjectXGroup()->Load(nameTag, m_partsFile[nCntFileName]);
			nCntFileName++;
		}

		//-----------------------------------------------------------------

		if (strcmp(&aString[0], "CHARACTERSET") == 0)
		{// �L�����N�^�[�̓ǂݍ���
			while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strncmp(&aString[0], "#", 1) == 0)
				{// ���ǂݍ���
					fgets(&aString[0], sizeof(aString), pFile);
				}

				if (strcmp(&aString[0], "NUM_PARTS") == 0)
				{// �ǂݍ��ރp�[�c��
					fscanf(pFile, "%s", &g_aEqual[0]);
					fscanf(pFile, "%d", &m_nMaxParts);

					// �������̉��
					m_motion = new MyMotion[MAX_MOTION];
					for (int i = 0; i < MAX_MOTION; i++)
					{
						m_motion[i].pKeySet = nullptr;
					}

					assert(m_motion != nullptr);

					m_pParts.resize(m_nMaxParts);
					for (unsigned int i = 0; i < m_pParts.size(); i++)
					{// �p�[�c�̐���
						m_pParts[i] = CParts::Create();
					}
				}

				//-----------------------------------------------------------------

				if (strcmp(&aString[0], "PARTSSET") == 0)
				{// �p�[�c�̓ǂݍ���
					while (strcmp(&aString[0], "END_PARTSSET") != 0)
					{
						fscanf(pFile, "%s", &aString[0]);

						if (strncmp(&aString[0], "#", 1) == 0)
						{// ���ǂݍ���
							fgets(&aString[0], sizeof(aString), pFile);
						}

						if (strcmp(&aString[0], "INDEX") == 0)
						{// �^�C�v�̓ǂݍ���
							int nType = -1;
							fscanf(pFile, "%s", &g_aEqual[0]);
							fscanf(pFile, "%d", &nType);

							std::string nameTag = "MOTION";

							nameTag += std::to_string(nType);

							// �����œǍ���
							m_pParts[nCntParts]->LoadModel(nameTag.c_str());
							m_pParts[nCntParts]->CalculationVtx();
						}
						if (strcmp(&aString[0], "PARENT") == 0)
						{// �e�̓ǂݍ���
							int nIdxParent = -1;
							fscanf(pFile, "%s", &g_aEqual[0]);
							fscanf(pFile, "%d", &nIdxParent);

							if (nIdxParent != -1)
							{// �e�̃��f���̐ݒ�
								m_pParts[nCntParts]->SetParent(m_pParts[nIdxParent]);
							}
						}
						if (strcmp(&aString[0], "POS") == 0)
						{// �ʒu�̓ǂݍ���
							D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							fscanf(pFile, "%s", &g_aEqual[0]);
							fscanf(pFile, "%f", &pos.x);
							fscanf(pFile, "%f", &pos.y);
							fscanf(pFile, "%f", &pos.z);
							m_pParts[nCntParts]->SetPos(pos);
							m_pParts[nCntParts]->SetPosOrigin(pos);
						}
						if (strcmp(&aString[0], "ROT") == 0)
						{// �����̓ǂݍ���
							D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							fscanf(pFile, "%s", &g_aEqual[0]);
							fscanf(pFile, "%f", &rot.x);
							fscanf(pFile, "%f", &rot.y);
							fscanf(pFile, "%f", &rot.z);
							m_pParts[nCntParts]->SetRot(rot);
							m_pParts[nCntParts]->SetRotOrigin(rot);
						}
					}

					// �p�[�c�J�E���g�̃C���N�������g
					nCntParts++;
				}
			}
		}

		//-----------------------------------------------------------------

		if (strcmp(&aString[0], "MOTIONSET") == 0)
		{// ���[�V�����̓ǂݍ���
			while (strcmp(&aString[0], "END_MOTIONSET") != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strncmp(&aString[0], "#", 1) == 0)
				{// ���ǂݍ���
					fgets(&aString[0], sizeof(aString), pFile);
				}

				if (strcmp(&aString[0], "LOOP") == 0)
				{// ���[�v�L���̓ǂݍ���
					fscanf(pFile, "%s", &g_aEqual[0]);
					fscanf(pFile, "%d", (int*)(&m_motion[nCntMotion].bLoop));
				}
				if (strcmp(&aString[0], "NUM_KEY") == 0)
				{// �L�[���̓ǂݍ���
					fscanf(pFile, "%s", &g_aEqual[0]);
					fscanf(pFile, "%d", &m_motion[nCntMotion].nNumKey);

					// �������̊m��
					m_motion[nCntMotion].pKeySet = new MyKeySet[m_motion[nCntMotion].nNumKey];
					assert(m_motion[nCntMotion].pKeySet != nullptr);

					for (int nCntNumKeySet = 0; nCntNumKeySet < m_motion[nCntMotion].nNumKey; nCntNumKeySet++)
					{
						m_motion[nCntMotion].pKeySet[nCntNumKeySet].pKey = new MyKey[m_nMaxParts];
						assert(m_motion[nCntMotion].pKeySet[nCntNumKeySet].pKey != nullptr);
					}
				}

				//-----------------------------------------------------------------

				if (strcmp(&aString[0], "KEYSET") == 0)
				{// �L�[�Z�b�g�̓ǂݍ���
					while (strcmp(&aString[0], "END_KEYSET") != 0)
					{
						fscanf(pFile, "%s", &aString[0]);

						if (strncmp(&aString[0], "#", 1) == 0)
						{// ���ǂݍ���
							fgets(&aString[0], sizeof(aString), pFile);
						}

						if (strcmp(&aString[0], "FRAME") == 0)
						{// �t���[�����̓ǂݍ���
							fscanf(pFile, "%s", &g_aEqual[0]);
							fscanf(pFile, "%d", &m_motion[nCntMotion].pKeySet[nCntKeySet].nFrame);
						}
						if (strcmp(&aString[0], "KEY") == 0)
						{// �L�[�̓ǂݍ���
							while (strcmp(&aString[0], "END_KEY") != 0)
							{
								fscanf(pFile, "%s", &aString[0]);

								if (strncmp(&aString[0], "#", 1) == 0)
								{// ���ǂݍ���
									fgets(&aString[0], sizeof(aString), pFile);
								}

								if (strcmp(&aString[0], "POS") == 0)
								{// �ʒu�̓ǂݍ���
									fscanf(pFile, "%s", &g_aEqual[0]);
									fscanf(pFile, "%f", &m_motion[nCntMotion].pKeySet[nCntKeySet].pKey[nCntKey].pos.x);
									fscanf(pFile, "%f", &m_motion[nCntMotion].pKeySet[nCntKeySet].pKey[nCntKey].pos.y);
									fscanf(pFile, "%f", &m_motion[nCntMotion].pKeySet[nCntKeySet].pKey[nCntKey].pos.z);
								}
								if (strcmp(&aString[0], "ROT") == 0)
								{// �����̓ǂݍ���
									fscanf(pFile, "%s", &g_aEqual[0]);
									fscanf(pFile, "%f", &m_motion[nCntMotion].pKeySet[nCntKeySet].pKey[nCntKey].rot.x);
									fscanf(pFile, "%f", &m_motion[nCntMotion].pKeySet[nCntKeySet].pKey[nCntKey].rot.y);
									fscanf(pFile, "%f", &m_motion[nCntMotion].pKeySet[nCntKeySet].pKey[nCntKey].rot.z);
								}
							}

							// �L�[�J�E���g�̃C���N�������g
							nCntKey++;
						}
					}

					// �L�[�J�E���g�̏�����
					nCntKey = 0;

					// �L�[�Z�b�g�J�E���g�̃C���N�������g
					nCntKeySet++;
				}
			}
			// �L�[�Z�b�g�J�E���g�̏�����
			nCntKeySet = 0;

			// �p�[�c���̃C���N�������g
			nCntMotion++;
		}
	}

	//�t�@�C�������
	fclose(pFile);

	// ������
	Init();
}

//=============================================================================
// �p�[�c�̈ʒu�����Ƃ̈ʒu�ɖ߂�
// Author : �������l
// �T�v : �p�[�c�̈ʒu�����Ƃ̈ʒu�ɖ߂�
//=============================================================================
void CMotion::SetPartsOrigin()
{
	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		// �ʒu�̐ݒ�
		m_pParts[nCntParts]->SetPos(m_pParts[nCntParts]->GetPosOrigin());

		//	�����̐ݒ�
		m_pParts[nCntParts]->SetRot(m_pParts[nCntParts]->GetRotOrigin());
	}
}

//=============================================================================
// �J�E���g�̃��Z�b�g
// Author : �������l
// �T�v : �J�E���g�̃��Z�b�g
//=============================================================================
void CMotion::CntReset(const int nNumMotionOld)
{
	m_motion[nNumMotionOld].nCntFrame = 0;
	m_motion[nNumMotionOld].nCntKeySet = 0;
}

//=============================================================================
// ��]�̐��K��
// Author : �������l
// �T�v : �p�X��
//=============================================================================
float CMotion::RotNormalization(float inRot)
{
	// �p�x�̐��K��(���݂̊p�x)
	if (inRot > D3DX_PI)
	{
		inRot = inRot - D3DX_PI * 2;
	}
	else if (inRot < -D3DX_PI)
	{
		inRot = inRot + D3DX_PI * 2;
	}

	return inRot;
}

//=============================================================================
// ���[�V�����ԍ��̐ݒ�
// Author : �������l
// �T�v : ���[�V�����̔ԍ��̐ݒ�
//=============================================================================
void CMotion::SetNumMotion(const int nNumMotion)
{
	// ���[�V�����J�E���g�̃��Z�b�g
	CntReset(m_nNumMotion);

	// ���[�V�����ԍ��̐ݒ�
	m_nNumMotion = nNumMotion;

	// ���[�V�����u�����h���s��
	m_bMotionBlend = true;
	m_bMotion = true;
}
