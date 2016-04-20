#pragma once

#include <Windows.h>

enum MethodResult {
	RE_INFINITE = -2,
	RE_INVALID = -1,
	RE_OK = 1,
	RE_FAIL = 0,
};

enum LightType {
	LIGHT_POINT = 1,	//点光源
	LIGHT_DIRECTIONAL = 2,	//环境光
	LIGHT_SPOT = 3	//聚光灯
};

#define PERCENT_OF(a,b) (int)(a * b)

//键盘按键数组总数
static const int keySize = 256;

enum FVFType {
	MY_FVF_GUI = 2,
	MY_FVF_MV = 3,
};

enum ControlType {
	GAME_GUI_STATICTEXT=1,
	GAME_GUI_BUTTON,
	GAME_GUI_BACKDROP
};

//鼠标状态
enum MouseState {
	MOUSE_BUTTON_UP=1,
	MOUSE_BUTTON_OVER,
	MOUSE_BUTTON_DOWN
};

enum MouseButton {
	MOUSE_LEFT_BUTTON=0,	//鼠标左键
	MOUSE_RIGHT_BUTTON,	//鼠标右键
};

#define WinHWND HWND

typedef long VertexType;

enum PrimType
{
	NULL_TYPE,
	POINT_LIST,
	TRIANGLE_LIST,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
	LINE_LIST,
	LINE_STRIP
};

enum RenderState
{
	CULL_NONE,
	CULL_CW,
	CULL_CCW,
	DEPTH_NONE,
	DEPTH_READONLY,
	DEPTH_READWRITE,
	SHADE_POINTS,
	SHADE_SOLIDTRI,
	SHADE_WIRETR,
	SHADE_WIREPOLY,
	TRANSPARENCY_NONE,
	TRANSPARENCY_ENABLE
};

enum TransState
{
	TRANS_ZERO = 1,
	TRANS_ONE,
	TRANS_SRCCOLOR,
	TRANS_INVSRCCOLOR,
	TRANS_SRCALPHA,
	TRANS_INVSRCALPHA,
	TRANS_DSTALPHA,
	TRANS_INVDSTALPHA,
	TRANS_DSTCOLOR,
	TRANS_INVDSTCOLOR,
	TRANS_SRCALPHASAT,
	TRANS_BOTHSRCALPHA,
	TRANS_INVBOTHSRCALPHA,
	TRANS_BLENDFACTOR,
	TRANS_INVBLENDFACTOR,
};

enum TextureState
{
	MIN_FILTER,
	MAG_FILTER,
	MIP_FILTER
};

enum FilterType
{
	POINT_TYPE,
	LINEAR_TYPE,
	ANISOTROPIC_TYPE
};

enum UGP_MS_TYPE
{
	UGP_MS_NONE,
	UGP_MS_SAMPLES_2,
	UGP_MS_SAMPLES_4,
	UGP_MS_SAMPLES_8,
	UGP_MS_SAMPLES_16
};

enum UGP_FOG_TYPE
{
	UGP_VERTEX_FOG,
	UGP_PIXEL_FOG
};

struct myGUIVertex
{
	float x, y, z, rhw;
	unsigned long color;
	float tu, tv;
};

struct myModelVertex
{
	float x, y, z;
	float nx, ny, nz;
	unsigned long color;
	float tu, tv;
};

struct mySkyBoxVertex
{
	float	x, y, z;
	float	u, v;
};
#define D3DFVF_SKYBOX D3DFVF_XYZ|D3DFVF_TEX1

#define UGPCOLOR_ARGB(a,r,g,b) ((unsigned long)((((a)&0xff)<<24)|\
							   (((r)&0xff)<<16)|(((g)&0xff)<<8)|\
							   ((b)&0xff)))
