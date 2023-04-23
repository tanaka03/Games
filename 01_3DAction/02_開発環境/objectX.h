#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"

class CObjectX : public CObject
{
public:
	explicit CObjectX(int nPriority = CObject::PRIORITY_THIRD);
	~CObjectX() override;

	HRESULT Init() override;											// ����������
	void Uninit() override;												// �I������
	void Update() override;												// �X�V����
	void Draw() override;												// �`�揈��
	void Draw(D3DXMATRIX mtxParent);									// �`�揈��
	void VtxUpdate() {};												// ���_���W�X�V����
	void Destroy() override { m_bRelease = true; }
	void CalculationVtx();												// ���_�ő召�l�̌v�Z����

	// Setter
	void SetPos(D3DXVECTOR3 pos) override;								// ���W�ݒ菈��
	void SetSize(D3DXVECTOR3 size);										// �T�C�Y�ݒ菈��
	void SetMove(D3DXVECTOR3 move);										// �ړ��ʐݒ菈��
	void SetCol(D3DXCOLOR col);											// �F�ݒ菈��
	void SetRot(D3DXVECTOR3 rot);										// �����ݒ菈��
	void SetMaxVtx(D3DXVECTOR3 Maxvtx);									// ���_�ő�l�ݒ菈��
	void SetMinVtx(D3DXVECTOR3 Minvtx);									// ���_�ŏ��l�ݒ菈��
	void SetParent(CObjectX* inParent) { m_pParent = inParent; }		// �e���f���̏��
	void SetCollisionFlag(bool inFlag) { m_isCollision = inFlag; }

	// Getter
	D3DXVECTOR3 GetPos(void) override { return m_pos; }					// ���W�擾����
	D3DXVECTOR3 GetSize(void) { return m_size; }						// �T�C�Y�擾����
	D3DXVECTOR3 GetMove(void) { return m_move; }						// �ړ��ʎ擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }							// �����擾����
	D3DXCOLOR GetCol(void) { return m_col; }							// �F�擾����
	D3DXVECTOR3 GetMaxVtx(void) { return m_MaxVtx; }					// ���_�ő�l�擾����
	D3DXVECTOR3 GetMinVtx(void) { return m_MinVtx; }					// ���_�ŏ��l�擾����
	CObjectX* GetParent(void) { return m_pParent; }						// �e���f���̏��
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	LPD3DXMESH GetMesh() { return m_pMesh; }
	LPD3DXBUFFER GetBuffMat() { return m_pBuffMat; }
	DWORD GetNumMat() { return m_NumMat; }
	bool IsCollision() { return m_isCollision; }
	bool GetDestroy() override { return m_bRelease; }

	static CObjectX *Create(D3DXVECTOR3 pos, int nPriority);			// ��������
	void LoadModel(const char *aFileName);								// ���f���̓ǂݍ��ݏ���

	// Collision
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pSize);													// �����蔻�� (���E, ��, ��O)
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *inMaxVtx, D3DXVECTOR3 *inMinVtx);							// �����蔻�� (���E, ��, ��O)
	bool UpCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pSize, D3DXVECTOR3 *pMove);								// �����蔻�� (�㑤)
	bool UpCollision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *inMaxVtx, D3DXVECTOR3 *inMinVtx, D3DXVECTOR3 *pMove);	// �����蔻�� (�㑤)

private:
	D3DXVECTOR3 m_pos;					// ���W
	D3DXVECTOR3 m_rot;					// �p�x
	D3DXVECTOR3 m_size;					// ���W
	D3DXVECTOR3 m_move;					// �p�x
	D3DXVECTOR3 m_MinVtx;				// ���f���̒��_�ŏ��l
	D3DXVECTOR3 m_MaxVtx;				// ���f���̒��_�ő�l
	D3DXCOLOR m_col;					// �F
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	LPD3DXMESH m_pMesh;					// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;			// �}�e���A�����ւ̃|�C���^
	DWORD m_NumMat;						// �}�e���A�����̐�

	CObjectX *m_pParent;				// �e���f���̏��
	bool m_isCollision;					// �����蔻�肪�K�v��

	bool m_bRelease;
};
#endif