//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CTexture
{
public: /* ��` */
	enum TEXTURE
	{
		TEXTURE_BULLET = 0,
		TEXTURE_BIGBULLET,
		TEXTURE_SQUAREBULLET,
		TEXTURE_REDBULLET,
		TEXTURE_PLAYER,
		TEXTURE_FUNNEL,
		TEXTURE_FUNNEL2,
		TEXTURE_EXPLOSION,
		TEXTURE_ENEMYDOG,
		TEXTURE_ENEMYBIRD,
		TEXTURE_ENEMYGHOST,
		TEXTURE_ENEMYFAIRYFIRE,
		TEXTURE_ENEMYFAIRYAQUA,
		TEXTURE_ENEMYGIRL,
		TEXTURE_SCOREITEM1,
		TEXTURE_SCOREITEM2,
		TEXTURE_RECOVERYITEM,
		TEXTURE_MAGNET,
		TEXTURE_ORB,
		TEXTURE_NUMBER,
		TEXTURE_ABILITY1,
		TEXTURE_EFFECT1,
		TEXTURE_EFFECT2,
		TEXTURE_EFFECT3,
		TEXTURE_EFFECT4,
		TEXTURE_EFFECTHEART,
		TEXTURE_EFFECTSPARK,
		TEXTURE_EFFECTRING,
		TEXTURE_EFFECTMAGIC1,
		TEXTURE_EFFECTMAGIC2,
		TEXTURE_PIPO_EFFECT,
		TEXTURE_PIPO_EFFECT2,
		TEXTURE_PIPO_EFFECT3,
		TEXTURE_DAMAGEFRAME,
		TEXTURE_GAUGE,
		TEXTURE_GAUGEFRAME,
		TEXTURE_FRAGMENT,
		TEXTURE_BG,
		TEXTURE_BGGLASS,
		TEXTURE_BGCLOUD,
		TEXTURE_BGSKY,
		TEXTURE_BGBRIGHT,
		TEXTURE_BGLACEA,
		TEXTURE_BGLACEB,
		TEXTURE_BGTITLE,
		TEXTURE_TUTORIAL1,
		TEXTURE_TUTORIAL2,
		TEXTURE_TUTORIAL3,
		TEXTURE_TUTORIAL4,
		TEXTURE_TUTORIAL5,
		TEXTURE_TUTORIAL6,
		TEXTURE_TITLE,
		TEXTURE_PRESSENTER,
		TEXTURE_START,
		TEXTURE_TUTORIAL,
		TEXTURE_QUIT,
		TEXTURE_RANK,
		TEXTURE_NOWSCORE,
		TEXTURE_NEW,
		TEXTURE_HP,
		TEXTURE_MP,
		TEXTURE_MAX,
		TEXTURE_NONE,	// �g�p���Ȃ�
	};

	static const char* s_FileName[];	// �t�@�C���p�X

public:
	CTexture();		// �f�t�H���g�R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

public: /* �����o�֐� */
	void LoadAll();										// �S�Ă̓ǂݍ���
	void Load(TEXTURE inTexture);						// �w��̓ǂݍ���
	void ReleaseAll();									// �S�Ă̔j��
	void Release(TEXTURE inTexture);					// �w��̔j��
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// ���̎擾

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// �e�N�X�`���̏��
};

#endif // !_TEXTURE_H_
