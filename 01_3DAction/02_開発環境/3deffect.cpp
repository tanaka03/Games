#include "application.h"
#include "object3d.h"
#include "texture.h"
#include "3deffect.h"
#include "model.h"
#include "game.h"
#include "player.h"

//��������������������������������������������������������������
// 3D�G�t�F�N�g�̃R���X�g���N�^
//��������������������������������������������������������������
C3DEffect::C3DEffect(int nPriority)
{
	SetObjState(CObject::OBJSTATE_3D);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�̃f�X�g���N�^
//��������������������������������������������������������������
C3DEffect::~C3DEffect()
{
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�̐���
//��������������������������������������������������������������
C3DEffect * C3DEffect::Create(C3DEffect::SInfo& info, int priority)
{
	C3DEffect *pObj = nullptr;
	pObj = new C3DEffect(priority);

	//�k���`�F�b�N
	if (pObj != nullptr)
	{
		pObj->m_info = info;
		pObj->BindTexture(info.texTag);
		pObj->LoadModel(info.modelShape);
		pObj->Init();
	}

	return pObj;
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�̏�����
//��������������������������������������������������������������
HRESULT C3DEffect::Init()
{
	for (size_t i = 0; i < m_modelData.size(); i++)
	{
		m_modelData[i].posOffset = m_info.posOffset;
		m_modelData[i].rotOffset = m_info.rotOffset;
	}

	m_beginCol = m_info.col;
	m_rot = m_info.beginRot;
	m_scale = m_info.beginScale;

	return S_OK;
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�̏I��
//��������������������������������������������������������������
void C3DEffect::Uninit()
{
	//���f���f�[�^���󂶂�Ȃ��ꍇ
	if (!m_modelData.empty())
	{
		m_modelData.clear();
	}

	Destroy();
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�̍X�V
//��������������������������������������������������������������
void C3DEffect::Update()
{
	{
		// �ړ��̌�����
		m_info.moveValue *= m_info.moveAttenuation;

		// �ړ���
		m_pos.x += m_info.moveValue.x;
		m_pos.y += m_info.moveValue.y;
		m_pos.z += m_info.moveValue.z;

		// ��]��
		m_rot.x += m_info.rotateValue.x;
		m_rot.y += m_info.rotateValue.y;
		m_rot.z += m_info.rotateValue.z;

		// �g�k��
		m_scale.x += m_info.scalingValue.x;
		m_scale.y += m_info.scalingValue.y;
		m_scale.z += m_info.scalingValue.z;

		// �F�̑J��
		if (m_info.transitionCol.r != 1.0f &&
			m_info.transitionCol.g != 1.0f &&
			m_info.transitionCol.b != 1.0f)
		{
			m_info.col.r += (m_info.transitionCol.r - m_beginCol.r) / m_info.transitionColEndTime;
			m_info.col.g += (m_info.transitionCol.g - m_beginCol.g) / m_info.transitionColEndTime;
			m_info.col.b += (m_info.transitionCol.b - m_beginCol.b) / m_info.transitionColEndTime;
		}

		// �A���t�@�l�̌�����
		m_info.col.a -= m_info.alphaAttenuation;
	}

	// �G�~�b�^����̐����ł͂Ȃ��ꍇ
	if (!m_useEmitter)
	{
		m_info.life--;

		if (m_info.life <= 0)
		{
			Destroy();
		}
	}
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�̕`��
//��������������������������������������������������������������
void C3DEffect::Draw()
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();
	CTexture* pTexture = CApplication::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;				//�v�Z�p�}�g���b�N�X

	// Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	if (m_info.tractPlayer)
	{
		CPlayer *pPlayer = CApplication::GetInstance()->GetMode()->GetGame()->GetPlayer();

		// ���[���h�}�g���b�N�X��������
		D3DXMatrixIdentity(&m_ParentmtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_ParentmtxWorld, &m_ParentmtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_ParentmtxWorld, &m_ParentmtxWorld, &mtxTrans);

		D3DXMatrixMultiply(&m_ParentmtxWorld, &m_ParentmtxWorld, &pPlayer->GetMatrix());

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_ParentmtxWorld);
	}
	else
	{
		// ���[���h�}�g���b�N�X��������
		D3DXMatrixIdentity(&m_ParentmtxWorld);

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_ParentmtxWorld, &m_ParentmtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_ParentmtxWorld, &m_ParentmtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_ParentmtxWorld);
	}

	for (size_t i = 0; i < m_modelData.size(); i++)
	{
		// �f�o�C�X�̃|�C���^���擾
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

		D3DXMATRIX parent = m_ParentmtxWorld;		// �v���C���[�̈ʒu���擾
		D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
		D3DMATERIAL9 matDef;						// ���݂̃}�e���A����ۑ�
		D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

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
		D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

		//�e�̃}�g���b�N�X���v���C���[�ɂ���
		pDevice->GetTransform(D3DTS_WORLD, &parent);

		//�e�̃}�g���b�N�X�Ƃ������킹��
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &parent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���݂̃}�e���A����ۑ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_modelData[i].buffMat->GetBufferPointer();

		for (size_t j = 0; j < m_modelData[i].dwNum; j++)
		{
			//�}�e���A���̐ݒ�
			pMat[j].MatD3D.Diffuse = m_info.col;
			pMat[j].MatD3D.Emissive = m_info.col;
			pDevice->SetMaterial(&pMat[j].MatD3D);

			if (pMat[j].pTextureFilename != nullptr && m_info.useFileTexture)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, pTexture->ConfirmLoadedPath(pMat[j].pTextureFilename));
			}

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture);

			//���f���p�[�c�̕`��
			m_modelData[i].mesh->DrawSubset(j);
		}

		//�ێ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

	// Z�o�b�t�@�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�̃��f���f�[�^���擾
//��������������������������������������������������������������
void C3DEffect::LoadModel(std::string path)
{
	// ���f���f�[�^�̃|�C���^���擾
	CModel *pModel = CApplication::GetInstance()->GetModel();

	SModelData data = {};

	data.mesh = pModel->GetMesh(path);
	data.buffMat = pModel->GetBuffMat(path);
	data.dwNum = pModel->GetModelNum(path);
	data.maxModel = pModel->GetMaxModel(path);
	data.minModel = pModel->GetMinModel(path);
	data.numVtx = pModel->GetVertexCount(path);
	data.numPrim = pModel->GetPrimitiveCount(path);

	m_modelData.push_back(data);
}

//��������������������������������������������������������������
// 3D�G�t�F�N�g�̃e�N�X�`�����o�C���h
//��������������������������������������������������������������
void C3DEffect::BindTexture(std::string inPath)
{
	m_pTexture = CApplication::GetInstance()->GetTexture()->GetTexture(inPath);		//�e�N�X�`���̃|�C���^
}