//**************************************************
//
// sound.h
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _SOUND_H_	//このマクロ定義がされてなかったら
#define _SOUND_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include <xaudio2.h>

//==================================================
// 定義
//==================================================
class CSound
{
	/* ↓定義↓ */
public:
	enum ELabel
	{
		LABEL_NONE = -1,
		LABEL_SE_BEAM = 0,
		LABEL_SE_PUNCH,
		LABEL_SE_STRIKE,
		LABEL_SE_KICK,
		LABEL_SE_SLOTSET,
		LABEL_SE_ROULETTE,
		LABEL_SE_STATUSUP,
		LABEL_BGM_STAGE1,
		LABEL_MAX,
	};

	struct SParam
	{
		char *pFileName;	// ファイル名
		int loop;			// ループ
	};

	static const SParam PARAM[];	// パラメータの情報

public:
	CSound();	// デフォルトコンストラクタ
	~CSound();	// デストラクタ

public:
	HRESULT Init(HWND hWnd);
	void Uninit();
	HRESULT Play(ELabel sound);
	void Stop(ELabel label);
	void Stop();

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);	// チャンクのチェック
	HRESULT LoadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// チャンクデータの読み込み

																									/* ↓メンバ変数↓ */
private:
	IXAudio2* m_pXAudio2;							// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;		// マスターボイス
	IXAudio2SourceVoice* m_pSourceVoice[LABEL_MAX];	// ソースボイス
	BYTE* m_pDataAudio[LABEL_MAX];					// オーディオデータ
	DWORD m_sizeAudio[LABEL_MAX];					// オーディオデータサイズ
};

#endif // !_SOUND_H_
