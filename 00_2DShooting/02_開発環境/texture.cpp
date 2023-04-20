//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "texture.h"
#include "renderer.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const char* CTexture::s_FileName[] =
{// �e�N�X�`���̃p�X
	"data/TEXTURE/BULLET/flare.png",			// �e�P
	"data/TEXTURE/BULLET/BigBullet.png",		// �e�Q
	"data/TEXTURE/BULLET/square.png",			// �e�R
	"data/TEXTURE/BULLET/bulletRed.png",		// �e�S
	"data/TEXTURE/Player.png",					// �v���C���[
	"data/TEXTURE/funnel.png",					// �t�@���l��
	"data/TEXTURE/funnel2.png",					// �t�@���l���Q
	"data/TEXTURE/explosion000.png",			// ����
	"data/TEXTURE/ENEMY/choco.png",				// �G�P
	"data/TEXTURE/ENEMY/bird.png",				// �G�Q
	"data/TEXTURE/ENEMY/Ghost.png",				// �G�R
	"data/TEXTURE/ENEMY/FireFairy.png",			// �G�S
	"data/TEXTURE/ENEMY/AquaFairy.png",			// �G�T
	"data/TEXTURE/ENEMY/Girl.png",				// �G�U
	"data/TEXTURE/ITEM/scoreItem.png",			// �X�R�A�A�C�e���P
	"data/TEXTURE/ITEM/scoreItemB.png",			// �X�R�A�A�C�e���Q
	"data/TEXTURE/ITEM/recovery.png",			// �񕜃A�C�e���Q
	"data/TEXTURE/ITEM/magnet.png",				// �A�r���e�B�A�C�e��
	"data/TEXTURE/ITEM/orb.png",				// ���@�����A�C�e��
	"data/TEXTURE/UI/number000.png",			// �X�R�A
	"data/TEXTURE/EFFECT/CircleA.png",			// �A�r���e�B�P
	"data/TEXTURE/EFFECT/bright.png",			// �G�t�F�N�g�P
	"data/TEXTURE/EFFECT/bright2.png",			// �G�t�F�N�g�Q
	"data/TEXTURE/EFFECT/bright3.png",			// �G�t�F�N�g�R
	"data/TEXTURE/EFFECT/Aster.png",			// �G�t�F�N�g�S
	"data/TEXTURE/EFFECT/heart.png",			// �n�[�g�G�t�F�N�g
	"data/TEXTURE/EFFECT/biribiri.png",			// �r���r���G�t�F�N�g
	"data/TEXTURE/EFFECT/ring.png",				// �փG�t�F�N�g
	"data/TEXTURE/EFFECT/MagicCircleB.png",		// ���@�w�G�t�F�N�g�P
	"data/TEXTURE/EFFECT/MagicCircle.png",		// ���@�w�G�t�F�N�g�Q
	"data/TEXTURE/EFFECT/pipo-particle.png",	// �p�[�e�B�N���P
	"data/TEXTURE/EFFECT/pipo-particle2.png",	// �p�[�e�B�N���Q
	"data/TEXTURE/EFFECT/pipo-particle3.png",	// �p�[�e�B�N���R
	"data/TEXTURE/FRAME/DamageFrame.png",		// �t���[���G�t�F�N�g�P
	"data/TEXTURE/UI/Gauge.png",				// �Q�[�W
	"data/TEXTURE/UI/GaugeFrame.png",			// �Q�[�W�t���[��
	"data/TEXTURE/UI/fragment.png",				// ����
	"data/TEXTURE/BG/BG_ocean.jpg",				// �w�i
	"data/TEXTURE/BG/BG_Glass.jpg",				// �w�i
	"data/TEXTURE/BG/BG_cloud.png",				// �w�i
	"data/TEXTURE/BG/BG_Sky2.jpg",				// �w�i
	"data/TEXTURE/BG/BG_Bright.png",			// �w�i
	"data/TEXTURE/BG/BG_laceframeA.png",		// �w�i
	"data/TEXTURE/BG/BG_ScrollA.png",			// �w�i
	"data/TEXTURE/BG/BG_Sky.png",				// �^�C�g���w�i
	"data/TEXTURE/TUTORIAL/tutorial1.png",		// �`���[�g���A��
	"data/TEXTURE/TUTORIAL/tutorial2.png",		// �`���[�g���A��
	"data/TEXTURE/TUTORIAL/tutorial3.png",		// �`���[�g���A��
	"data/TEXTURE/TUTORIAL/tutorial4.png",		// �`���[�g���A��
	"data/TEXTURE/TUTORIAL/tutorial5.png",		// �`���[�g���A��
	"data/TEXTURE/TUTORIAL/tutorial6.png",		// �`���[�g���A��
	"data/TEXTURE/UI/title.png",				// �^�C�g�����S
	"data/TEXTURE/UI/PressEnter.png",			// �G���^�[����
	"data/TEXTURE/UI/Start.png",				// �X�^�[�g�{�^��
	"data/TEXTURE/UI/Tutorial.png",				// �`���[�g���A���{�^��
	"data/TEXTURE/UI/Quit.png",					// �I���{�^��
	"data/TEXTURE/UI/rank.png",					// �����N
	"data/TEXTURE/UI/nowScore.png",				// ����̃X�R�A
	"data/TEXTURE/UI/new.png",					// NEW
	"data/TEXTURE/UI/HP.png",					// HP
	"data/TEXTURE/UI/MP.png"					// MP
};
static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::TEXTURE_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture() :
	s_pTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// �e�N�X�`���̓ǂݍ��݂�����Ă���
			continue;
		}

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::ReleaseAll(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// �e�N�X�`���̉��
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Release(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != NULL)
	{// �e�N�X�`���̉��
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = NULL;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	// �ǂݍ���
	Load(inTexture);

	return s_pTexture[inTexture];
}
