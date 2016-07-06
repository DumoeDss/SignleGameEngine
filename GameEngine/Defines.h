#pragma once

#include <Windows.h>
//方法返回值
enum MethodResult {
	RE_INFINITE = -2,
	RE_INVALID = -1,
	RE_OK = 1,
	RE_FAIL = 0,
};
//光源类型
enum LightType {
	LIGHT_POINT = 1,	//点光源
	LIGHT_DIRECTIONAL = 2,	//环境光
	LIGHT_SPOT = 3	//聚光灯
};
//用于百分比放置GUI
#define PERCENT_OF(a,b) (int)(a * b)

//键盘按键数组总数
static const int keySize = 256;
//FVF类型
enum FVFType {
	MY_FVF_GUI = 2,
	MY_FVF_MV = 3,
};
//控件类型
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
//渲染图形类型
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
//渲染状态
enum RenderState
{
	CULL_NONE,	//无裁剪
	CULL_CW,	//顺时针裁剪
	CULL_CCW,	//逆时针裁剪
	DEPTH_NONE,	//无深度缓存
	DEPTH_READONLY,	//只读深度缓存
	DEPTH_READWRITE,	//读写深度缓存
	SHADE_POINTS,	//点着色
	SHADE_SOLIDTRI,	//实心三角形着色
	SHADE_WIRETR,	//三角形线框着色
	SHADE_WIREPOLY,	//多边形线框着色
	TRANSPARENCY_NONE,	//无透明度
	TRANSPARENCY_ENABLE	//使用透明度
};
//透明状态
enum TransState
{
	TRANS_ZERO = 1,	//融合因子
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
//纹理状态
enum TextureState
{
	MIN_FILTER,	//缩小过滤器
	MAG_FILTER,	//放大
	MIP_FILTER	//多级渐变
};
//过滤器类型
enum FilterType
{
	POINT_TYPE,	//点过滤器
	LINEAR_TYPE,	//线
	ANISOTROPIC_TYPE	//纹理
};
//多采样
enum MultiSampleType
{
	MY_MS_NONE,
	MY_MS_SAMPLES_2,
	MY_MS_SAMPLES_4,
	MY_MS_SAMPLES_8,
	MY_MS_SAMPLES_16
};
//雾效类型
enum FogType
{
	FOG_VERTEX,	//顶点雾
	FOG_PIXEL	//像素雾
};
//GUI顶点结构
struct myGUIVertex
{
	float x, y, z, rhw;
	unsigned long color;
	float tu, tv;
};
//模型顶点结构
struct myModelVertex
{
	float x, y, z;
	float nx, ny, nz;
	unsigned long color;
	float tu, tv;
};
//天空盒顶点结构
struct mySkyBoxVertex
{
	float	x, y, z;
	float	u, v;
};
#define D3DFVF_SKYBOX D3DFVF_XYZ|D3DFVF_TEX1

#define MYCOLOR_ARGB(a,r,g,b) ((unsigned long)((((a)&0xff)<<24)|\
							   (((r)&0xff)<<16)|(((g)&0xff)<<8)|\
							   ((b)&0xff)))
//判断函数是否返回成功
#ifndef HR
#define HR(x)    { hr = x; if( FAILED(hr) ) { return hr; } }
#endif
//删除对象指针
#ifndef SAFE_DELETE					
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    
//释放对象指针
#ifndef SAFE_RELEASE			
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif
//删除数组
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif 
