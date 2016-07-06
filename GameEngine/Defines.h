#pragma once

#include <Windows.h>
//��������ֵ
enum MethodResult {
	RE_INFINITE = -2,
	RE_INVALID = -1,
	RE_OK = 1,
	RE_FAIL = 0,
};
//��Դ����
enum LightType {
	LIGHT_POINT = 1,	//���Դ
	LIGHT_DIRECTIONAL = 2,	//������
	LIGHT_SPOT = 3	//�۹��
};
//���ڰٷֱȷ���GUI
#define PERCENT_OF(a,b) (int)(a * b)

//���̰�����������
static const int keySize = 256;
//FVF����
enum FVFType {
	MY_FVF_GUI = 2,
	MY_FVF_MV = 3,
};
//�ؼ�����
enum ControlType {
	GAME_GUI_STATICTEXT=1,
	GAME_GUI_BUTTON,
	GAME_GUI_BACKDROP
};

//���״̬
enum MouseState {
	MOUSE_BUTTON_UP=1,
	MOUSE_BUTTON_OVER,
	MOUSE_BUTTON_DOWN
};

enum MouseButton {
	MOUSE_LEFT_BUTTON=0,	//������
	MOUSE_RIGHT_BUTTON,	//����Ҽ�
};

#define WinHWND HWND

typedef long VertexType;
//��Ⱦͼ������
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
//��Ⱦ״̬
enum RenderState
{
	CULL_NONE,	//�޲ü�
	CULL_CW,	//˳ʱ��ü�
	CULL_CCW,	//��ʱ��ü�
	DEPTH_NONE,	//����Ȼ���
	DEPTH_READONLY,	//ֻ����Ȼ���
	DEPTH_READWRITE,	//��д��Ȼ���
	SHADE_POINTS,	//����ɫ
	SHADE_SOLIDTRI,	//ʵ����������ɫ
	SHADE_WIRETR,	//�������߿���ɫ
	SHADE_WIREPOLY,	//������߿���ɫ
	TRANSPARENCY_NONE,	//��͸����
	TRANSPARENCY_ENABLE	//ʹ��͸����
};
//͸��״̬
enum TransState
{
	TRANS_ZERO = 1,	//�ں�����
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
//����״̬
enum TextureState
{
	MIN_FILTER,	//��С������
	MAG_FILTER,	//�Ŵ�
	MIP_FILTER	//�༶����
};
//����������
enum FilterType
{
	POINT_TYPE,	//�������
	LINEAR_TYPE,	//��
	ANISOTROPIC_TYPE	//����
};
//�����
enum MultiSampleType
{
	MY_MS_NONE,
	MY_MS_SAMPLES_2,
	MY_MS_SAMPLES_4,
	MY_MS_SAMPLES_8,
	MY_MS_SAMPLES_16
};
//��Ч����
enum FogType
{
	FOG_VERTEX,	//������
	FOG_PIXEL	//������
};
//GUI����ṹ
struct myGUIVertex
{
	float x, y, z, rhw;
	unsigned long color;
	float tu, tv;
};
//ģ�Ͷ���ṹ
struct myModelVertex
{
	float x, y, z;
	float nx, ny, nz;
	unsigned long color;
	float tu, tv;
};
//��պж���ṹ
struct mySkyBoxVertex
{
	float	x, y, z;
	float	u, v;
};
#define D3DFVF_SKYBOX D3DFVF_XYZ|D3DFVF_TEX1

#define MYCOLOR_ARGB(a,r,g,b) ((unsigned long)((((a)&0xff)<<24)|\
							   (((r)&0xff)<<16)|(((g)&0xff)<<8)|\
							   ((b)&0xff)))
//�жϺ����Ƿ񷵻سɹ�
#ifndef HR
#define HR(x)    { hr = x; if( FAILED(hr) ) { return hr; } }
#endif
//ɾ������ָ��
#ifndef SAFE_DELETE					
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    
//�ͷŶ���ָ��
#ifndef SAFE_RELEASE			
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif
//ɾ������
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif 
