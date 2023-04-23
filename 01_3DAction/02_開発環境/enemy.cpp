#include <stdlib.h>
#include "object3d.h"
#include "application.h"
#include "input.h"
#include "keyboard.h"
#include "enemy.h"
#include "camera.h"
#include "debugproc.h"
#include "file.h"
#include "light.h"
#include "model.h"
#include "meshfield.h"
#include "player.h"
#include "utility.h"
#include "game.h"
#include "3dgauge.h"
#include "particle.h"
#include "stage.h"
#include "motion.h"
#include "motion_model3D.h"
#include "parts.h"
#include "player.h"
#include "gauge.h"
#include "score.h"
#include "item.h"
#include "particle_emitter.h"

//��������������������������������������������������������������
// �G�̃R���X�g���N�^
//��������������������������������������������������������������
CEnemy::CEnemy() :
	m_col(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)),
	m_fAttenuation(0.6f),
	m_bCollision(false),
	m_OnceCollision(true)
{
	SetObjType(OBJTYPE_ENEMY);
	SetObjState(CObject::OBJSTATE_3D);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bJump = false;
}

//��������������������������������������������������������������
// �G�̃f�X�g���N�^
//��������������������������������������������������������������
CEnemy::~CEnemy()
{
}

//��������������������������������������������������������������
// �G�̐���
//��������������������������������������������������������������
CEnemy * CEnemy::Create(SInfo& info)
{
	CEnemy *pPlayer = nullptr;
	pPlayer = new CEnemy;

	//�k���`�F�b�N
	if (pPlayer != nullptr)
	{
		// �|���S���̏���������
		pPlayer->SetInfo(info);
		pPlayer->Init();
	}

	return pPlayer;
}

//��������������������������������������������������������������
// �G�̏�����
//��������������������������������������������������������������
HRESULT CEnemy::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	//���f���̃��[�h
	m_pMotionModel = CMotionModel3D::Create();
	m_pMotionModel->SetMotion(m_info.animationPath.c_str());

	m_info.power = 1;
	m_info.scale = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_fAttenuation = m_info.speed;

	for (int i = 0; i < m_pMotionModel->GetMotion()->GetMaxParts(); i++)
	{
		m_pMotionModel->GetMotion()->GetParts(i)->Init();
	}

	m_modelData.resize(1);
	m_modelData[0].minModel = m_pMotionModel->GetMinVtx();
	m_modelData[0].maxModel = m_pMotionModel->GetMaxVtx();

	m_pHp = C3DGauge::Create(m_objpos, D3DXVECTOR3(50.0f, 5.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), C3DGauge::GAUGETYPE_HP, CObject::PRIORITY_THIRD);
	m_pHp->ValueSetting(m_info.life);
	m_pHp->SetMaxValue(m_info.life);

	return S_OK;
}

//��������������������������������������������������������������
// �G�̏I��
//��������������������������������������������������������������
void CEnemy::Uninit()
{
	//���f���f�[�^���󂶂�Ȃ��ꍇ
	if (!m_modelData.empty())
	{
		m_modelData.clear();
	}

	if (m_pMotionModel != nullptr)
	{
		m_pMotionModel->Uninit();
		delete m_pMotionModel;
		m_pMotionModel = nullptr;
	}

	if (m_pHp != nullptr)
	{
		m_pHp->Destroy();
	}

	Destroy();
}

//��������������������������������������������������������������
// �G�̍X�V
//��������������������������������������������������������������
void CEnemy::Update()
{
	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

	m_posOld = m_objpos;

	m_pMotionModel->Update();

	// �Փ˔���
	CMeshField *pMesh = CApplication::GetInstance()->GetMode()->GetGame()->GetMeshField();
	bool collision = pMesh->Collision(m_objpos);

	if (m_bCollision)
	{
		m_move.y = 0.0f;
		m_objpos = D3DXVECTOR3(m_objpos.x, m_collisionPos.y, m_objpos.z);
		m_bJump = true;
	}
	if (collision)
	{
		D3DXVECTOR3 collisionPos = pMesh->GetHitPos();
		m_move.y = 0.0f;
		m_objpos = D3DXVECTOR3(m_objpos.x, collisionPos.y, m_objpos.z);
		m_bJump = true;
	}
	else
	{
		m_move.y -= 3.5f;
		m_bJump = false;
	}

	m_objpos += m_move;
	m_fAttenuation = m_info.speed;

	// ���[�V�����̑J�ڊ֌W
	if (m_transitionTime >= 0)
	{
		m_transitionTime--;
	}

	//�G�ƃv���C���[�̓����蔻��
	CObject *pObject = CObject::GetTop(PRIORITY_THIRD);
	while (pObject != nullptr)
	{
		if (pObject == this)
		{
			pObject = pObject->GetNext();
			continue;
		}

		//�I�u�W�F�N�g�̃^�C�v���擾
		CObject::EObjType objType = pObject->GetObjType();

		if (objType == OBJTYPE_ENEMY)
		{	// �I�u�W�F�N�g�^�C�v���G�̏ꍇ
			CEnemy *pObj = (CEnemy*)pObject;
			CEnemy::SModelData enemyModelData = *pObj->GetModelData(0);

			//���f���̔��a
			D3DXVECTOR3 selfModelRadius = (m_modelData[0].maxModel - m_modelData[0].minModel) / 2;
			D3DXVECTOR3 enemyModelRadius = (enemyModelData.maxModel - enemyModelData.minModel) / 2;

			if (CUtility::isCircleCollision(m_objpos, selfModelRadius.x, pObj->GetPos(), enemyModelRadius.x))
			{	// �G�ƓG�����������ꍇ
				m_fAttenuation = 0.0f;
			}
		}

		if (objType == OBJTYPE_PLAYER)
		{	//�I�u�W�F�N�g�^�C�v���v���C���[�̏ꍇ
			CPlayer *pObj = (CPlayer*)pObject;
			CPlayer::SModelData playerModelData = *pObj->GetModelData(0);

			//���f���̔��a
			D3DXVECTOR3 selfModelRadius = (m_modelData[0].maxModel - m_modelData[0].minModel) / 2;
			D3DXVECTOR3 playerModelRadius = (playerModelData.m_maxModel - playerModelData.m_minModel) / 2;

			if (CUtility::isCircleCollision(m_objpos, selfModelRadius.x, pObj->GetPos(), playerModelRadius.x))
			{	//�v���C���[�ƓG�����������ꍇ
				m_fAttenuation = 0.0f;
			}

			if (m_info.visionValue.empty())
			{	// �ݒ肳�ꂽ�����͈̔͂̐��l�����݂��Ȃ��ꍇ
				pObject = pObject->GetNext();
				continue;
			}

			for (size_t i = 0; i < m_info.visionValue.size(); i++)
			{
				if (CUtility::isCircleCollision(m_objpos, m_info.visionValue[i], pObj->GetPos(), playerModelRadius.x))
				{	//�v���C���[���G�̔���͈͓̔��������ꍇ
					Behavior(i);
				}
			}
		}

		pObject = pObject->GetNext();
	}

	if (m_posOld != m_objpos)
	{
		Motion(MOTION_MOVE);
	}
	else
	{
		Motion(MOTION_NEUTRAL);
	}

	EnemyState();

	m_pHp->SetPos(D3DXVECTOR3(m_objpos.x, m_objpos.y + 50.0f, m_objpos.z));
	m_pHp->SetValue(m_info.life);

	//�ړI�̕����̐��K��
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2;
	}

	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2;
	}

	//======================
	//���K��
	//======================
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}

	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}

	if (m_objpos.y <= -100.0f)
	{
		Destroy();
	}

	if (m_info.life <= 0)
	{
		CApplication::GetInstance()->GetMode()->GetGame()->AddKillCount();
		std::vector<std::string> list;

		int expNum = pPlayer->GetNumExpGauge();
		CGauge *pGauge = pPlayer->GetExpGauge(expNum);
		pGauge->AddValue(m_info.exp);

		CApplication::GetInstance()->GetMode()->GetGame()->GetScore()->AddValue(m_info.score);

		////�p�[�e�B�N���i�K��
		//CParticle::SInfo particle = {};
		//particle.pos = m_objpos;
		//particle.scale = D3DXVECTOR3(35.0f,35.0f,0.0f);
		//particle.col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		//particle.destCol = D3DXCOLOR(1.0f, 0.5f, 0.0f, 0.0f);
		//particle.colAttenuation = 0.8f;
		//particle.destroyTime = 70;
		//particle.rotateValue = 0.1f;
		//particle.fallDelayTime = 35;
		//particle.weight = 0.5f;

		//CUtility::stringMultiPush(list, "Rotate, ColorTransition, Gravity");
		//particle.infoProperty = list;

		//int popParticle = 10;

		//for (int i = 0; i < popParticle; i++)
		//{
		//	particle.move = D3DXVECTOR3(-sinf((i * ((360 / popParticle) * (D3DX_PI / 180)))), 1.5f, -cosf((i * ((360 / popParticle) * (D3DX_PI / 180))))) * 2.5f;
		//	CParticle::Create(particle, "STAR2", CObject::PRIORITY_THIRD);
		//}

		CParticleEmitter *pEmitter = CParticleEmitter::Create("Attack");
		pEmitter->SetPos(m_objpos);

		CItem::Create(m_objpos);

		Destroy();
	}
}

//��������������������������������������������������������������
// �G�̕`��
//��������������������������������������������������������������
void CEnemy::Draw()
{
	D3DXVECTOR3 playerPos = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer()->GetPos();
	D3DXVECTOR3 distance = playerPos - m_objpos;

	if (distance.x > 500.0f && distance.y > 350.0f && distance.z > 500.0f)
	{
		return;
	}

	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_enemymtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_enemymtxWorld, &m_enemymtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_enemymtxWorld, &m_enemymtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_enemymtxWorld);

	if (m_pMotionModel->GetMotion() != nullptr)
	{// �p�[�c�̕`��ݒ�
		m_pMotionModel->GetMotion()->SetParts(m_enemymtxWorld);
	}

	//�v���C���[�̈ʒu���f�̐ݒ�
	//EnemyMtx();

	////���f���̕`��
	//ModelDraw();
}

void CEnemy::Behavior(int idx)
{
	if (m_info.behavior.empty())
	{
		return;
	}

	CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

	// �Ǐ]
	if (m_info.behavior[idx] == "Adulation")
	{
		D3DXVECTOR3 playerPos = pPlayer->GetPos();

		D3DXVECTOR3 vec = D3DXVECTOR3(playerPos.x, playerPos.y + m_move.y, playerPos.z) - m_objpos;
		D3DXVec3Normalize(&vec, &vec);

		//�G�̈ړ�
		m_objpos += vec * m_fAttenuation;

		float rotX = playerPos.x - m_objpos.x;
		float rotZ = playerPos.z - m_objpos.z;

		//�����̌v�Z
		float angle = atan2f(rotX, rotZ) + D3DX_PI;
		m_rot = D3DXVECTOR3(0.0f, angle, 0.0f);
	}

	// �U��
	if (m_info.behavior[idx] == "Attack")
	{
		m_attackCnt++;
		if (m_info.coolTime >= m_attackCnt)
		{
			return;
		}

		Motion(MOTION_ATTACK);
		m_transitionTime = 20;
		int damage = -(m_info.power);

		if (!pPlayer->GetInvincible())
		{	// ���G��Ԃł͂Ȃ��ꍇ
			pPlayer->SetSpeed(0.5f);
			pPlayer->GetHPGauge()->AddValue(damage);
			pPlayer->SetLife(pPlayer->GetHPGauge()->GetValue());
		}

		m_attackCnt = 0;
	}
}

//��������������������������������������������������������������
// �G�̈ʒu�̃}�g���b�N�X�ݒ�
//��������������������������������������������������������������
void CEnemy::EnemyMtx()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_enemymtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_enemymtxWorld, &m_enemymtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_objpos.x, m_objpos.y, m_objpos.z);
	D3DXMatrixMultiply(&m_enemymtxWorld, &m_enemymtxWorld, &mtxTrans);

	//Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_enemymtxWorld);
}

//��������������������������������������������������������������
// �G�̃��f���̃}�g���b�N�X��ݒ�
//��������������������������������������������������������������
void CEnemy::ModelDraw()
{
	for (unsigned int i = 0; i < m_modelData.size(); i++)
	{
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
		D3DXMATRIX parent = m_enemymtxWorld;

		D3DXMATRIX mtxRot, mtxTrans, mtxScale;			//�v�Z�p�}�g���b�N�X
		D3DMATERIAL9 matDef;							//���݂̃}�e���A����ۑ�
		D3DXMATERIAL *pMat;								//�}�e���A���f�[�^�ւ̃|�C���^

		//�e�N�X�`���̐ݒ��߂�
		pDevice->SetTexture(0, NULL);

		//���[���h�}�g���b�N�X��������
		D3DXMatrixIdentity(&m_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_modelData[i].rotOffset.y, m_modelData[i].rotOffset.x, m_modelData[i].rotOffset.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_modelData[i].posOffset.x, m_modelData[i].posOffset.y, m_modelData[i].posOffset.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// �s��g�k�֐�
		D3DXMatrixScaling(&mtxScale, m_info.scale.x, m_info.scale.y, m_info.scale.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

		//�e�̃}�g���b�N�X���v���C���[�ɂ���
		pDevice->GetTransform(D3DTS_WORLD, &parent);

		//�e�̃}�g���b�N�X�Ƃ������킹��
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &parent);

		//Z�e�X�g
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		//���f���̉e
		//Shadow();

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���݂̃}�e���A����ۑ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_modelData[i].buffMat->GetBufferPointer();

		for (unsigned int j = 0; j < m_modelData[i].dwNum; j++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[j].MatD3D);

			D3DMATERIAL9 material = pMat[j].MatD3D;
			material.Diffuse = m_col;

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&material);

			//���f���p�[�c�̕`��
			m_modelData[i].mesh->DrawSubset(j);
		}

		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}

//��������������������������������������������������������������
// �G�̃��f���f�[�^���擾
//��������������������������������������������������������������
void CEnemy::LoadModel(std::string path)
{
	CModel *pModel = CApplication::GetInstance()->GetModel();
	SModelData data = {};

	data.mesh = pModel->GetMesh(path);
	data.buffMat = pModel->GetBuffMat(path);
	data.dwNum = pModel->GetModelNum(path);
	data.maxModel = pModel->GetMaxModel(path);
	data.minModel = pModel->GetMinModel(path);
	data.pVtxBuff = pModel->GetVtxBuff(path);
	data.pIdxBuff = pModel->GetIdxBuff(path);
	data.numVtx = pModel->GetVertexCount(path);
	data.numPrim = pModel->GetPrimitiveCount(path);

	m_modelData.push_back(data);
}

//��������������������������������������������������������������
// �G�̏�ԕω�
//��������������������������������������������������������������
void CEnemy::EnemyState()
{
	switch (m_state)
	{
	case CEnemy::STATE_DAMAGE:
		m_stateTime++;

		if ((m_stateTime % 10) == 0)
		{
			m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			m_state = CEnemy::STATE_DEFAULT;
		}
		break;

	default:
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_stateTime = 0;
		break;
	}
}

void CEnemy::Motion(EMotionType type)
{
	if (m_transitionTime >= 0)
	{
		return;
	}

	if (m_motionType == type)
	{	// �O��Ɠ������[�V�����^�C�v�������ꍇ
		return;
	}

	m_motionType = type;
	m_pMotionModel->GetMotion()->SetNumMotion(type);
}