#ifndef _2DEFFECT_H_
#define _2DEFFECT_H_

#include "object2d.h"

class C2DEffect : public CObject2D
{
public:
	//--------------------------------------
	// �p�[�e�B�N�����̍\����
	//--------------------------------------
	struct SInfo
	{
		D3DXVECTOR3 pos;						// �ʒu
		D3DXVECTOR3 destPos;					// �ړI�̈ʒu
		D3DXVECTOR3 move;						// �ړ���
		D3DXCOLOR col;							// �F
		D3DXCOLOR destCol;						// �ړI�̐F
		std::vector<std::string> infoProperty;	// �v���p�e�B
		int destroyTime;						// �G�t�F�N�g����������
		float moveAttenuation;					// �ړ��̌�����
		float colAttenuation;					// �F�̌�����
		float scalingSpeed;						// �g�傷�鑬�x
	};

	explicit C2DEffect(int nPriority);
	~C2DEffect() override;

	static C2DEffect *Create(SInfo& info, std::string url, int nPriority);	// ��������

	HRESULT Init() override;												// ����������
	void Update() override;													// �X�V����
	void Draw() override;													// �`�揈��
	void Behavior(std::vector<std::string>& prop);							// �p�[�e�B�N���̋���

	//�Z�b�^�[
	void SetInfo(SInfo& info) { m_info = info; }
	void SetPath(std::string path) { m_path = path; }

private:
	SInfo m_info;						// �p�[�e�B�N���̏��
	std::string m_path;					// �e�N�X�`���̃p�X
	int m_nTime;						// ����
};
#endif