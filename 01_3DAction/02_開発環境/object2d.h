//����������������������������������������
//Object2D.h
//����������������������������������������
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "object.h"
#include "texture.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

// ���_�f�[�^
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

class CObject2D : public CObject
{
public:
	explicit CObject2D(int priority = CObject::PRIORITY_THIRD);
	~CObject2D() override;

	static CObject2D* Create(D3DXVECTOR3 pos, D3DXVECTOR2 scale, std::string tex, int priority, D3DXCOLOR col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));			// ��������

	HRESULT Init() override;																				// ����������
	void Uninit() override;																					// �I������
	void Update() override;																					// �X�V����
	void Draw() override;																					// �`�揈��
	void BindTexture(std::string inPath);																	// �e�N�X�`���̃o�C���h
	void SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom);										// UV���W�̐ݒ�
	void SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop);		// �A�j���[�V�����̐ݒ�
	bool SquareCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Length, float CollisionVal);			// �l�p����
	bool CircleCollision(D3DXVECTOR3 pos, D3DXVECTOR3 Destpos, float Radius, float CollisionVal);			// �۔���

	//�Z�b�^�[
	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }												// �ʒu�̐ݒ�
	void SetMove(D3DXVECTOR3 move) { m_move = move; }														// �ړ��ʂ̐ݒ�
	void SetCol(D3DXCOLOR col) { m_col = col; }																// �F�̐ݒ�
	void SetScale(D3DXVECTOR2 scale) { m_Width = scale.x, m_Height = scale.y; }								// �e�N�X�`���̑傫���̐ݒ�
	void SetRot(float rot) { m_rot = rot; }																	// �����̐ݒ�
	void SetTexture(LPDIRECT3DTEXTURE9 tex) { m_pTexture = tex; }
	void Destroy() override { m_bRelease = true; }															// ���S�t���O

	//�Q�b�^�[
	D3DXVECTOR3 GetPos() override { return m_objpos; }														// �ʒu���擾
	D3DXVECTOR3 GetMove() { return m_move; }																// �ړ��ʂ��擾
	D3DXVECTOR2 GetScale() { return D3DXVECTOR2(m_Width, m_Height); }										// �傫�����擾
	D3DXCOLOR GetCol() { return m_col; }																	// �F���擾
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }													// �e�N�X�`���̏����擾
	float GetWidth() { return m_Width; }																	// �����擾
	float GetHeight() { return m_Height; }																	// �������擾
	bool GetDestroy() override { return m_bRelease; }														// ���S���Ă��邩�ǂ���

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`��
	D3DXVECTOR3 m_objpos;					// �I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXCOLOR m_col;						// �F
	int m_nCounterAnim;						// �A�j���[�V�����J�E���^
	int m_nPatternAnim;						// �A�j���[�V�����p�^�[��
	int m_nCntY;							// Y���W�𓮂����ۂɎg�p����J�E���^
	int m_CounterAnim;						// �A�j���[�V�����J�E���^�[
	int m_PatternAnimX;						// X�̃p�^�[��
	int m_PatternAnimY;						// Y�̃p�^�[��
	int m_DivisionX;						// X������
	int m_DivisionY;						// Y������
	int m_DivisionMAX;						// �ő啪����
	int m_AnimationSpeed;					// �A�j���[�V�������鑬�x
	int m_AnimationSpdCnt;					// �A�j���[�V�����̃X�s�[�h�J�E���^�[
	int m_Timer;							// �^�C�}�[
	int m_CntTime;							// �e�N�X�`���A�j���[�V�����̃^�C�}�[
	float m_Width;							// ��
	float m_Height;							// ����
	float m_rot;							// ����
	bool m_bAnimation;						// �A�j���[�V���������邩�ǂ���
	bool m_bLoop;							// �A�j���[�V���������[�v���邩�ǂ���
	bool m_bRelease;						// ���S�t���O
};

#endif