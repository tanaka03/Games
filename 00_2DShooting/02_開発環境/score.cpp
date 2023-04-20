#include "main.h"
#include "application.h"
#include "object2d.h"
#include "score.h"
#include <string>
using namespace std;

#define MAX_SCORE	(8)

//����������������������������������������
//�ÓI�����o�ϐ��錾
//����������������������������������������
int CScore::m_nScore = 0;
int CScore::m_nNum = 0;
int CScore::m_nAll = 0;
int CScore::m_aPosTexU[MAX_SCORE] = {};
int CScore::m_aRankingScore[10] = {};

//����������������������������������������
//�X�R�A�̃R���X�g���N�^
//����������������������������������������
CScore::CScore()
{
	m_nScore = 0;
	m_nCntAll = 0;
}

//����������������������������������������
//�X�R�A�̃f�X�g���N�^
//����������������������������������������
CScore::~CScore()
{

}

//����������������������������������������
//�X�R�A�̐���
//����������������������������������������
CScore * CScore::Create(D3DXVECTOR3 pos)
{
	CScore *pScore = nullptr;

	for (int i = 0; i < MAX_SCORE; i++)
	{
		pScore = new CScore;

		//�k���`�F�b�N
		if (pScore != nullptr)
		{
			// �|���S���̏���������
			pScore->Init();
			pScore->SetPos(D3DXVECTOR3(pos.x + (i * 45.0f), pos.y, 0.0f));
		}
	}

	return pScore;
}

CScore * CScore::Create(D3DXVECTOR3 pos, int score)
{
	CScore *pScore = nullptr;

	for (int i = 0; i < MAX_SCORE; i++)
	{
		pScore = new CScore;

		//�k���`�F�b�N
		if (pScore != nullptr)
		{
			// �|���S���̏���������
			pScore->Init();
			pScore->SetUseRank(true);
			pScore->SetPos(D3DXVECTOR3(pos.x + (i * 45.0f), pos.y, 0.0f));
			pScore->SetResult(score, m_nAll);
		}
	}

	m_nAll++;
	return pScore;
}

//����������������������������������������
//�X�R�A�̏���������
//����������������������������������������
HRESULT CScore::Init()
{
	CObject2D::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CObject2D::SetScale(25.0f, 30.0f);
	CObject2D::Init();
	CObject2D::SetTexture(CTexture::TEXTURE_NUMBER);
	SetIdx(m_nAll);

	VERTEX_2D*pVtx;        //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//����������������������������������������
//�X�R�A�̏I������
//����������������������������������������
void CScore::Uninit()
{
	CObject2D::Uninit();
	CObject2D::Release();
}

//����������������������������������������
//�X�R�A�̍X�V����
//����������������������������������������
void CScore::Update()
{
	CObject2D::Update();
	if (m_nScore < 0)
	{
		m_nScore = 0;
	}

	if (m_nAll <= 10)
	{
		m_nAll = 0;
	}

	if (GetUseRank())
	{
		SetRank();
	}

	else
	{
		Set(m_nScore);
	}
}

//����������������������������������������
//�X�R�A�̕`�揈��
//����������������������������������������
void CScore::Draw()
{
	CObject2D::Draw();
}

//����������������������������������������
//�X�R�A�̐ݒ菈��
//����������������������������������������
void CScore::Set(int nScore)
{
	m_aPosTexU[8];	//�e���̐������i�[

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int ValueA = StrErase("100000000", m_nNum);
	int ValueB = StrErase("10000000", m_nNum);

	m_aPosTexU[m_nNum] = m_nScore % ValueA / ValueB;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + m_aPosTexU[m_nNum] * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + m_aPosTexU[m_nNum] * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_aPosTexU[m_nNum] * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + m_aPosTexU[m_nNum] * 0.1f, 1.0f);

	m_nNum++;
	if (m_nNum >= MAX_SCORE)
	{
		m_nNum = 0;
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

void CScore::SetRank()
{
	m_aPosTexU[8];	//�e���̐������i�[

	VERTEX_2D*pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int ValueA = StrErase("100000000", m_nNum);
	int ValueB = StrErase("10000000", m_nNum);

	int idx = GetIdx();
	m_aPosTexU[m_nNum] = m_aRankingScore[GetIdx()] % ValueA / ValueB;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + m_aPosTexU[m_nNum] * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + m_aPosTexU[m_nNum] * 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + m_aPosTexU[m_nNum] * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + m_aPosTexU[m_nNum] * 0.1f, 1.0f);

	m_nNum++;
	if (m_nNum >= MAX_SCORE)
	{
		m_nNum = 0;
	}

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//����������������������������������������
//�X�R�A�̉��Z����
//����������������������������������������
void CScore::Add(int nValue)
{
	m_nScore += nValue;
}

//����������������������������������������
//���l�̕������int�^�ɂ��鏈��
//����������������������������������������
int CScore::StrErase(char* Str, int Num)
{
	string str(Str);

	for (int i = 0; i < Num ; i++)
	{
		str.pop_back();
	}

	int DestNum = stoi(str);

	return DestNum;
}