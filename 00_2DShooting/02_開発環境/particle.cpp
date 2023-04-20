// ����������������������������������������
// effect.cpp
// ����������������������������������������
#include "particle.h"
#include "main.h"

#include "utility.h"
#include "renderer.h"
#include "application.h"
#include <assert.h>

//==================================================
// �ÓI�����o�[�ϐ�
//==================================================

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CParticle::CParticle() : 
	m_data({})
{

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CParticle::~CParticle()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CParticle::Init()
{
	CObject2D::Init();
	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CParticle::Uninit()
{
	CObject2D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CParticle::Update()
{
	CObject2D::Update();

	/* ���g�p���Ă���Ȃ火 */

	// �G�t�F�N�g�̈ړ�
	auto m_objpos = GetPos();
	m_objpos += m_data.move;

	// ����
	m_data.nLife--;							// �̗͂̌���
	m_data.move.y += m_data.fWeight;			// �d��
	m_data.move *= m_data.fAttenuation;			// �ړ��ʂ̐���
	m_data.fWeight += m_data.fWeightTransition;	// �d���̐���
	m_data.move.x -= 0.1f;
	D3DXCOLOR myColor = CObject2D::GetCol();
	if (m_data.color.bColTransition)
	{// �F�̐���
		if (m_data.color.nEndTime >= m_data.color.nCntTransitionTime)
		{
			m_data.color.nCntTransitionTime++;
			myColor.r += m_data.color.colTransition.r;
			myColor.g += m_data.color.colTransition.g;
			myColor.b += m_data.color.colTransition.b;
			//myColor.a += m_data.color.colTransition.a;
		}
	}
	myColor.a -= 1.0f / m_data.nMaxLife;

	SetPos(m_objpos);
	SetCol(D3DXCOLOR(myColor.r, myColor.g, myColor.b, myColor.a));
	SetScale(m_data.fWidth, m_data.fHeight);

	if (m_data.nLife <= 0)
	{// �G�t�F�N�g�̎���
		Release();
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CParticle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	switch (m_data.alphaBlend)
	{
	case TYPE_NONE:	// ��Z
		break;

	case TYPE_ADD:	// ���Z
		// ���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		break;

	case TYPE_SUB:	// ���Z
		// ���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	default:
		assert(false);
		break;
	}

	CObject2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	// �e�N�X�`���������p���Ȃ�
	pDevice->SetTexture(0, NULL);
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CParticle* CParticle::Create(const Info& inParticle, const D3DXVECTOR3& inPos)
{
	CParticle* particle = nullptr;
	if (particle == nullptr)
	{
		particle = new CParticle;
		particle->Init();
		particle->SetScale(particle->m_data.fWidth, particle->m_data.fHeight);
		particle->SetPos(inPos);
		particle->m_data = inParticle;
		particle->SetTexture(CTexture::TEXTURE_EFFECTRING);
		particle->SetCol(D3DXCOLOR(particle->m_data.color.colBigin.r, particle->m_data.color.colBigin.g, particle->m_data.color.colBigin.b, particle->m_data.color.colBigin.a));
		
		particle->CObject2D::SetTexture(CTexture::TEXTURE_EFFECT2);

		return particle;
	}
	return nullptr;
}

//--------------------------------------------------
// �e�N�X�`���̓Ǎ���
//--------------------------------------------------
void CParticle::LoadTex()
{

}

//--------------------------------------------------
// float �� DWORD �ɕϊ�
//--------------------------------------------------
DWORD CParticle::FloattoDword(float fVal)
{
	return *((DWORD*)&fVal);
}
