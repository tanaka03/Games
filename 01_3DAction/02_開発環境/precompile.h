#ifndef PRECOMPILE_H_
#define PRECOMPILE_H_

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <assert.h>
#include <tchar.h> 
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")	//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

// �X�N���[���̕�
constexpr int SCREEN_WIDTH = 1280;
// �X�N���[���̍���
constexpr int SCREEN_HEIGHT = 720;

#endif // PRECOMPILE_H_