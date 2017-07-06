#ifndef _CONST_H_
#define _CONST_H_

const int g_iWINCX = 800;
const int g_iWINCY = 600;

const int g_iTileCX = 48;
const int g_iTileCY = 48;

//const int g_iTileCX = 32;
//const int g_iTileCY = 32;

const int g_iTileCountX = 28;
const int g_iTileCountY = 18;

const float PI = 3.1415f;


//키 상태를 관리하기 위한 변수
const DWORD KEY_LEFT	= 0x00000001;
const DWORD KEY_RIGHT	= 0x00000002;
const DWORD KEY_UP		= 0x00000004;
const DWORD KEY_DOWN	= 0x00000008;
const DWORD KEY_SPACE	= 0x00000010;
const DWORD KEY_LBUTTON = 0x00000100;	//0x00000020;
const DWORD KEY_CRT = 0x00001000;


//플레이어 상태값.
const DWORD STATE_STAND  = 0x00000001;
const DWORD STATE_WALK	 = 0x00000002;
const DWORD STATE_ATTACK = 0x00000004;
const DWORD STATE_DEAD   = 0x00000008;
const DWORD STATE_JUMP   = 0x00000010;
const DWORD STATE_JUMP_DOWN	 = 0x00000100;
const DWORD STATE_ATTACK_DOWN	 = 0x00001000;
const DWORD STATE_SKILL	 = 0x00001010;
const DWORD STATE_NEUTRAL =0x00010000;
const DWORD STATE_LADDER =0x00100000;
const DWORD STATE_HIT =0x01000000;
const DWORD STATE_WAIT =0x01000001;
//const DWORD STATE_DEAD   = 0x00000100;

#endif