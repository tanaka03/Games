//=============================================================================
// Shader.h
//=============================================================================
#ifndef _SHADER_H_
#define _SHADER_H_

// �V�F�[�_�[�̍\���̂��`
struct VERTEX_SHADER
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`��
};
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_SHADER(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

class CShader
{
public:
	CShader();
	~CShader();

	virtual HRESULT Load() = 0;
	virtual void Begin() = 0;
	virtual void End();
	virtual void BeginPass(UINT pass)					{ if (m_pEffect == nullptr) return; else m_pEffect->BeginPass(pass); }
	virtual void CommitChanges()						{ if (m_pEffect == nullptr) return; else m_pEffect->CommitChanges(); }
	virtual void EndPass()								{ if (m_pEffect == nullptr) return; else m_pEffect->EndPass(); }
	virtual void SetTechnique(std::string tech)			{ if (m_pEffect == nullptr) return; else m_pEffect->SetTechnique(tech.c_str()); }
	virtual bool isOK()									{ if (m_pEffect == nullptr) return false; else return true; }

	LPD3DXEFFECT GetEffect() { return m_pEffect; }

protected:
	LPD3DXEFFECT m_pEffect;

private:
};

#endif