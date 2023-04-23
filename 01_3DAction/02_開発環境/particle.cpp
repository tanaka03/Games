//����������������������������������������
// �p�[�e�B�N������
//����������������������������������������
#include "application.h"
#include "renderer.h"
#include "particle.h"
#include "player.h"
#include "game.h"

//��������������������������������������������������������������
// �p�[�e�B�N���̃R���X�g���N�^
//��������������������������������������������������������������
CParticle::CParticle(int nPriority) :
	CBillboard(CObject::PRIORITY_THIRD),
	m_info({}),
	m_nTime(0)			// ����
{
}

//��������������������������������������������������������������
// �p�[�e�B�N���̃f�X�g���N�^
//��������������������������������������������������������������
CParticle::~CParticle()
{
}

//��������������������������������������������������������������
// �p�[�e�B�N���̐���
//��������������������������������������������������������������
CParticle * CParticle::Create(SInfo& info, const std::string url, int nPriority)
{
	CParticle *pParticle = new CParticle(nPriority);

	if (pParticle != nullptr)
	{
		pParticle->SetInfo(info);
		pParticle->SetPath(url);
		pParticle->Init();
	}
	else
	{
		assert(false);
	}

	return pParticle;
}

//��������������������������������������������������������������
// �p�[�e�B�N���̏�����
//��������������������������������������������������������������
HRESULT CParticle::Init()
{
	// �e�N�X�`���̓ǂݍ���
	BindTexture(m_path);

	// �I�u�W�F�N�g�̏�����
	CBillboard::Init();

	CBillboard::SetPos(m_info.pos);
	CBillboard::SetMove(m_info.move * m_info.moveAttenuation);
	CBillboard::SetCol(m_info.col);
	CBillboard::SetScale(m_info.scale);
	CBillboard::SetBlend(BLEND_ADDITIVE);

	return S_OK;
}

//��������������������������������������������������������������
// �p�[�e�B�N���̍X�V
//��������������������������������������������������������������
void CParticle::Update()
{
	CBillboard::Update();

	Behavior(m_info.infoProperty);
}

//��������������������������������������������������������������
// �p�[�e�B�N���̕`��
//��������������������������������������������������������������
void CParticle::Draw()
{
	// �f�o�C�X�̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstance()->GetRenderer()->GetDevice();

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�e�X�g
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CBillboard::Draw();

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// Z�o�b�t�@�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//��������������������������������������������������������������
// �p�[�e�B�N���̃v���p�e�B�ɉ���������
//��������������������������������������������������������������
void CParticle::Behavior(std::vector<std::string>& prop)
{
	for (auto &p : prop)
	{
		// �r���{�[�h�̉�]
		if (p == "Rotate")
		{
			CBillboard::Rotate(m_info.rotateValue);
		}

		// �F�̕ψ�
		else if (p == "ColorTransition")
		{
			D3DXCOLOR col = CBillboard::GetCol();

			col.r += (m_info.destCol.r - col.r) / (m_info.destroyTime * m_info.colAttenuation);
			col.g += (m_info.destCol.g - col.g) / (m_info.destroyTime * m_info.colAttenuation);
			col.b += (m_info.destCol.b - col.b) / (m_info.destroyTime * m_info.colAttenuation);

			CBillboard::SetCol(col);
		}

		// �g�k
		else if (p == "Scaling")
		{
			D3DXVECTOR3 scale = CBillboard::GetScale();

			scale.x += m_info.scalingValue.x;
			scale.y += m_info.scalingValue.y;
			scale.z += m_info.scalingValue.z;

			CBillboard::SetScale(scale);
		}

		// �d��
		else if (p == "Gravity")
		{
			D3DXVECTOR3 move = CBillboard::GetMove();

			if (m_nTime >= m_info.fallDelayTime)
			{
				move.y -= m_info.weight;
			}

			CBillboard::SetMove(move);
		}

		// �w�肵���ʒu�Ɍ������Ĉړ�
		else if (p == "Vector")
		{
			D3DXVECTOR3 objPos = CBillboard::GetPos();
			D3DXVECTOR3 vec = m_info.destPos - objPos;
			D3DXVec3Normalize(&vec, &vec);

			objPos += vec * m_info.moveAttenuation;

			CBillboard::SetPos(objPos);
		}
	}
}