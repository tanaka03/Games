//����������������������������������������
//Billboard.h
//����������������������������������������
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "object.h"
#include "texture.h"

class CBillboard : public CObject
{
public:
	//--------------------------------------
	// �u�����h�^�C�v�̗�
	//--------------------------------------
	enum EBlend
	{
		BLEND_NONE = 0,
		BLEND_ADDITIVE,
		BLEND_SUBSTRUCT,
		BLEND_MAX
	};

	explicit CBillboard(int nPriority = CObject::PRIORITY_THIRD);
	~CBillboard() override;

	static CBillboard* Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, int priority);							// ��������

	HRESULT Init() override;																				// ����������
	void Uninit() override;																					// �I������
	void Update() override;																					// �X�V����
	void Draw() override;																					// �`�揈��
	void BindTexture(std::string inPath);																	// �e�N�X�`�����o�C���h
	void SetUV(float Xtop, float Xbottom, float Ytop, float Ybottom);										// UV���W�̐ݒ�
	void SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop);		// �A�j���[�V�����̐ݒ�
	void Destroy() override { m_bRelease = true; }															// ���S�t���O�̐ݒ�
	void AlphaTest() { m_bIsAlphaTest = true; }																// �e�N�X�`���̃A���t�@�l�̃e�X�g���J�n
	void Rotate(float rot) { m_bIsRotate = true, m_destRotate = rot; }										// ��]�̐ݒ�

	//�Z�b�^�[
	void SetPos(D3DXVECTOR3 pos) override { m_objpos = pos; }												// �ʒu�̐ݒ�
	void SetMove(D3DXVECTOR3 move) { m_move = move; }														// �ړ��ʂ̐ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }															// �����̐ݒ�
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }													// �傫���̐ݒ�
	void SetCol(D3DXCOLOR col) { m_col = col; }																// �F�̐ݒ�
	void SetBlend(EBlend blend) { m_blend = blend; }														// �u�����h�^�C�v�̐ݒ�
	void SetZBuff(_D3DCMPFUNC func) { m_Zfunc = func; }														// Z�o�b�t�@�e�X�g�̐ݒ�
	void SetMtxWorld(D3DXMATRIX mtx) { m_mtxWorld = mtx; }

	//�Q�b�^�[
	D3DXVECTOR3 GetPos() override { return m_objpos; }														// �ʒu�̎擾
	D3DXVECTOR3 GetMove() { return m_move; }																// �ړ��ʂ̎擾
	D3DXVECTOR3 GetRot() { return m_rot;}																	// �����̎擾
	D3DXVECTOR3 GetScale() { return m_scale; }																// �傫���̎擾
	D3DXCOLOR GetCol() { return m_col; }																	// �F�̎擾
	EBlend GetBlend() { return m_blend; }																	// �u�����h�^�C�v�̎擾
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }
	LPDIRECT3DTEXTURE9 GetMyTexture() { return m_pTexture; }
	float GetWidth() { return m_Width; }																	// ���̎擾
	float GetHeight() { return m_Height; }																	// �����̎擾
	bool GetDestroy() override { return m_bRelease; }														// ���S���Ă��邩�ǂ���

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`��
	D3DXVECTOR3 m_objpos;					// �ʒu
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_scale;					// �傫��
	D3DXCOLOR m_col;						// �F
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	_D3DCMPFUNC m_Zfunc;					// Z�o�b�t�@�̃^�C�v
	EBlend m_blend;							// �u�����h�^�C�v
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
	float m_destRotate;						// ��]�̑���
	bool m_bAnimation;						// �A�j���[�V���������邩�ǂ���
	bool m_bLoop;							// �A�j���[�V���������[�v���邩�ǂ���
	bool m_bIsRotate;						// ��]�����邩�ǂ���
	bool m_bIsAlphaTest;					// �A���t�@�e�X�g�����邩�ǂ���
	bool m_bRelease;						// ���S�t���O
};

#endif