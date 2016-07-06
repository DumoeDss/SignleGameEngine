#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include "Defines.h"

class MyTerrain
{
public:
	MyTerrain(
		IDirect3DDevice9* device,
		std::string heightmapFileName,
		int numVertsPerRow,
		int numVertsPerCol,
		int cellSpacing,
		float heightScale);

	~MyTerrain();

	int  getHeightmapEntry(int row, int col);
	void setHeightmapEntry(int row, int col, int value);

	float getHeight(float x, float z);
	//加载纹理贴图
	bool  loadTexture(std::string fileName);
	bool  genTexture(D3DXVECTOR3* directionToLight);
	//渲染地形
	bool  renderTerrain(D3DXMATRIX* world, bool drawTris);

private:
	IDirect3DDevice9*       m_device;
	IDirect3DTexture9*      m_texture;
	IDirect3DVertexBuffer9* m_vertexBuffer;
	IDirect3DIndexBuffer9*  m_indexBuffer;

	int m_numVertsPerRow;	//每行顶点数
	int m_numVertsPerCol;	//每列顶点数
	int m_cellSpacing;	//每个单元格中两个顶点之间距离

	int m_numCellsPerRow;	//每行单元格数
	int m_numCellsPerCol;	//每列单元格数
	int m_width;	//总宽度
	int m_depth;	//总深度
	int m_numVertices;	//顶点总数
	int m_numTriangles;	//三角形总数

	float m_heightScale;	//缩放系数

	std::vector<int> m_heightmap;	//存储高度数据

	bool  readRawFile(std::string fileName);	//读取高度图
	bool  computeVertices();
	bool  computeIndices();
	bool  lightTerrain(D3DXVECTOR3* directionToLight);
	float computeShade(int cellRow, int cellCol, D3DXVECTOR3* directionToLight);

	float Lerp(float a, float b, float t)	//插值函数
	{
		return a - (a*t) + (b*t);
	}

	struct TerrainVertex
	{
		TerrainVertex() {}
		TerrainVertex(float x, float y, float z, float u, float v)
		{
			m_x = x; m_y = y; m_z = z; m_u = u; m_v = v;
		}
		float m_x, m_y, m_z;
		float m_u, m_v;

		static const DWORD FVF;
	};
};

const D3DXCOLOR      WHITE(D3DCOLOR_XRGB(255, 255, 255));
const D3DXCOLOR      BLACK(D3DCOLOR_XRGB(0, 0, 0));
const D3DXCOLOR        RED(D3DCOLOR_XRGB(255, 0, 0));
const D3DXCOLOR      GREEN(D3DCOLOR_XRGB(0, 255, 0));
const D3DXCOLOR       BLUE(D3DCOLOR_XRGB(0, 0, 255));
const D3DXCOLOR     YELLOW(D3DCOLOR_XRGB(255, 255, 0));
const D3DXCOLOR       CYAN(D3DCOLOR_XRGB(0, 255, 255));
const D3DXCOLOR    MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

const D3DXCOLOR BEACH_SAND(D3DCOLOR_XRGB(255, 249, 157));
const D3DXCOLOR DESERT_SAND(D3DCOLOR_XRGB(250, 205, 135));

const D3DXCOLOR LIGHTGREEN(D3DCOLOR_XRGB(60, 184, 120));
const D3DXCOLOR  PUREGREEN(D3DCOLOR_XRGB(0, 166, 81));
const D3DXCOLOR  DARKGREEN(D3DCOLOR_XRGB(0, 114, 54));

const D3DXCOLOR LIGHT_YELLOW_GREEN(D3DCOLOR_XRGB(124, 197, 118));
const D3DXCOLOR  PURE_YELLOW_GREEN(D3DCOLOR_XRGB(57, 181, 74));
const D3DXCOLOR  DARK_YELLOW_GREEN(D3DCOLOR_XRGB(25, 123, 48));

const D3DXCOLOR LIGHTBROWN(D3DCOLOR_XRGB(198, 156, 109));
const D3DXCOLOR DARKBROWN(D3DCOLOR_XRGB(115, 100, 87));

